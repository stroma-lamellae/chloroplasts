from PlagiarismDetection.JavaParser import JavaParser
from PlagiarismDetection.JavaLexer import JavaLexer
from PlagiarismDetection.JavaParserVisitor import JavaParserVisitor

from PlagiarismDetection.CPP14Parser import CPP14Parser
from PlagiarismDetection.CPP14Lexer import CPP14Lexer
from PlagiarismDetection.CPP14Visitor import CPP14Visitor

from typing import List, Dict, Tuple
from antlr4 import *
from collections import defaultdict

import PlagiarismDetection.JavaSyntax as JavaSyntax
import PlagiarismDetection.CPP14Syntax as CPP14Syntax

class AnHash:
    startLine: int = -1
    endLine: int = -1
    hashVal: int = -1
    filename: str

class StrippedFile:
    filename: str
    data: str

class Match:
    subList: List[Submission] = []
    number: int #unique within result


FNV_OFFSET_BASIS = 0xcbf29ce484222325
FNV_PRIME        = 0x00000100000001b3
MAX_64           = 0xffffffffffffffff

def winnow(hashes: List[AnHash], w: int) -> List[AnHash]:
    if w > len(hashes):
        print("Error: window length can't be less than number of hashes")
        exit(1)
    
    hashesIndex:int  = 0
    h: List[AnHash] = []
    fingerPrints: List[AnHash] = []

    for i in range(w):
        h.append(AnHash())

    for i in range(w):
        h[(i+1)%w] = hashes[hashesIndex]
        hashesIndex+=1


    minHash: int = 0
    minHashVal: int = MAX_64
    for i in range(w):
        if h[i].hashVal <= minHashVal:
            minHash = i
            minHashVal = h[i].hashVal

    fingerPrints.append(h[minHash])
    r: int = 0

    while hashesIndex < len(hashes):
        r = (r+1)%w
        h[r] = hashes[hashesIndex]
        hashesIndex += 1

        if minHash == r:
            i = (r-1)%w
            while i != r:
                if h[i].hashVal < h[minHash].hashVal:
                    minHash = i

                i = (i-1+w)%w
            fingerPrints.append(h[minHash])
        else:
            if h[r].hashVal < h[minHash].hashVal:
                minHash = r
                fingerPrints.append(h[minHash])
        
    return fingerPrints

def kGramHash(k: int, data: str, filename: str) -> List[AnHash]:
    
    # Create map of how many linebreaks before each literal char
    nNewLinesPrior: Dict[int] = {}
    nNewLines: int = 0
    nLiterals: int = 0

    for i in range(len(data)):
        if data[i] == '\n':
            nNewLines += 1
        else:
            nNewLinesPrior[nLiterals] = nNewLines
            nLiterals+=1
    
    data = data.replace('\n','')

    kGramList: List[AnHash] = []

    for i in range(len(data)-k+1):
        aHash: int = FNV_OFFSET_BASIS
        for c in data[0+i:k+i]:
            aHash = (aHash * FNV_PRIME) & MAX_64
            aHash = (aHash ^ ord(c)) & MAX_64

        leHash = AnHash()
        leHash.startLine = nNewLinesPrior[0+i]+1
        leHash.endLine = nNewLinesPrior[k+i-1]+1
        leHash.hashVal = aHash
        leHash.filename = filename

        kGramList.append(leHash)

    return kGramList

def replaceIfContains(word: str, string: str, rep: str) -> str:
    
    begLoc = string.find(word)

    while begLoc != -1:

        endLoc = begLoc + len(word) - 1

        origBeg = begLoc
        origEnd = endLoc

        if begLoc - 1 >= 0:
            begLoc = begLoc - 1
        if endLoc + 1 < len(string):
            endLoc = endLoc + 1

        # Letter to left is a lowercase letter
        if not ((string[begLoc] >= 'a' and string[begLoc] <= 'z') or (string[begLoc] >= 'A' and string[begLoc] <= 'Z')) or origBeg == begLoc:
            # Letter to right is a lowercase letter
            if not ((string[endLoc] >= 'a' and string[endLoc] <= 'z') or (string[endLoc] >= 'A' and string[endLoc] <= 'Z') or (string[endLoc] >= '0' and string[endLoc] <= '9') or string[endLoc] == '_') or origEnd == endLoc:
                string = string[:origBeg] + rep + string[origBeg+len(word):]

        begLoc = string.find(word, begLoc+len(word)+1)

    return string

