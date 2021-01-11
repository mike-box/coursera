import fileinput
import sys, getopt
from enum import Enum, unique

@unique
class TOKEN_TYPE(Enum):
    TOKEN_KEYWORD = 0
    TOKEN_SYMBOL = 1
    TOKEN_IDENTIFIER = 2
    TOKEN_INT_CONST = 3
    TOKEN_STRING_CONST = 4
    TOKEN_INVALID = 5

@unique
class KEYWORD_TYPE(Enum):
    KEYWORD_CLASS = 101
    KEYWORD_METHOD = 102
    KEYWORD_FUNCTION = 103
    KEYWORD_CONSTRUCTOR = 104
    KEYWORD_BOOLEAN = 105
    KEYWORD_CHAR = 106
    KEYWORD_VOID = 107
    KEYWORD_VAR = 108
    KEYWORD_STATIC = 109
    KEYWORD_FIELD = 110
    KEYWORD_LET = 111
    KEYWORD_DO = 112
    KEYWORD_IF = 113
    KEYWORD_WHILE = 114
    KEYWORD_RETURN = 115
    KEYWORD_TRUE = 116
    KEYWORD_FALSE = 117
    KEYWORD_NULL = 118
    KEYWORD_THIS = 119
    KEYWORD_VALID = 120

keywordname = ["class","method","function","constructor","boolean","char","void","var","static"
               ,"field","let","do","if","else","while","return","true","false","null","this"]
keywordtype = [name for name, member in KEYWORD_TYPE.__members__.items()]
keworddict = dict(zip(keywordname,keywordtype))
tokenname = ["keyword","symbol","identifier","integerConstant","stringConstant"]
tokentype = [name for name, member in TOKEN_TYPE.__members__.items()]
tokendict = dict(zip(tokentype,tokenname))
symboldict = set(['{','}','(',')','[',']',',',';','=','.','+','-','*','/','&','|','~','<','>'])

def validNum(val):
    if len(val) == 0:
        return False
    if val[0] == '0' and len(val) > 1:
        return False
    for c in val:
        if ord(c) < ord('0') or ord(c) > ord('9'):
            return False
    return True

def isAlpha(val):
    if ord(val) >= ord('a') and ord(val) <= ord('z'):
        return True
    if ord(val) >= ord('A') and ord(val) <= ord('Z'):
        return True
    return False

def isDigit(val):
    if ord(val) >= ord('0') and ord(val) <= ord('9'):
        return True
    return False

def validIdentifiers(val):
    if not (val[0] == '_' or isAlpha(val[0])):
        return False
    for i in range(1,len(val)):
        if not (val[i] == '_' or isAlpha(val[i]) or isDigit(val[i])):
            return False
    return True

class Token:
    def __init__(self,tkStr,tkType,linenum,column):
        self.tkStr = tkStr
        self.tkType =  tkType
        self.linenum = linenum
        self.column = column   

