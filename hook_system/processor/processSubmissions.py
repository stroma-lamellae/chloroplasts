from submission import Submission
from match import Match
from typing import List
import threading


class ProcessSubmissions():
    mutex = threading.Lock()
    submissionQueue = []

    @staticmethod
    def addToQueue(sub: Submission):
        return True, "1456", "10 Minutes"

    @staticmethod
    def processQueue():
        return

    @staticmethod
    def __sendEmail(emailAddr: str, msg: str) -> bool:
        return True
    
    @staticmethod
    def __generateResult(matches: List[Match]) -> str:
        return "<results></results>"