def processFile(filename: str, k: int, w: int) -> Tuple[List[AnHash], str]:
    fileData: str = ''
    with open(filename, 'r') as inFile:
        fileData = inFile.read()

    lexar = JavaLexer(InputStream(fileData))
    tokenStream = CommonTokenStream(lexar)
    parser = JavaParser(tokenStream)
    tree = parser.compilationUnit()

    visitor = JavaParserVisitor()
    visitor.visit(tree)

    var, funcs, classes, types = JavaSyntax.getLists()

    words = fileData.split(' ')

    for i in range(len(words)):
        for v in var:
            words[i] = replaceIfContains(v, words[i], "V")

        for f in funcs:
            words[i] = replaceIfContains(f, words[i], "F")

        for c in classes:
            words[i] = replaceIfContains(c, words[i], "C")

        for t in types:
            words[i] = replaceIfContains(t, words[i], "T")

    stripped = ''.join(words).replace('\t','')
    
    return winnow(kGramHash(k, stripped, filename), w), stripped

def process(files: List[str], whiteList: List[str] = []) -> None:
    
    #First we have to create a dict with hash values of all the files
    # Then go through each file and check the dict for hash values that match
    strippedData: List[StrippedFile] = []
    hashDB: Dict[List[AnHash]] = defaultdict(list)
    matchList: List[Match] = []

    k: int = 45
    w: int = 12

    for aFile in files:
        hashes, stripped = processFile(aFile, k, w)

        strFile = StrippedFile()
        strFile.filename = aFile
        strFile.data = stripped

        strippedData.append(strFile)

        for aHash in hashes:
            hashDB[aHash.hashVal].append(aHash)
    
    #Remove hashes that we don't care if being copied
    for white in whiteList:
        hashes, _ = processFile(white, k, w)

        for aHash in hashes:
            if aHash.hashVal in hashDB:
                del hashDB[aHash.hashVal]

    for _ , hashes in hashDB.items():
        if len(hashes) > 1:
            subList: List[Submission] = []

            for aHash in hashes:
                s: Submission = Submission()

                s.filename = aHash.filename
                s.lineStart = aHash.startLine
                s.lineEnd = aHash.endLine
                # s.studentHash = ??????? #IDK where this is coming from
                subList.append(s)
            
            m: Match = Match()
            m.subList = subList
            matchList.append(m)

    
    nonDupeList : List[Match] = []

    for subList in matchList:
        firstFile = subList.subList[0].filename
        multiFiles = False

        for sub in subList.subList[1:]:
            if sub.filename != firstFile:
                multiFiles = True
                break

        if multiFiles:
            nonDupeList.append(subList)

    # TODO generate xml from match list
    for subList in nonDupeList:
        for sub in subList.subList:
            print(sub.filename + ", " + str(sub.lineStart) + "->" + str(sub.lineEnd))
        print()
    print("Total Matches:",len(nonDupeList))

def main():
    filesNon = ["/home/dom/projects/chloroplasts/test-harness/Year/2018-2019/Fall/COSC/1P02/A1/Alan_Turing-Test_4561234/PermutationGenerator.java", "/home/dom/projects/chloroplasts/test-harness/Year/2018-2019/Fall/COSC/1P02/A1/Ada_Lovês-Programmingbabbagémachinès_5012386/xmastree.java"]
    process(filesNon)

    filesPlag = ["/home/dom/projects/chloroplasts/test-harness/Year/2018-2019/Fall/COSC/1P02/A1/Richard_GNU-Linux_1302241/christmasTree.java","/home/dom/projects/chloroplasts/test-harness/Year/2018-2019/Fall/COSC/1P02/A1/Ada_Lovês-Programmingbabbagémachinès_5012386/xmastree.java"]
    process(filesPlag)

if __name__ == "__main__":
    main()