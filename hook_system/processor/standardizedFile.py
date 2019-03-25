from hookFile import HookFile

class StandardizedFile():
    def __init__(self, origFile: HookFile, standardizedData: str):
        self.origFile = origFile
        self.standardizedData = standardizedData