from JavaParser import JavaParser
from JavaLexer import JavaLexer
from JavaParserVisitor import JavaParserVisitor

from CPP14Parser import CPP14Parser
from CPP14Lexer import CPP14Lexer
from CPP14Visitor import CPP14Visitor

from antlr4 import *
from standardizedFile import StandardizedFile
from hookFile import HookFile
from typing import List

import JavaSyntax as JavaSyntax
import CPP14Syntax as CPP14Syntax


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


def standardizeJava(javaFiles: List[HookFile]) -> List[StandardizedFile]:
    standardizedFiles: List[StandardizedFile] = []
    
    for javaFile in javaFiles:
        lexer = JavaLexer(InputStream(javaFile.fileData))
        tokenStream = CommonTokenStream(lexer)
        parser = JavaParser(tokenStream)
        tree = parser.compilationUnit()

        visitor = JavaParserVisitor()
        visitor.visit(tree)

        var, funcs, classes, types = JavaSyntax.getLists()

        words = javaFile.fileData.split(' ')

        for i in range(len(words)):
            for v in var:
                words[i] = replaceIfContains(v, words[i], "V")

            for f in funcs:
                words[i] = replaceIfContains(f, words[i], "F")

            for c in classes:
                words[i] = replaceIfContains(c, words[i], "C")

            for t in types:
                words[i] = replaceIfContains(t, words[i], "T")

        stripped = ''.join(words).replace('\t','').lower()

        standardizedFiles.append(StandardizedFile(javaFile, stripped))

        JavaSyntax.clearLists()

    return standardizedFiles
    
def standardizeC(cFiles: List[HookFile]) -> List[StandardizedFile]:
    standardizedFiles: List[StandardizedFile] = []

    for cFile in cFiles:
        lexer = CPP14Lexer(InputStream(cFile.fileData))
        tokenStream = CommonTokenStream(lexer)
        parser = CPP14Parser(tokenStream)
        tree = parser.translationunit()

        visitor = CPP14Visitor()
        visitor.visit(tree)

        var = CPP14Syntax.getVarList()

        words = cFile.fileData.split(' ')

        for i in range(len(words)):
            for v in var:
                words[i] = replaceIfContains(v, words[i], "v")

        stripped = ''.join(words).replace('\t','').lower()

        standardizedFiles.append(StandardizedFile(cFile, stripped))

        CPP14Syntax.clearList()

    return standardizedFiles
