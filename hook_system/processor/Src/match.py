from plagiarismOccurence import PlagiarismOccurence
from typing import List

class Match():

    def __init__(self, matchID:int, plagiarismList: List[PlagiarismOccurence]):
        self.matchID = matchID
        self.plagiarismList = plagiarismList