class JackTokenizer:
    def __init__(self,infile):
        # read all source code string to the buffer
        self.curr = 0
        self.buffer = ""
        with open(infile,"r") as ifs:
           self.buffer = ifs.read()
        ifs.close()
        self.end = len(self.buffer)
        self.tokens = []
        self.parseToken()
        self.outfile = infile[:infile.find(".jack")] + "T.xml"
        self.genToken()

    def parseToken(self):
        pos = 0
        currStr = ""
        currLine = 1
        currColum = 1

        while pos < self.end:
            #we will skip space
            if self.buffer[pos] == ' ' or \
               self.buffer[pos] == '\n' or \
               self.buffer[pos] == '\t':
                while pos < self.end and (self.buffer[pos] == ' ' or \
                                          self.buffer[pos] == '\n' or \
                                          self.buffer[pos] == '\t'):
                    if self.buffer[pos] == '\n':
                        currLine += 1
                        currColum = 0
                    pos += 1
                    currColum += 1
                continue
        
            # we will skip the comment "//"
            if pos + 1 < len(self.buffer) and self.buffer[pos:pos+2] == "//":
                while pos < self.end and self.buffer[pos] != '\n':
                    currColum += 1
                    pos += 1
                continue

            # we will skip the comment "/* .. */"
            if pos + 1 < len(self.buffer) and self.buffer[pos:pos+2] == "/*":
                pos += 2
                currColum += 2
                while pos < self.end and self.buffer[pos:pos+2] != "*/":
                    if self.buffer[pos] == '\n':
                        currLine += 1
                        currColum = 0
                    pos += 1
                    currColum += 1
                pos += 2
                continue
          
            # check curr token is symbol
            if self.buffer[pos] in symboldict:
                currStr = self.buffer[pos:pos+1]
                self.tokens.append(Token(currStr,self.getType(currStr),currLine,currColum))
                pos += 1
                currColum += 1
                continue
            
            # check string constant
            if pos < self.end and self.buffer[pos] == '"':
                posCurr = pos
                pos += 1
                while pos < self.end and self.buffer[pos] != '"' and self.buffer[pos] != '\n':
                    pos += 1
                    currColum += 1
                pos += 1
                currColum += 1
                currStr = self.buffer[posCurr:pos]
                self.tokens.append(Token(currStr,self.getType(currStr),currLine,currColum))
                continue

            # check curr token 
            posCurr = pos
            while pos < self.end and self.buffer[pos] != ' ' and \
                  self.buffer[pos] != '\n' and self.buffer[pos] not in symboldict:
                currColum += 1
                pos += 1
            if pos > posCurr:
                currStr = self.buffer[posCurr:pos]
                self.tokens.append(Token(currStr,self.getType(currStr),currLine,currColum))

        return True      
    
    def hasMoreTokens(self):
        if self.curr >= len(self.tokens) - 1:
            return False
        return True
    
    def advance(self):
        self.curr += 1

    def currToken(self):
        return self.tokens[self.curr].tkStr

    def tokenType(self):
        return self.tokens[self.curr].tkType
        
    def getType(self,token):
        if token in keworddict:
            return TOKEN_TYPE.TOKEN_KEYWORD
        elif len(token) == 1 and token[0] in symboldict:
            return TOKEN_TYPE.TOKEN_SYMBOL
        elif validNum(token):
            return TOKEN_TYPE.TOKEN_INT_CONST
        elif len(token) > 1 and token[0] == '"' and token[-1] == '"':
            return TOKEN_TYPE.TOKEN_STRING_CONST
        elif validIdentifiers(token):
            return TOKEN_TYPE.TOKEN_IDENTIFIER
        else:
            return TOKEN_TYPE.TOKEN_INVALID

    def keyWord(self):
        return self.tokens[self.curr].tkStr

    def symbol(self):
        return self.tokens[self.curr].tkStr
    
    def identifier(self):
        return self.tokens[self.curr].tkStr
    
    def intVal(self):
        return self.tokens[self.curr].tkStr
    
    def stringVal(self):
        return self.tokens[self.curr].tkStr[1:-1]
    
    def genToken(self):
        out =  open(self.outfile,"w")
        out.write("<tokens>\n")
        for token in self.tokens:
            t = token.tkType
            s = token.tkStr
            row = token.linenum
            col = token.column 
            if t == TOKEN_TYPE.TOKEN_KEYWORD:
                out.write("<keyword> ")
                out.write(s)
                out.write(" </keyword>\n")
            elif t == TOKEN_TYPE.TOKEN_SYMBOL:
                out.write("<symbol> ")
                out.write(s)
                out.write(" </symbol>\n")
            elif t == TOKEN_TYPE.TOKEN_INT_CONST:
                out.write("<integerConstant> ")
                out.write(s)
                out.write(" </integerConstant>\n")
            elif t == TOKEN_TYPE.TOKEN_STRING_CONST:
                out.write("<stringConstant> ")
                out.write(s[1:-1])
                out.write(" </stringConstant>\n")
            elif t == TOKEN_TYPE.TOKEN_IDENTIFIER:
                out.write("<identifier> ")
                out.write(s)
                out.write(" </identifier>\n")
        out.write("</tokens>\n")
        out.close()

def main(input):
    parser = JackTokenizer(input)
    parser.genToken()

if __name__ == "__main__":
    main(sys.argv[1])