from hookFileType import HookFileType

class HookFile():

    def __init__(self, fileName: str, fileOwner: str, fileType: HookFileType, fileData: str):
        self.fileName = fileName
        self.fileOwner = fileOwner
        self.fileType = fileType
        self.fileData = fileData