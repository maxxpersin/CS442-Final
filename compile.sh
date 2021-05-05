#!/bin/sh

echo Compiling in1

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp tests/in/in1 listing out.asm

echo Executing in1
spim run out.asm > tests/out/in1.txt

echo Compiling in2

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp tests/in/in2 listing out.asm

echo Executing in2
spim run out.asm > tests/out/in2.txt


echo Compiling in3

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp tests/in/in3 listing out.asm

echo Executing in3
spim run out.asm > tests/out/in3.txt


echo Compiling in4

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp tests/in/in4 listing out.asm

echo Executing in4
spim run out.asm > tests/out/in4.txt


echo Compiling in5

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp tests/in/in5 listing out.asm

echo Executing in5
spim run out.asm > tests/out/in5.txt


echo Compiling in6

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp tests/in/in6 listing out.asm

echo Executing in6
spim run out.asm > tests/out/in6.txt