import fileinput
import sys, getopt
from enum import Enum, unique

@unique
class SEG_TYPE(Enum):
    SEG_CONST = 0
    SEG_ARG = 1
    SEG_LOCAL = 2
    SEG_STATIC  = 3
    SEG_THIS = 4
    SEG_THAT = 5
    SEG_POINTER = 6
    SEG_TMP  = 7

@unique
class OP_TYPE(Enum):
    OP_ADD = 0
    OP_SUB = 1
    OP_NEG = 2
    OP_EQ = 3
    OP_GT = 4
    OP_LT = 5
    OP_AND = 6
    OP_OR = 7
    OP_NOT = 8

optype = ['+','-','=','>','<','&','|']
soptype = ['-','~']
opname = ["add","sub","eq","gt","lt","and","or",]
sopname = ["neg","not"]
opdict = dict(zip(optype,opname))
sopdict = dict(zip(soptype,sopname))

class VmWriter:
    def __init__(self,filename):
        # read all source code string to the buffer
        self.code = []
        outfile = filename[:filename.find(".jack")] + ".vm"
        self.out = None
        self.out = open(outfile,"w+")

    def writePush(self,seg,idx):
        # self.out.write("push " + seg + " " + str(idx))
        # self.out.write("\n")
        self.code.append("push " + seg + " " + str(idx))
        return True
    
    def writePop(self,seg,idx):
        # self.out.write("pop " + seg + " " + str(idx) + "\n")
        self.code.append("pop " + seg + " " + str(idx))
        return True
    
    def writeArithmetic(self,op):
        # self.out.write(opdict[op] + "\n")
        self.code.append(opdict[op])
        return True
    
    def writeSigArithmetic(self,op):
        self.code.append(sopdict[op])
        return True

    def writeLabel(self,label):
        # self.out.write("label " + label + "\n")
        self.code.append("label " + label)
        return True
    
    def writeGoto(self,label):
        # self.out.write("goto " + label + "\n")
        self.code.append("goto " + label)
        return True
    
    def writeIf(self,label):
        #self.out.write("if-goto " + label + "\n")
        self.code.append("if-goto " + label)
        return True
    
    def writeCall(self,name,nArgs):
        #self.out.write("call " + name + " " + str(nArgs) + "\n")
        self.code.append("call " + name + " " + str(nArgs))
        return True
    
    def writeFunction(self,name,nLocals):
        #self.out.write("function "+ name + " " + str(nLocals) + "\n")
        self.code.append("function "+ name + " " + str(nLocals))
        return True
    
    def writeReturn(self):
        #self.out.write("return\n")
        self.code.append("return")
        return True
    
    def close(self):
        for v in self.code:
            self.out.write(v)
            self.out.write("\n")
        self.out.close()
        return True
