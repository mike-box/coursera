from JackTokenizer import JackTokenizer,TOKEN_TYPE,KEYWORD_TYPE,tokentype,tokendict
import fileinput
import sys, getopt
from enum import Enum, unique
import sys

class CompilationEngine:
    def __init__(self,infile):
        # read all source code string to the buffer
        self.parser = JackTokenizer(infile)
        outfile = infile[:infile.find(".jack")] + ".xml"
        self.out = open(outfile,"w")
        self.depth = 0
        self.compileClass()
        self.out.close()

    def lowerLevel(self):
        self.depth += 1

    def upperLevel(self):
        self.depth -= 1

    def compileOut(self,str):
        self.out.write("  "*self.depth)
        self.out.write(str)

    def compileOutElement(self,tkType,tkStr):
        self.out.write("  "*self.depth)
        typeStr = ""
        if tkType == TOKEN_TYPE.TOKEN_KEYWORD:
            typeStr = "keyword"
        elif tkType == TOKEN_TYPE.TOKEN_SYMBOL:
            typeStr = "symbol"
        elif tkType == TOKEN_TYPE.TOKEN_IDENTIFIER:
            typeStr = "identifier"
        elif tkType == TOKEN_TYPE.TOKEN_INT_CONST:
            typeStr = "integerConstant"
        elif tkType == TOKEN_TYPE.TOKEN_STRING_CONST:
            typeStr = "stringConstant"
        elif tkType == TOKEN_TYPE.TOKEN_INVALID:
            typeStr = "invalid"
        self.out.write("<" + typeStr + "> " + tkStr + " </" + typeStr + ">\n")

    def compileClass(self):
        self.compileOut("<class>\n")
        self.lowerLevel()
        
        # parse class
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD  and \
           self.parser.keyWord() == "class":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid class define!\n")
            exit(1)

        # parse class name
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid class define!\n")
            exit(1)

        #parse symbol '{' 
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
            self.parser.symbol() == "{":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid class define!\n")
            exit(1)
            
        #parse class val des
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
              (self.parser.keyWord() == "static" or self.parser.keyWord() == "field"):
            self.compileClassVarDec()
            
        #parse class method
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
            (self.parser.keyWord() == "method" or \
            self.parser.keyWord() == "constructor" or \
            self.parser.keyWord() == "function"):
            self.compileSubroutine()

        #parse symbol '{'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
            self.parser.symbol() == "}":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid class define!\n")
            exit(1)

        # end of parse class
        self.upperLevel()
        self.compileOut("</class>\n")
        return True          

    def compileClassVarDec(self):
        self.compileOut("<classVarDec>\n")
        self.lowerLevel()

        # parse key word
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
          (self.parser.keyWord() == "static" or self.parser.keyWord() == "field"):
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid val define!\n")
            exit(1)
        
        # parse val type
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD or \
           self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid val define!\n")
            exit(1)
        
        # parse val name
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid val define!\n")
            exit(1)

        # parse the left val name
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
              self.parser.symbol() == ";"):
            # parse symbol ','
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ",":
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()
            else:
                print(str(sys._getframe().f_lineno) + "valid val define!\n")
                exit(1)

            # parse val name
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()
            else:
                print(str(sys._getframe().f_lineno) + "valid val define!\n")
                exit(1)
            

        # parse the end symbol  
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ";":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "valid val define!\n")
            exit(1)

        # end of class var descrtion
        self.upperLevel()
        self.compileOut("</classVarDec>\n")
        return True

    def compileSubroutine(self):
        self.compileOut("<subroutineDec>\n")
        self.lowerLevel()

        # parse key word
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD  and \
           (self.parser.keyWord() == "constructor" or \
            self.parser.keyWord() == "function" or \
            self.parser.keyWord() == "method"):
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "invalid subroutine!\n")
            exit(1)
        
        # parse type
        if (self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD  and \
           (self.parser.keyWord() == "int" or \
            self.parser.keyWord() == "char" or \
            self.parser.keyWord() == "void" or \
            self.parser.keyWord() == "boolean")) or \
            self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
           if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD:
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()
           elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "invalid subroutine!\n")
            exit(1)
        
        # parse subroutineName
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "invalid subroutine!\n")
            exit(1)
        
        # parse '('
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "(":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "invalid subroutine!\n")
            exit(1)

        # parse param list
        self.compileParameterList()

        # parse ')'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ")":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print(str(sys._getframe().f_lineno) + "invalid subroutine!\n")
            exit(1)

        # parse body
        self.compileSubroutineBody()

        self.upperLevel()
        self.compileOut("</subroutineDec>\n")
        return True
    
    def compileSubroutineBody(self):
        self.compileOut("<subroutineBody>\n")
        self.lowerLevel()

        # parse '{'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "{":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print("inValid sub routine body define!\n")
            exit(1)
        
        # parse var 
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "var":
            self.compileVarDec()
        
        # parse statements
        self.compileStatements()

        # parse '}'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "}":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid sub routine body define!\n")
            exit(1)

        self.upperLevel()
        self.compileOut("</subroutineBody>\n")
        return True

    def compileParameterList(self):
        self.compileOut("<parameterList>\n")
        self.lowerLevel()

        # parse rest param
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and\
            self.parser.symbol() == ")"):
            # parse first element type
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER or \
               (self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
               (self.parser.keyWord() == "int" or self.parser.keyWord() == "char" or \
                self.parser.keyWord() == "boolean")):
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()

            # parse first element varName
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()

            # parse ','
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
                if self.parser.symbol() == ",":
                    self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                    self.parser.advance()
                elif self.parser.symbol() == ")":
                    break
                else:
                    print(str(sys._getframe().f_lineno) + "valid param list!\n")
                    exit(1)
            else:
                print(str(sys._getframe().f_lineno) + "valid param list!\n")
                exit(1)

        self.upperLevel()
        self.compileOut("</parameterList>\n")
        return True
    
    def compileVarDec(self):
        self.compileOut("<varDec>\n")
        self.lowerLevel()

        # parse key word
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "var":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print("valid val define!\n")
            exit(1)
        
        # parse var type
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD or \
           self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print("valid val define!\n")
            exit(1)
        
        # parse var name
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print("valid val define!\n")
            exit(1)

        # parse the rest var name
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
              self.parser.symbol() == ";"):
            # parse ","
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ",":
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()
            else:
                print("valid val define!\n")
                exit(1)

            # parse var name
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
                self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                self.parser.advance()
            else:
                print("valid val define!\n")
                exit(1)
            
        # parse the end symbol  
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ";":
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        else:
            print("valid var define!\n")
            exit(1)

        # end of class var descrtion
        self.upperLevel()
        self.compileOut("</varDec>\n")
        return True 
    
    def compileStatements(self):
        self.compileOut("<statements>\n")
        self.lowerLevel()

        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
             (self.parser.keyWord() == "do" or \
              self.parser.keyWord() == "if" or \
              self.parser.keyWord() == "while" or \
              self.parser.keyWord() == "let" or \
              self.parser.keyWord() == "return"):
            if self.parser.keyWord() == "do":
                self.compileDo()
            elif self.parser.keyWord() == "if":
                self.compileIf()
            elif self.parser.keyWord() == "while":
                self.compileWhile()
            elif self.parser.keyWord() == "let":
                self.compileLet()
            elif self.parser.keyWord() == "return":
                self.compileReturn()
            else:
                print("valid statement define!\n")
                exit(1)

        self.upperLevel()
        self.compileOut("</statements>\n")
        return True 
    
    def compileDo(self):
        self.compileOut("<doStatement>\n")
        self.lowerLevel()

        # parse do
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "do":
            self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
            self.parser.advance()
        else:
            print("inValid do  define!\n")
            exit(1)
        
        # parse '('
        while not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "("):
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()
        
        # parse '('
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "(":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid do statement  define!\n")
            exit(1)

        # parse expression list
        self.compileExpressionList()
        
        # parse ')'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ")":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid do statement body define!\n")
            exit(1)

        # parse  ';'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ';':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid do statement  define!\n")
            exit(1)
    
        self.upperLevel()
        self.compileOut("</doStatement>\n")
        return True
    
    def compileLet(self):
        self.compileOut("<letStatement>\n")
        self.lowerLevel()

        # parse let 
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "let":
            self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
            self.parser.advance()
        else:
            print("inValid let  define!\n")
            exit(1)

        # parse varname
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            self.compileOutElement(self.parser.tokenType(),self.parser.identifier())
            self.parser.advance()
        else:
            print("inValid let  define!\n")
            exit(1)
        
        # parse `[expression]`
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
              self.parser.symbol() == '[':
            # parse '['
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()

            # parse expression
            self.compileExpression()

            # parse ']'
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
               self.parser.symbol() == ']':
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()
            else:
                print("inValid let  define!\n")
                exit(1)

        # parse  '='
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == '=':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid let  define!\n")
            exit(1)

        # parse expression
        self.compileExpression()

        # parse  ';'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ';':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid let  define!\n")
            exit(1)
    
        self.upperLevel()
        self.compileOut("</letStatement>\n")
        return True
    
    def compileWhile(self):
        self.compileOut("<whileStatement>\n")
        self.lowerLevel()

        # parse return 
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "while":
            self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
            self.parser.advance()
        else:
            print("inValid while  define!\n")
            exit(1)

        # parse '('
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == '(':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid while  define!\n")
            exit(1)
        
        # parse expression
        self.compileExpression()

        # parse  ')'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ')':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid while  define!\n")
            exit(1)

        # parse  '{'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == '{':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid while  define!\n")
            exit(1)
        
        # parse statements
        self.compileStatements()

        # parse  '}'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == '}':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("inValid while  define!\n")
            exit(1)

        self.upperLevel()
        self.compileOut("</whileStatement>\n")
        return True
    
    def compileReturn(self):
        self.compileOut("<returnStatement>\n")
        self.lowerLevel()

        # parse return 
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "return":
            self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
            self.parser.advance()
        else:
            print("valid if return statement!\n")
            exit(1)

        # parse expression  list
        if not (self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ';'):
            self.compileExpression()
        
        # parse ';'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ';':
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("valid if return statement!\n")
            exit(1)

        self.upperLevel()
        self.compileOut("</returnStatement>\n")
        return True
    
    def compileIf(self):
        self.compileOut("<ifStatement>\n")
        self.lowerLevel()

        # parse if 
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "if":
            self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
            self.parser.advance()
        else:
            print("valid if define!\n")
            exit(1)

        # parse '('
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "(":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("valid if define!\n")
            exit(1)
        
        # parse expression
        self.compileExpression()
        
        # parse ')'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == ")":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("valid if define!\n")
            exit(1)
        
        # parse '{'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "{":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("valid if define!\n")
            exit(1)

        # parse statements
        self.compileStatements()

        # parse '}'
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           self.parser.symbol() == "}":
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
        else:
            print("valid if define!\n")
            exit(1)
        
        # parse else
        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD and \
           self.parser.keyWord() == "else":
            # parse 'else'
            self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
            self.parser.advance()
            
            # parse '{'
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
            self.parser.symbol() == "{":
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()
            else:
                print("valid if define!\n")
                exit(1)

            # parse statements
            self.compileStatements()
            
            # parse '}'
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
            self.parser.symbol() == "}":
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()
            else:
                print("valid if define!\n")
                exit(1)

        self.upperLevel()
        self.compileOut("</ifStatement>\n")
        return
    
    def compileExpression(self):
        self.compileOut("<expression>\n")
        self.lowerLevel()

        # parse term
        self.compileTerm()

        # parse op
        while self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
           (self.parser.symbol() == "+" or self.parser.symbol() == "-" or \
            self.parser.symbol() == "*" or self.parser.symbol() == "/" or \
            self.parser.symbol() == "&" or self.parser.symbol() == "|" or \
            self.parser.symbol() == ">" or self.parser.symbol() == "<" or \
            self.parser.symbol() == "="):
            # parse op
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()

            # parse term
            self.compileTerm()
        
        self.upperLevel()
        self.compileOut("</expression>\n")
        return
    
    def compileTerm(self):
        self.compileOut("<term>\n")
        self.lowerLevel()

        if self.parser.tokenType() == TOKEN_TYPE.TOKEN_INT_CONST:
            # parse int const
            self.compileOutElement(self.parser.tokenType(),self.parser.intVal())
            self.parser.advance()
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_STRING_CONST:
            # parse string const
            self.compileOutElement(self.parser.tokenType(),self.parser.stringVal())
            self.parser.advance()
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_KEYWORD:
            # parse keword const
            if self.parser.keyWord() == "true" or self.parser.keyWord() == "false" or \
               self.parser.keyWord() == "null" or self.parser.keyWord() == "this":
                self.compileOutElement(self.parser.tokenType(),self.parser.keyWord())
                self.parser.advance()
            else:
                print("inValid expression define!\n")
                exit(1)
        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
            if self.parser.symbol() == "(":
                # parse '('
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()
                # parse expression
                self.compileExpression()
                # parse ')'
                if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
                   self.parser.symbol() == ")":
                    self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                    self.parser.advance()
                else:
                    print("valid term define!\n")
                    exit(1)

            elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and \
                (self.parser.symbol() == "-" or self.parser.symbol() == "~"):
                # parse unaryOp
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()
                # parse term
                self.compileTerm()
            else:
                print("valid term define!\n")
                exit(1)

        elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
            # parse subroutineName or varName
            self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
            self.parser.advance()

            # parse expression
            if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "[":
                # parse '['
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()
                # parse expression
                self.compileExpression()
                # parse ']'
                if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "]":
                    self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                    self.parser.advance()
                else:
                    print("valid term define!\n")
                    exit(1)
            elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ".":
                # parse '.'
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()

                # parse subroutineName
                if self.parser.tokenType() == TOKEN_TYPE.TOKEN_IDENTIFIER:
                    self.compileOutElement(self.parser.tokenType(),self.parser.currToken())
                    self.parser.advance()
                else:
                    print("valid term define!\n")
                    exit(1)

                # parse '('
                if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "(":
                    self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                    self.parser.advance()
                else:
                    print("valid term define!\n")
                    exit(1)

                # parse expressList
                self.compileExpressionList()

                # parse ')'
                if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ")":
                    self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                    self.parser.advance()
                else:
                    print("valid term define!\n")
                    exit(1)
            elif self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == "(":
                self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                self.parser.advance()

                # parse expressList
                self.compileExpressionList()

                # parse ')'
                if self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL and self.parser.symbol() == ")":
                    self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
                    self.parser.advance()
                else:
                    print("valid term define!\n")
                    exit(1)

        self.upperLevel()
        self.compileOut("</term>\n")
        return True
    
    def compileExpressionList(self):
        self.compileOut("<expressionList>\n")
        self.lowerLevel()

        if self.parser.symbol() == ')' and \
           self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
            self.upperLevel()
            self.compileOut("</expressionList>\n")
            return True

        # parse expression
        self.compileExpression()

        # parse `, expression`
        while self.parser.symbol() == ',' and \
              self.parser.tokenType() == TOKEN_TYPE.TOKEN_SYMBOL:
            # parse ','
            self.compileOutElement(self.parser.tokenType(),self.parser.symbol())
            self.parser.advance()
            # parse expression
            self.compileExpression()

        self.upperLevel()
        self.compileOut("</expressionList>\n")
        return

def main(input):
    parser = CompilationEngine(input)

if __name__ == "__main__":
    main(sys.argv[1])