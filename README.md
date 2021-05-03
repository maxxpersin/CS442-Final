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
To compile and execute with the input program set as tests/in/in1 and default output to tests/out/in1.txt

# Feature Areas Completed

### First line of all outputs are appended by spim and can be ignored

## Integer Expressions
Test files include in1, in2, in3, in4. However, arithmatic statements can be found in all other test files.

### in1 Output
```
Loaded: /usr/local/Cellar/spim/9.1.22/share/exceptions.s
20
0
1
-1162261467
1
0
1
0
```
### in2 Output
```
Loaded: /usr/local/Cellar/spim/9.1.22/share/exceptions.s
10201020-999-1000

```

### in3 Output
```
Loaded: /usr/local/Cellar/spim/9.1.22/share/exceptions.s
02346
```

### in4 Output
```
Loaded: /usr/local/Cellar/spim/9.1.22/share/exceptions.s
109
```

## Integer I/O
Test files include in5 and in6. The bulk of testing was done with in5, in6 output will be shown later.

### in5 Output
#### With input given in order as
```
99
10
-1
2
```
Output
```
Loaded: /usr/local/Cellar/spim/9.1.22/share/exceptions.s
9910-1
-100100254




5
8 18                  
```

## Control Structures
Test files incldue in6.

### in6 Output
### With input given as
```
4
```
Output
```
Loaded: /usr/local/Cellar/spim/9.1.22/share/exceptions.s
14321
0
1
2
3
4
5
9
10

```