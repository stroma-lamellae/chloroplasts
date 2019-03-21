from submission import Submission
from match import Match
from typing import List, Tuple
import threading

mutex = threading.Lock()
submissionQueue: List[Tuple[str, str]] = []


def addToQueue(filePath: str, emailAddr: str) -> Tuple[bool, str]:
    
    
    mutex.acquire()

    nPrior: int = len(submissionQueue)

    submissionQueue.append((filePath, emailAddr))

    nCur:int = len(submissionQueue)

    mutex.release()

    if nCur == nPrior+1:
        return True, "10 Minutes"
    else:
        return False, ""



def processQueue():
    return

def __sendEmail(emailAddr: str, msg: str) -> bool:
    return True

def __generateResult(matches: List[Match]) -> str:
    return "<results></results>"