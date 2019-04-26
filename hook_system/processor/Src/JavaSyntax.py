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

def clearLists():
    variableList.clear()
    funcList.clear()
    classList.clear()
    typeList.clear()