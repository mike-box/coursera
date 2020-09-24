// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// eq
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@StackTest.0.TRUE
D;JEQ
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.0.TRUE)
@SP
M=M-1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// eq
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@StackTest.1.TRUE
D;JEQ
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.1.TRUE)
@SP
M=M-1

// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// eq
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@StackTest.2.TRUE
D;JEQ
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.2.TRUE)
@SP
M=M-1

// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
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
@StackTest.3.TRUE
D;JLT
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.3.TRUE)
@SP
M=M-1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 892
@892
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
@StackTest.4.TRUE
D;JLT
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.4.TRUE)
@SP
M=M-1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
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
@StackTest.5.TRUE
D;JLT
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.5.TRUE)
@SP
M=M-1

// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// gt
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@StackTest.6.TRUE
D;JGT
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.6.TRUE)
@SP
M=M-1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

// gt
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@StackTest.7.TRUE
D;JGT
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.7.TRUE)
@SP
M=M-1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// gt
@SP
A=M
A=A-1
D=M
A=A-1
MD=M-D
M=-1
@StackTest.8.TRUE
D;JGT
@SP
A=M
A=A-1
A=A-1
M=0
(StackTest.8.TRUE)
@SP
M=M-1

// push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 53
@53
D=A
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

// push constant 112
@112
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

// neg
@SP
A=M
A=A-1
D=M
M=-D

// and
@SP
A=M
A=A-1
D=M
A=A-1
M=D&M
@SP
M=M-1

// push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1

// or
@SP
A=M
A=A-1
D=M
A=A-1
M=D|M
@SP
M=M-1

// not
@SP
A=M
A=A-1
D=M
M=!D

