// push constant 10
@10
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

// push constant 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop argument 2
@2
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

// pop argument 1
@1
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

// push constant 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop this 6
@6
D=A
@THIS
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

// push constant 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop that 5
@5
D=A
@THAT
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

// pop that 2
@2
D=A
@THAT
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

// push constant 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop temp 6
@6
D=A
@5
D=A+D
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

// push that 5
@5
D=A
@THAT
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

// push argument 1
@1
D=A
@ARG
A=M+D
D=M
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

// push this 6
@6
D=A
@THIS
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push this 6
@6
D=A
@THIS
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

// sub
@SP
A=M
A=A-1
D=M
A=A-1
M=M-D
@SP
M=M-1

// push temp 6
@6
D=A
@5
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

