/* Semantics.c
   Support and semantic action routines.
   
*/

#include <strings.h>
#include <stdlib.h>

#include "CodeGen.h"
#include "Semantics.h"
#include "SymTab.h"
#include "IOMngr.h"

extern SymTab *table;

/* Semantics support routines */

struct ExprRes *doIntLit(char *digits)
{

  struct ExprRes *res;

  res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  res->Reg = AvailTmpReg();
  res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), digits, NULL);

  return res;
}

extern struct ExprRes *doIntLitNeg(char *digits)
{
  struct ExprRes *res;

  res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  res->Reg = AvailTmpReg();
  res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), digits, NULL);
  AppendSeq(res->Instrs, GenInstr(NULL, "mul", TmpRegName(res->Reg), TmpRegName(res->Reg), "-1"));

  return res;
}

struct ExprRes *doRval(char *name)
{

  struct ExprRes *res;

  if (!findName(table, name))
  {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Undeclared variable");
  }
  res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  res->Reg = AvailTmpReg();
  res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);

  return res;
}

struct ExprRes *doAdd(struct ExprRes *Res1, struct ExprRes *Res2)
{

  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "add",
                                   TmpRegName(reg),
                                   TmpRegName(Res1->Reg),
                                   TmpRegName(Res2->Reg)));
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

extern struct ExprRes *doSubtraction(struct ExprRes *Res1, struct ExprRes *Res2)
{
  int reg;
  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  Res1->Reg = reg;
  free(Res2);

  return Res1;
}

struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2)
{

  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "mul",
                                   TmpRegName(reg),
                                   TmpRegName(Res1->Reg),
                                   TmpRegName(Res2->Reg)));
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

struct ExprRes *doDiv(struct ExprRes *Res1, struct ExprRes *Res2)
{
  int reg;

  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "div", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);

  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

// Base stored in Res1->Reg
// Exponent stored in Res2->Reg
// Loop over exponent and create instrs where we multiply base by itself
struct ExprRes *doExponential(struct ExprRes *Res1, struct ExprRes *Res2)
{
  int reg = AvailTmpReg();
  int reg2 = AvailTmpReg();
  int reg3 = AvailTmpReg();
  char *label = GenLabel();
  char *label2 = GenLabel();
  char *label3 = GenLabel();
  AppendSeq(Res1->Instrs, Res2->Instrs);

  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res1->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg2), TmpRegName(Res2->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "move", TmpRegName(reg3), TmpRegName(Res2->Reg), NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg3), TmpRegName(reg3), "1"));

  AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(reg3), label3));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg2), TmpRegName(reg2), "1"));

  AppendSeq(Res1->Instrs, GenInstr(label, NULL, NULL, NULL, NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(reg2), label2));

  AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg), TmpRegName(reg), TmpRegName(Res1->Reg)));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(reg2), TmpRegName(reg2), "1"));

  AppendSeq(Res1->Instrs, GenInstr(NULL, "j", label, NULL, NULL));

  AppendSeq(Res1->Instrs, GenInstr(label3, NULL, NULL, NULL, NULL));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "li", TmpRegName(reg), "1", NULL));

  AppendSeq(Res1->Instrs, GenInstr(label2, NULL, NULL, NULL, NULL));

  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  ReleaseTmpReg(reg2);
  ReleaseTmpReg(reg3);

  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

// Need to do a division, then use mfhi (move from hi) to access the remainder of our operation. This is the modulo.
extern struct ExprRes *doModulo(struct ExprRes *Res1, struct ExprRes *Res2)
{
  int reg;
  reg = AvailTmpReg();
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "div", NULL, TmpRegName(Res1->Reg), TmpRegName(Res2->Reg))); // We dont care about the quotient
  AppendSeq(Res1->Instrs, GenInstr(NULL, "mfhi", TmpRegName(reg), NULL, NULL));

  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);

  Res1->Reg = reg;
  free(Res2);
  return Res1;
}

struct InstrSeq *doPrint(struct Node *node)
{

  struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));

  struct Node *curr = node;
  while (curr)
  {
    struct ExprRes *currInstr = (struct ExprRes *)curr->name;
    AppendSeq(code, currInstr->Instrs);
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "1", NULL));
    AppendSeq(code, GenInstr(NULL, "move", "$a0", TmpRegName(currInstr->Reg), NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

    ReleaseTmpReg(currInstr->Reg);
    free(currInstr);
    curr = curr->next;
  }

  /**
  * this section prints a new line, temporarily removing
  */
  // AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
  // AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
  // AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

  return code;
}

extern struct InstrSeq *doPrintlines(struct ExprRes *Res)
{
  struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));
  int reg = AvailTmpReg();
  AppendSeq(code, Res->Instrs);
  AppendSeq(code, GenInstr(NULL, "move", TmpRegName(reg), TmpRegName(Res->Reg), NULL));

  char *label = GenLabel();
  AppendSeq(code, GenInstr(label, NULL, NULL, NULL, NULL)); // Label to jump back to, based on amount of new lines desired;

  AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
  AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
  AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));

  AppendSeq(code, GenInstr(NULL, "sub", TmpRegName(reg), TmpRegName(reg), "1"));
  AppendSeq(code, GenInstr(NULL, "bne", "$zero", TmpRegName(reg), label));

  ReleaseTmpReg(reg);
  ReleaseTmpReg(Res->Reg);

  free(Res);

  return code;
}

