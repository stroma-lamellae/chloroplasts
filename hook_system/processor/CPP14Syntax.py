from antlr4 import *
from CPP14Parser import CPP14Parser

variableList = []

def addVariable(ctx):
    global variableList

    if isinstance(ctx, CPP14Parser.DeclaratoridContext):
        ctxChild = ctx.getChild(0)

        if isinstance(ctxChild, CPP14Parser.IdexpressionContext):
            idContext = ctxChild.getChild(0)

            if isinstance(idContext, CPP14Parser.UnqualifiedidContext):
                variableList.append(str(idContext.getChild(0)))

def getVarList():
    return list(dict.fromkeys(variableList))