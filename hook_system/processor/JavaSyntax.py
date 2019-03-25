from antlr4 import *
from JavaParser import JavaParser

variableList = []
classList = []
funcList = []
typeList = []

def getClass(ctx):
    terminals = []
    for x in range(ctx.getChildCount()):
        if isinstance(ctx.getChild(x), TerminalNode):
            terminals.append(str(ctx.getChild(x)))

    return terminals[1]

def getVars(ctx):
    terminals = []
    for x in range(ctx.getChildCount()):
        if isinstance(ctx.getChild(x), TerminalNode):
            terminals.append(str(ctx.getChild(x)))

    return terminals

def addVariable(ctx):
    global variableList, funcList, classList
    
    if isinstance(ctx, JavaParser.VariableDeclaratorIdContext):
        # print("Variable")
        possibleVars = getVars(ctx)

        variableList += possibleVars

    if isinstance(ctx, JavaParser.MethodDeclarationContext):
        # print("Method")
        possibleVars = getVars(ctx)

        funcList += possibleVars

    if isinstance(ctx, JavaParser.ClassDeclarationContext):
        # print("Class")
        possibleVars = getClass(ctx)

        classList.append(possibleVars)

    if isinstance(ctx, JavaParser.TypeTypeContext):
        
        if isinstance(ctx.getChild(0), JavaParser.ClassOrInterfaceTypeContext):
            typeList.append(str(ctx.getChild(0).getChild(0)))

def getLists():
    return list(dict.fromkeys(variableList)), list(dict.fromkeys(funcList)), list(dict.fromkeys(classList)), list(dict.fromkeys(typeList))