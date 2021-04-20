# CS442-Final
Final Project for CS442

# Compilation and Execution
```
$ yacc -d ExprEval.y
```
```
$ lex lex1.l
```
```
$ cc -o comp lex.yy.c y.tab.c SymTab.c Semantics.c CodeGen.c IOMngr.c main.c
```
```
$ ./comp <file to compile> <error output file> <compilation output file>
```
```
$ spim run <asm file>
```

# Alternative Execution
In the terminal, run
```
$ ./compile.sh
```
To compile and execute with the input program set as in1.txt