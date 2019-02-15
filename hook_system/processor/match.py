from hookFile import HookFile

class Match():

    def __init__(self, sOneFile: HookFile, sOneLines: tuple, sTwoFile: HookFile, sTwoLines: tuple):
        self.sOneFile = sOneFile
        self.sOneLines = sOneLines

        self.sTwoFile = sTwoFile
        self.sTwoLines = sTwoLines