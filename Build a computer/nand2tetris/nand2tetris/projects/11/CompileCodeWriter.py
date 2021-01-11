import fileinput
import sys, getopt
import os
from enum import Enum, unique
import sys
from JackTokenizer import JackTokenizer,TOKEN_TYPE,KEYWORD_TYPE,tokentype,tokendict
from SymbolTable import SymbolTable
from VmWriter import VmWriter,SEG_TYPE,OP_TYPE,opdict
from CompileEngine import CompileEngine

class CompileCodeWriter:
    def __init__(self,infile):
        # read all source code string to the buffer
        self.parser = JackTokenizer(infile)
        self.engile = CompileEngine(infile)
        self.out = VmWriter(infile)
        # class global symbol table
        self.classTable = SymbolTable()
        # sub routine symbol table
        self.subTable = SymbolTable()
        # vm writer
        self.vmout = VmWriter(infile)
        # class name
        self.classname = ""
        self.subname = ""
        self.subkind = ""
        self.subtype = ""
        self.iflabelcnt = 0
        self.whilelabelcnt = 0
        self.writeClassCode()
        self.out.close()

    def ifLabel(self):
        res = []
        res.append("IF_END" + str(self.iflabelcnt))
        res.append("IF_" + str(self.iflabelcnt))
        self.iflabelcnt += 1
        return res

    def whileLabel(self):
        res = []
        res.append("WHILE_EXP" + str(self.whilelabelcnt))
        res.append("WHILE_END" + str(self.whilelabelcnt))
        self.whilelabelcnt += 1
        return res

    def functionLabel(self):
        return self.classname + "." + self.subname

    def writeClassCode(self):
        self.classTable.startSubroutine()
        # parse class
        self.parser.advance()
        # parse class name
        self.classname = self.parser.currToken()
        self.parser.advance()
        #parse symbol '{' 
        self.parser.advance()
        #parse class val des
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
              (self.parser.keyWord() == "static" or self.parser.keyWord() == "field"):
            self.writeClassVarDecCode()
        
        #parse class method
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
            (self.parser.keyWord() == "method" or \
            self.parser.keyWord() == "constructor" or \
            self.parser.keyWord() == "function"):
            self.subkind = self.parser.keyWord()
            self.writeSubroutineCode()
        #parse symbol '{'
        self.parser.advance()

        return True          

    def writeClassVarDecCode(self):
        varname = ""
        vartype = ""
        varkind = ""

        # parse key word
        varkind = self.parser.keyWord()
        self.parser.advance()
        # parse val type
        vartype = self.parser.currToken()
        self.parser.advance()
        # parse val name
        varname = self.parser.currToken()
        self.parser.advance()
        #add one var define to the symbol table
        self.classTable.define(varname,vartype,varkind)
        # parse the left val name
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
              self.parser.symbol() == ";"):
            # parse symbol ','
            self.parser.advance()
            # parse val name
            varname = self.parser.currToken()
            self.classTable.define(varname,vartype,varkind)
            self.parser.advance()
        # parse the end symbol ';'
        self.parser.advance()

        return True

    def writeSubroutineCode(self):
        fieldcnt = 0
        self.subTable.startSubroutine()

        # parse key word
        self.subkind = self.parser.currToken()
        self.parser.advance()
        if self.subkind == "method":
            self.subTable.define("this",self.classname,"argument")
        # parse type
        self.subtype = self.parser.currToken()
        self.parser.advance()
        # parse subroutineName
        self.subname = self.parser.currToken()
        self.parser.advance()
        # parse '('
        self.parser.advance()
        # parse param list
        self.writeParameterListCode()
        # parse ')'
        self.parser.advance()
        # parse body
        self.writeSubroutineBodyCode()

        return True
    
    def writeSubroutineBodyCode(self):
        nlocals = 0
        # parse '{'
        self.parser.advance()
        # parse var 
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "var":
            nlocals += self.writeVarDecCode()
        
        # function define
        funcname = self.classname + "." + self.subname
        self.out.writeFunction(funcname,nlocals)
        if self.subkind == "constructor":
            fieldcnt = self.classTable.varCount("field")
            self.out.writePush("constant",fieldcnt)
            self.out.writeCall("Memory.alloc",1)
            self.out.writePop("pointer",0)
        elif self.subkind == "method":
            self.out.writePush("argument",0)
            self.out.writePop("pointer",0)

        # parse statements
        self.writeStatementsCode()
        # parse '}'
        self.parser.advance()
        return True

    def writeParameterListCode(self):
        varname = ""
        varkind = "argument"
        vartype = ""
        paramcnt = 0

        # parse rest param
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and\
            self.parser.symbol() == ")"):
            # parse element type
            vartype = self.parser.currToken()
            self.parser.advance()
            # parse element varName
            varname = self.parser.currToken()
            paramcnt += 1
            self.parser.advance()
            # add argument variable into the symbol table
            self.subTable.define(varname,vartype,varkind)
            # parse ','
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
                if self.parser.symbol() == ",":
                    self.parser.advance()
                elif self.parser.symbol() == ")":
                    break

        return paramcnt
    
    def writeVarDecCode(self):
        nlocals = 1
        varname = ""
        varkind = "var"
        vartype = ""

        # parse key word
        varkind = self.parser.keyWord()
        self.parser.advance()
        # parse var type
        vartype = self.parser.currToken()
        self.parser.advance()
        # parse var name
        varname = self.parser.currToken()
        self.parser.advance()
        self.subTable.define(varname,vartype,varkind)

        # parse the rest var name
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
              self.parser.symbol() == ";"):
            self.parser.advance()
            # parse var name
            nlocals += 1
            varname = self.parser.currToken()
            self.subTable.define(varname,vartype,varkind)
            self.parser.advance()
  
        # parse the end symbol  
        self.parser.advance()
        return nlocals 
    
    def writeStatementsCode(self):
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
             (self.parser.keyWord() == "do" or \
              self.parser.keyWord() == "if" or \
              self.parser.keyWord() == "while" or \
              self.parser.keyWord() == "let" or \
              self.parser.keyWord() == "return"):
            if self.parser.keyWord() == "do":
                self.writeDoCode()
            elif self.parser.keyWord() == "if":
                self.writeIfCode()
            elif self.parser.keyWord() == "while":
                self.writeWhileCode()
            elif self.parser.keyWord() == "let":
                self.writeLetCode()
            elif self.parser.keyWord() == "return":
                self.writeReturnCode()
            else:
                print("valid statement define!\n")
                exit(1)

        return True 
    
    def writeDoCode(self):
        funcname = []
        argsCnt = 0
        varname = ""
        vartype = ""
        varkind = ""
        varidx  = ""

        # parse do
        self.parser.advance()
        # parse 'call name'
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "("):
            # write code
            if self.parser.tokenType() != TOKEN_TYPE.TOKEN_SYMBOL:
                funcname.append(self.parser.currToken())
            self.parser.advance()

        # parse '('
        self.parser.advance()
        
        # sub call
        callname = ""
        varname = funcname[0]
        if len(funcname) == 1:
            self.out.writePush("pointer",0)
            callname = self.classname + "." + funcname[0]
            argsCnt += 1
        elif len(funcname) == 2:
            if self.subTable.indexOf(varname) >= 0:
                vartype = self.subTable.typeOf(varname)
                varkind = self.subTable.kindOf(varname)
                varidx =  self.subTable.indexOf(varname)
                callname = vartype + "." + funcname[1]
                argsCnt += 1
                if varkind == "field":
                    self.out.writePush("this",varidx)
                elif varkind == "var":
                    self.out.writePush("local",varidx)
                elif varkind == "static":
                    self.out.writePush("static",varidx)
                elif varkind == "argument":
                    self.out.writePush("argument",varidx)
            elif  self.classTable.indexOf(varname) >= 0:
                vartype = self.classTable.typeOf(varname)
                varkind = self.classTable.kindOf(varname)
                varidx =  self.classTable.indexOf(varname)
                callname = vartype + "." + funcname[1]
                argsCnt += 1
                if varkind == "field":
                    self.out.writePush("this",varidx)
                elif varkind == "var":
                    self.out.writePush("local",varidx)
                elif varkind == "static":
                    self.out.writePush("static",varidx)
                elif varkind == "argument":
                    self.out.writePush("argument",varidx)
            else:
                callname = funcname[0] + "." + funcname[1]
        # parse expression list       
        argsCnt += self.writeExpressionListCode()
        # parse ')'
        self.parser.advance()
        # parse  ';'
        self.parser.advance()
        # write call name
        self.out.writeCall(callname,argsCnt)
        self.out.writePop("temp",0)

        return True
    
    def writeLetCode(self):
        varname = ""
        vartype = ""
        varkind = ""
        varidx  = ""
        isArray = False
        # parse let 
        self.parser.advance()
   
        # parse varname
        varname = self.parser.currToken()
        # search the key
        if self.subTable.indexOf(varname) >= 0:
            vartype = self.subTable.typeOf(varname)
            varkind = self.subTable.kindOf(varname)
            varidx =  self.subTable.indexOf(varname)
        elif  self.classTable.indexOf(varname) >= 0:
            vartype = self.classTable.typeOf(varname)
            varkind = self.classTable.kindOf(varname)
            varidx =  self.classTable.indexOf(varname)
        else:
            print("invalid var statement!")
            return False

        # skip varname
        self.parser.advance()
      
        # parse `[expression]`
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == '[':
            
            # we push the head arrdress of the array
            isArray = True
            # parse '['
            self.parser.advance()
            # parse expression
            self.writeExpressionCode()
            # we parse the array
            if varkind == "field":
                self.out.writePush("this",varidx)
            elif varkind == "var":
                self.out.writePush("local",varidx)
            elif varkind == "static":
                self.out.writePush("static",varidx)
            elif varkind == "argument":
                self.out.writePush("argument",varidx)
            self.out.writeArithmetic("+")
            # parse ']'
            self.parser.advance()

        # parse  '='
        self.parser.advance()
        # parse expression
        self.writeExpressionCode()
        # pop value from the stack
        if isArray:
            self.out.writePop("temp",0)
            self.out.writePop("pointer",1)
            self.out.writePush("temp",0)
            self.out.writePop("that",0)
        else:
            if varkind == "field":
                self.out.writePop("this",varidx)
            elif varkind == "var":
                self.out.writePop("local",varidx)
            elif varkind == "static":
                self.out.writePop("static",varidx)
            elif varkind == "argument":
                self.out.writePop("argument",varidx)
        # parse  ';'
        self.parser.advance()
        return True
    
    def writeWhileCode(self):
        label = self.whileLabel()

        # parse return 
        self.parser.advance()
        # parse '('
        self.parser.advance()
        # parse expression
        self.out.writeLabel(label[0])
        self.writeExpressionCode()
        self.out.writeSigArithmetic("~")
        self.out.writeIf(label[1])
        # parse  ')'
        self.parser.advance()
        # parse  '{'
        self.parser.advance()
        # parse statements
        self.writeStatementsCode()
        self.out.writeGoto(label[0])
        # parse  '}'
        self.out.writeLabel(label[1])
        self.parser.advance()

        return True
    
    def writeReturnCode(self):        
        # parse return 
        self.parser.advance()
        # parse expression  list
        if not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ';'):
            self.writeExpressionCode()
        # parse ';'
        self.parser.advance()
        if self.subtype == "void":
            self.out.writePush("constant",0)
        self.out.writeReturn()

        return True
    
    def writeIfCode(self):
        label = self.ifLabel()

        # parse if 
        self.parser.advance()
        # parse '('
        self.parser.advance()
        # parse expression
        self.writeExpressionCode()
        self.out.writeSigArithmetic("~")
        # parse ')'
        self.parser.advance()
        # parse '{'
        self.parser.advance()
        # parse statements
        self.out.writeIf(label[1])
        self.writeStatementsCode()
        self.out.writeGoto(label[0])
        # parse '}'
        self.parser.advance()
   
        # parse else
        self.out.writeLabel(label[1])
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "else":
            
            # parse 'else'
            self.parser.advance()
            # parse '{'
            self.parser.advance()
            # parse statements
            self.writeStatementsCode()
            # parse '}'
            self.parser.advance()
        self.out.writeLabel(label[0])

        return True
    
    def writeExpressionCode(self):
        # parse term
        self.writeTermCode()

        # parse op
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           (self.parser.symbol() == "+" or self.parser.symbol() == "-" or \
            self.parser.symbol() == "*" or self.parser.symbol() == "/" or \
            self.parser.symbol() == "&" or self.parser.symbol() == "|" or \
            self.parser.symbol() == ">" or self.parser.symbol() == "<" or \
            self.parser.symbol() == "="):
            # parse op
            op = self.parser.symbol()
            self.parser.advance()
            # parse term
            self.writeTermCode()
            # code write op
            if op == "*":
                self.out.writeCall("Math.multiply",2)
            elif op == '/':
                self.out.writeCall("Math.divide",2)
            else:
                self.out.writeArithmetic(op)
        return True
    
    def writeTermCode(self):
        varname = ""
        vartype = ""
        varkind = ""
        varidx  = 0
        paramCnt = 0

        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_INT_CONST:
            # push constant x
            self.out.writePush("constant",self.parser.intVal())
            #print(self.parser.intVal())
            self.parser.advance()
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_STRING_CONST:
            # push string x
            val = self.parser.stringVal()
            self.out.writePush("constant",len(val))
            self.out.writeCall("String.new",1)
            for c in val:
                self.out.writePush("constant",ord(c))
                self.out.writeCall("String.appendChar",2)
            self.parser.advance()
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD:
            # parse keword const
            if self.parser.keyWord() == "true" or self.parser.keyWord() == "false" or \
               self.parser.keyWord() == "null" or self.parser.keyWord() == "this":
                if self.parser.keyWord() == "true":
                    self.out.writePush("constant",0)
                    self.out.writeSigArithmetic("~")
                elif self.parser.keyWord() == "false":
                    self.out.writePush("constant",0)
                elif self.parser.keyWord() == "null":
                    self.out.writePush("constant",0)
                elif self.parser.keyWord() == "this":
                    self.out.writePush("pointer",0)
                self.parser.advance()
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
            if self.parser.symbol() == "(":
                # parse '('
                self.parser.advance()
                # parse expression
                self.writeExpressionCode()
                # parse ')'
                self.parser.advance()
            elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
                (self.parser.symbol() == "-" or self.parser.symbol() == "~"):
                # parse unaryOp
                op = self.parser.symbol()
                self.parser.advance()
                # parse term
                self.writeTermCode()
                self.out.writeSigArithmetic(op)
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            # skip varname
            termname = self.parser.currToken()
            self.parser.advance()

            # we push the head arrdress of the array
            # parse expression
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "[":
                # parse subroutineName or varName            
                if self.subTable.indexOf(termname) >= 0:
                    vartype = self.subTable.typeOf(termname)
                    varkind = self.subTable.kindOf(termname)
                    varidx =  self.subTable.indexOf(termname)
                elif  self.classTable.indexOf(termname) >= 0:
                    vartype = self.classTable.typeOf(termname)
                    varkind = self.classTable.kindOf(termname)
                    varidx =  self.classTable.indexOf(termname)
                else:
                    print("invalid var statement!")
                    return False

                # parse '['
                self.parser.advance()
                # parse expression
                self.writeExpressionCode()
                 # parse var type 
                if varkind == "field":
                    self.out.writePush("this",varidx)
                elif varkind == "var":
                    self.out.writePush("local",varidx)
                elif varkind == "static":
                    self.out.writePush("static",varidx)
                elif varkind == "argument":
                    self.out.writePush("argument",varidx)
                # add
                self.out.writeArithmetic("+")
                self.out.writePop("pointer",1)
                self.out.writePush("that",0)

                # parse ']'
                self.parser.advance()
            # parse subcall
            elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ".":
                # parse '.'
                self.parser.advance()

                # parse subroutineName
                termfunc = self.parser.currToken()
                self.parser.advance()

                # parse call name
                if self.subTable.indexOf(termname) >= 0:
                    vartype = self.subTable.typeOf(termname)
                    varkind = self.subTable.kindOf(termname)
                    varidx =  self.subTable.indexOf(termname)
                    paramCnt += 1
                    if varkind == "field":
                        self.out.writePush("this",varidx)
                    elif varkind == "var":
                        self.out.writePush("local",varidx)
                    elif varkind == "static":
                        self.out.writePush("static",varidx)
                    elif varkind == "argument":
                        self.out.writePush("argument",varidx)
                elif  self.classTable.indexOf(termname) >= 0:
                    vartype = self.classTable.typeOf(termname)
                    varkind = self.classTable.kindOf(termname)
                    varidx =  self.classTable.indexOf(termname)
                    paramCnt += 1
                    if varkind == "field":
                        self.out.writePush("this",varidx)
                    elif varkind == "var":
                        self.out.writePush("local",varidx)
                    elif varkind == "static":
                        self.out.writePush("static",varidx)
                    elif varkind == "argument":
                        self.out.writePush("argument",varidx)
                else:
                    vartype = termname

                # parse '('
                self.parser.advance()
                # parse expressList
                paramCnt += self.writeExpressionListCode()
                # parse ')'
                self.parser.advance()
                # write var code
                self.out.writeCall(vartype + "." + termfunc,paramCnt)
            # parse call
            elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "(":
                # parse '('
                self.parser.advance()
                # parse expressList
                self.out.writePush("pointer",0)
                paramCnt = self.writeExpressionListCode() + 1
                # parse ')'
                self.parser.advance()
                # write var code
                self.out.writeCall(self.classname + "." + termfunc,paramCnt)
                # print(self.classname + "." + termfunc + str(paramCnt))
            else:
                # parse subroutineName or varName            
                if self.subTable.indexOf(termname) >= 0:
                    vartype = self.subTable.typeOf(termname)
                    varkind = self.subTable.kindOf(termname)
                    varidx =  self.subTable.indexOf(termname)
                elif  self.classTable.indexOf(termname) >= 0:
                    vartype = self.classTable.typeOf(termname)
                    varkind = self.classTable.kindOf(termname)
                    varidx =  self.classTable.indexOf(termname)
                else:
                    print("invalid var statement!")
                    return False

                if varkind == "field":
                    self.out.writePush("this",varidx)
                elif varkind == "var":
                    self.out.writePush("local",varidx)
                elif varkind == "static":
                    self.out.writePush("static",varidx)
                elif varkind == "argument":
                    self.out.writePush("argument",varidx)

        return True
    
    def writeExpressionListCode(self):
        argsCnt = 0

        if self.parser.symbol() == ')' and \
           self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
            return argsCnt

        # parse expression
        argsCnt += 1
        self.writeExpressionCode()
        
        # parse `, expression`
        while self.parser.symbol() == ',' and \
              self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
            # parse ','
            self.parser.advance()
            # parse expression
            argsCnt += 1
            self.writeExpressionCode()

        return argsCnt

def main(input):
    if os.path.exists(input):
        if os.path.isdir(input):
            files = os.listdir(input)
            for f in files:
                filename = input+f
                if filename.find(".jack") >= 0:
                    CompileCodeWriter(input+f)
        else:
            CompileCodeWriter(input)            
    else:
        print("invalid path")

if __name__ == "__main__":
    main(sys.argv[1])