/* Prototyp Funktionen */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum { false, true } bool;

extern int version; /* The current version */


extern int calculationStack[9999]; /* Stack for Calculation */
extern int sp; /* Stack Pointer Variable for Calculations */

extern int staticAreaSize;
extern int instructionCount;
extern int programSize;
extern int staticVar;
extern char letter; /* character */
extern bool haltThis;
extern bool debugMode;
extern int programMemory[9999]; /* List of all Program Instructions */
extern int globalVars[9999]; /* Lists all global Variables */
extern int pc; /* Program Counter Variable for Instructions */

void haltProgram (void);
void push (int value);
int pop (void);
void add (void);
void sub (void);
void mul (void);
void divide (void);
void mod (void);
void rdint (void);
void wrint (void);
void rdchr (void);
void wrchr (void);
void pushg (int);
void popg (int);
void asf (void);
void rsf (void);
void pushl (void);
void popl (void);
void EQ (void);
void NE (void);
void LT (void);
void LE (void);
void GT (void);
void GE (void);
void JMP (void);
void BRF (void);
void BRT (void);
void CALL(void);
void RET (void);
void DROP (void);
void PUSHR (void);
void POPR (void);
void DUP (void);
void debugInstructions(void);
void matchInstruction(void);
