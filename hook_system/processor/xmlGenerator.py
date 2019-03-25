import xml.etree.cElementTree as ET
from typing import List
from match import Match

def generateResult(matches: List[Match]) -> str:
    
    root = ET.Element("results")

    if matches:
        matchesTag = ET.SubElement(root, "matches")

    for match in matches:
        matchTag = ET.SubElement(matchesTag, "match")

        ET.SubElement(matchTag, "number").text = str(match.matchID)

        submissionsTag = ET.SubElement(matchTag, "submissions")
        for plagiarism in match.plagiarismList:
            submissionTag = ET.SubElement(submissionsTag, "submission")

            ET.SubElement(submissionTag, "hash").text = plagiarism.hookFile.fileOwner
            ET.SubElement(submissionTag, "file").text = plagiarism.hookFile.fileName
            ET.SubElement(submissionTag, "line_start").text = str(plagiarism.lineStart)
            ET.SubElement(submissionTag, "line_finish").text = str(plagiarism.lineEnd)

    return ET.tostring(root)