extern struct InstrSeq *doRead(struct Node *node)
{
  struct InstrSeq *code = (struct InstrSeq *)malloc(sizeof(struct InstrSeq));

  struct Node *curr = node;
  while (curr)
  {
    AppendSeq(code, GenInstr(NULL, "li", "$v0", "5", NULL));
    AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
    AppendSeq(code, GenInstr(NULL, "sw", "$v0", (char *)curr->name, NULL));

    curr = curr->next;
  }

  return code;
}

struct InstrSeq *doAssign(char *name, struct ExprRes *Expr)
{

  struct InstrSeq *code;

  if (!findName(table, name))
  {
    writeIndicator(getCurrentColumnNum());
    writeMessage("Undeclared variable");
  }

  code = Expr->Instrs;

  AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));

  ReleaseTmpReg(Expr->Reg);
  free(Expr);

  return code;
}

extern struct ExprRes *doBExprEq(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "seq", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doBExprNotEq(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sne", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doBExprLtOrEq(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sle", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doBExprGtOrEq(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sge", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doBExprLt(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "slt", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doBExprGt(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  AppendSeq(Res1->Instrs, Res2->Instrs);
  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sgt", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doNegate(struct ExprRes *Res1)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "not", TmpRegName(reg), TmpRegName(Res1->Reg), NULL));

  // This next bit should (ideally) clear all of our garbage bits
  // I hate mips
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(reg), TmpRegName(reg), "31"));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "srl", TmpRegName(reg), TmpRegName(reg), "31"));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  free(Res1);
  return Res;
}

extern struct ExprRes *doOr(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "or", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(reg), TmpRegName(reg), "31"));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "srl", TmpRegName(reg), TmpRegName(reg), "31"));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct ExprRes *doAnd(struct ExprRes *Res1, struct ExprRes *Res2)
{
  struct ExprRes *Res;
  int reg = AvailTmpReg();

  Res = (struct ExprRes *)malloc(sizeof(struct ExprRes));
  AppendSeq(Res1->Instrs, Res2->Instrs);
  AppendSeq(Res1->Instrs, GenInstr(NULL, "and", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));

  // I'm leaving this here in case I find out I need to do this in the future
  AppendSeq(Res1->Instrs, GenInstr(NULL, "sll", TmpRegName(reg), TmpRegName(reg), "31"));
  AppendSeq(Res1->Instrs, GenInstr(NULL, "srl", TmpRegName(reg), TmpRegName(reg), "31"));

  Res->Reg = reg;
  Res->Instrs = Res1->Instrs;
  ReleaseTmpReg(Res1->Reg);
  ReleaseTmpReg(Res2->Reg);
  free(Res1);
  free(Res2);
  return Res;
}

extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq)
{
  struct InstrSeq *seq2;
  char *label = GenLabel();
  AppendSeq(Res->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res->Reg), label));
  seq2 = AppendSeq(Res->Instrs, seq);
  AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));
  free(Res);
  return seq2;
}

extern struct Node *appendToArgList(char *c, struct Node *next)
{
  struct Node *curr = (struct Node *)malloc(sizeof(struct Node));

  curr->name = strdup(c);
  curr->next = next;

  return curr;
}

extern struct Node *appendToExprList(struct ExprRes *Res1, struct Node *next)
{
  struct Node *curr = (struct Node *)malloc(sizeof(struct Node));

  curr->name = Res1;
  curr->next = next;

  return curr;
}

/*

extern struct InstrSeq * doIf(struct ExprRes *res1, struct ExprRes *res2, struct InstrSeq * seq) {
	struct InstrSeq *seq2;
	char * label;
	label = GenLabel();
	AppendSeq(res1->Instrs, res2->Instrs);
	AppendSeq(res1->Instrs, GenInstr(NULL, "bne", TmpRegName(res1->Reg), TmpRegName(res2->Reg), label));
	seq2 = AppendSeq(res1->Instrs, seq);
	AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));
	ReleaseTmpReg(res1->Reg);
  	ReleaseTmpReg(res2->Reg);
	free(res1);
	free(res2);
	return seq2;
}

*/
void Finish(struct InstrSeq *Code)
{
  struct InstrSeq *code;
  //struct SymEntry *entry;
  int hasMore;
  struct Attr *attr;

  code = GenInstr(NULL, ".text", NULL, NULL, NULL);
  //AppendSeq(code,GenInstr(NULL,".align","2",NULL,NULL));
  AppendSeq(code, GenInstr(NULL, ".globl", "main", NULL, NULL));
  AppendSeq(code, GenInstr("main", NULL, NULL, NULL, NULL));
  AppendSeq(code, Code);
  AppendSeq(code, GenInstr(NULL, "li", "$v0", "10", NULL));
  AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
  AppendSeq(code, GenInstr(NULL, ".data", NULL, NULL, NULL));
  AppendSeq(code, GenInstr(NULL, ".align", "4", NULL, NULL));
  AppendSeq(code, GenInstr("_nl", ".asciiz", "\"\\n\"", NULL, NULL));

  hasMore = startIterator(table);
  while (hasMore)
  {
    AppendSeq(code, GenInstr((char *)getCurrentName(table), ".word", "0", NULL, NULL));
    hasMore = nextEntry(table);
  }

  WriteSeq(code);

  return;
}
