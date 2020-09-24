// function Sys.init 0
(Sys.init)
@0
D=A
@Sys.init.LOCAL.end
D;JEQ
(Sys.init.LOCAL.start)
@SP
A=M
M=0
@SP
M=M+1
D=D-1
@Sys.init.LOCAL.start
D;JNE
(Sys.init.LOCAL.end)

// push constant 4
@4
D=A
@SP
A=M
M=D
@SP
M=M+1

// call Main.fibonacci 1
@Main.fibonacci.RETURN.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci.RETURN.0)

// label WHILE
(Sys.init$WHILE)

// goto WHILE
@Sys.init$WHILE
0;JMP

