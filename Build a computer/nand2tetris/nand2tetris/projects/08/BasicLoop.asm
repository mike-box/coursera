// push constant 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 0
@0
D=A
@LCL
AD=M+D
@R13
M=D
@SP
A=M
A=A-1
D=M
@R13
A=M
M=D
@SP
M=M-1
// label LOOP_START
($LOOP_START)
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
// push local 0
@0
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
A=M
A=A-1
D=M
A=A-1
M=M+D
@SP
M=M-1
// pop local 0	
@0
D=A
@LCL
AD=M+D
@R13
M=D
@SP
A=M
A=A-1
D=M
@R13
A=M
M=D
@SP
M=M-1
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
// pop argument 0
@0
D=A
@ARG
AD=M+D
@R13
M=D
@SP
A=M
A=A-1
D=M
@R13
A=M
M=D
@SP
M=M-1
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
// if-goto LOOP_START
@SP
A=M
A=A-1
D=M
@SP
M=M-1
@$LOOP_START
D;JNE
// push local 0
@0
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

