from hookFile import HookFile

class PlagiarismOccurence():

    def __init__(self, hookFile: HookFile, lineStart: int, lineEnd: int):
        self.hookFile = hookFile
        self.lineStart = lineStart
        self.lineEnd = lineEnd