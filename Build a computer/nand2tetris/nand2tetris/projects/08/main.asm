// function Main.fibonacci 0
(Main.fibonacci)
@0
D=A
@Main.fibonacci.LOCAL.end
D;JEQ
(Main.fibonacci.LOCAL.start)
@SP
A=M
M=0
@SP
M=M+1
D=D-1
@Main.fibonacci.LOCAL.start
D;JNE
(Main.fibonacci.LOCAL.end)

// push argument 0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1

// lt
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@Main.0.TRUE
D;JLT
@SP
A=M
A=A-1
A=A-1
M=0
(Main.0.TRUE)
@SP
M=M-1

// if-goto IF_TRUE
@SP
A=M
A=A-1
D=M
@SP
M=M-1
@Main.fibonacci$IF_TRUE
D;JNE

// goto IF_FALSE
@Main.fibonacci$IF_FALSE
0;JMP

// label IF_TRUE
(Main.fibonacci$IF_TRUE)

// push argument 0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// return
@LCL
D=M
@R6
M=D
@5
D=D-A
A=D
D=M
@R5
M=D
@SP
A=M
A=A-1
D=M
@SP
M=M-1
@ARG
A=M
M=D
@ARG
D=M
D=D+1
@SP
M=D
@LCL
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@R5
A=M
0;JMP

// label IF_FALSE
(Main.fibonacci$IF_FALSE)

// push argument 0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1

// sub
@SP
A=M
A=A-1
D=M
A=A-1
M=M-D
@SP
M=M-1

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

// push argument 0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// sub
@SP
A=M
A=A-1
D=M
A=A-1
M=M-D
@SP
M=M-1

// call Main.fibonacci 1
@Main.fibonacci.RETURN.1
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
(Main.fibonacci.RETURN.1)

// add
@SP
A=M
A=A-1
D=M
A=A-1
M=M+D
@SP
M=M-1

// return
@LCL
D=M
@R6
M=D
@5
D=D-A
A=D
D=M
@R5
M=D
@SP
A=M
A=A-1
D=M
@SP
M=M-1
@ARG
A=M
M=D
@ARG
D=M
D=D+1
@SP
M=D
@LCL
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@R5
A=M
0;JMP

