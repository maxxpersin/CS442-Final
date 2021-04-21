/* Semantics.h
   The action and supporting routines for performing semantics processing.
*/

/* Semantic Records */
struct IdList
{
  struct SymEntry *TheEntry;
  struct IdList *Next;
};

struct ExprRes
{
  int Reg;
  struct InstrSeq *Instrs;
};

struct ExprResList
{
  struct ExprRes *Expr;
  struct ExprResList *Next;
};

struct BExprRes
{
  char *Label;
  struct InstrSeq *Instrs;
};

struct Node
{
  void *name;
  struct Node *next;
};

/* Semantics Actions */
extern struct ExprRes *doIntLit(char *digits);
extern struct ExprRes *doIntLitNeg(char *digits);
extern struct ExprRes *doRval(char *name);
extern struct InstrSeq *doAssign(char *name, struct ExprRes *Res1);
extern struct ExprRes *doAdd(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doSubtraction(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doMult(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doDiv(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doExponential(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doModulo(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct InstrSeq *doPrint(struct Node *node);
extern struct InstrSeq *doRead(struct Node *node);
extern struct ExprRes *doBExprEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprNotEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprLtOrEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprGtOrEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprLt(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doBExprGt(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doNegate(struct ExprRes *Res1);
extern struct ExprRes *doOr(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct ExprRes *doAnd(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct InstrSeq *doIf(struct ExprRes *Res, struct InstrSeq *seq);

extern struct Node *appendToArgList(char *c, struct Node *next);
extern struct Node *appendToExprList(struct ExprRes *Res1, struct Node *next);

extern void Finish(struct InstrSeq *Code);
