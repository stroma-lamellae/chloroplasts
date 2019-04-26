# Copyright (C) 2019 Hook System Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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