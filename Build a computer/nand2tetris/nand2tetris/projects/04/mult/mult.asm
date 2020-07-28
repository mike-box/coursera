// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// created by mike meng @ 2020.7.28
// Put your code here.
    @0
    D=A
    @R2
    M=D //set R2 to zero

(LOOP)
    @R1
    D=M
    @END
    D;JEQ // we first need to test if R1 is zero.
    @R0
    D=M
    @R2
    M=M+D // we add R0 once .
    @R1
    M=M-1 // we dec R1 one time.
    @LOOP
    0;JMP

(END)
    @END
    0;JMP


