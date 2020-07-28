// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
// Created by mike meng,Date : 2020.7.28

(LISTEN)
    @0       //set r0 to zero
    D=A 
    @R0
    M=D
    @8192    //set r1 to max size 8192
    D=A 
    @R1
    M=D
    @SCREEN  //set screen start address
    D=A
    @screenaddr
    M=D
    @KBD     // listen to the keyboard register
    D=M
    @FILL
    D;JGT

(FLUSH)
    @0      //set r2 to 0
    D=A 
    @R2 
    M=D
    @LOOP
    0;JMP

(FILL)
    D=-1     //set r2 to -1 
    @R2 
    M=D
    
(LOOP)
    @R0
    D=M
    @R1
    D=D-M
    @LISTEN
    D;JGE
    @R2
    D=M
    @screenaddr
    A=M
    M=D // set addres to -1 or 0;
    @R0
    M=M+1
    @screenaddr
    M=M+1
    @LOOP
    0;JMP

(END)
    @END // program’s end
    0;JMP // infiniteD loop