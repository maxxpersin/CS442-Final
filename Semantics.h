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
extern struct InstrSeq *doPrint(struct ExprRes *Expr);
extern struct BExprRes *doBExpr(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct BExprRes *doBExprNotEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct BExprRes *doBExprLtOrEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct BExprRes *doBExprGtOrEq(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct BExprRes *doBExprLt(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct BExprRes *doBExprGt(struct ExprRes *Res1, struct ExprRes *Res2);
extern struct BExprRes *doNegate(struct BExprRes *Res1);
extern struct InstrSeq *doIf(struct BExprRes *bRes, struct InstrSeq *seq);

extern void Finish(struct InstrSeq *Code);
