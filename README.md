# CS442-Final Maxx Persin
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
To compile and execute all programs within tests/in/, output is directed to .txt files in tests/out/

# Feature Areas Completed

## Integer Expressions
Test files include in1, in2, in3, in4. However, arithmatic statements can be found in all other test files.

### in1 Output
```
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
10201020-999-1000

```

### in3 Output
```
02346
```

### in4 Output
```
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
# Other Tests
## These tests are contained in tests/test1/ 
## t1.c - t7.c have been translated to my language

### t1.c Output
```
27
-13
140
2
6
6
49
```

### t2.c Output
```
19
4
1
262144
```

### t3.c Output
```
9
8
7
6
98763013270531159839239        9876
```

### t4.c Output
```
0
5
1
0-17255
1-17256
2-16256
3-16257
4-15257
5-15258
```

### t5.c Output
```
0
5
1
0-17255
1-17256
2-16256
3-16257
4-15257
5-15258
```

### t6.c Output
```
4
9 
2
4
249
1
0
2
012
-1
3
5
-135
2
4
5
245
```

### t7.c Output
```
6
1
2
3
123
1
3
2
123
2
1
3
123
2
3
1
123
3
1
2
123
3
2
1
123
```