#!/bin/sh

yacc -d ExprEval.y 
lex lex1.l
cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
./comp in6 listing out.asm
spim run out.asm