// sys init 
@256
D=A
@SP
M=D
@Sys.init.RETURN.0
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
@0
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(Sys.init.RETURN.0)

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

// push constant 4000	
@4000
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 0
@0
D=A
@3
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

// push constant 5000
@5000
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 1
@1
D=A
@3
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

// call Sys.main 0
@Sys.main.RETURN.1
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
@0
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.main
0;JMP
(Sys.main.RETURN.1)

// pop temp 1
@1
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

// label LOOP
(Sys.init$LOOP)

// goto LOOP
@Sys.init$LOOP
0;JMP

// function Sys.main 5
(Sys.main)
@5
D=A
@Sys.main.LOCAL.end
D;JEQ
(Sys.main.LOCAL.start)
@SP
A=M
M=0
@SP
M=M+1
D=D-1
@Sys.main.LOCAL.start
D;JNE
(Sys.main.LOCAL.end)

// push constant 4001
@4001
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 0
@0
D=A
@3
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

// push constant 5001
@5001
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 1
@1
D=A
@3
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

// push constant 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 1
@1
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

// push constant 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 2
@2
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

// push constant 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 3
@3
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

// push constant 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1

// call Sys.add12 1
@Sys.add12.RETURN.2
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
@Sys.add12
0;JMP
(Sys.add12.RETURN.2)

// pop temp 0
@0
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

// push local 1
@1
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push local 2
@2
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push local 3
@3
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push local 4
@4
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

// add
@SP
A=M
A=A-1
D=M
A=A-1
M=M+D
@SP
M=M-1

// add
@SP
A=M
A=A-1
D=M
A=A-1
M=M+D
@SP
M=M-1

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
@5
D=D-A
A=D
D=M
@R13
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
@R13
A=M
0;JMP

// function Sys.add12 0
(Sys.add12)
@0
D=A
@Sys.add12.LOCAL.end
D;JEQ
(Sys.add12.LOCAL.start)
@SP
A=M
M=0
@SP
M=M+1
D=D-1
@Sys.add12.LOCAL.start
D;JNE
(Sys.add12.LOCAL.end)

// push constant 4002
@4002
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 0
@0
D=A
@3
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

// push constant 5002
@5002
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 1
@1
D=A
@3
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

// push constant 12
@12
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

// return
@LCL
D=M
@5
D=D-A
A=D
D=M
@R13
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
@R13
A=M
0;JMP


