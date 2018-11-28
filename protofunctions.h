/* Prototyp Funktionen */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum { false, true } bool;

extern int version; /* The current version */

extern int *staticPtr; /* Lists all global Variables */
extern int calculationStack[9999]; /* Stack for Calculation */
extern int sp; /* Stack Pointer Variable for Calculations */
extern int fp;
extern int regADD;
extern int staticAreaSize;
extern int instructionCount;
extern int staticVar;
extern bool haltThis;
extern bool debugMode;
extern unsigned int programMemory[9999]; /* List of all Program Instructions */
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
void pushg (int value);
void popg (int value);
void asf (int value);
void rsf ();
void pushl (int value);
void popl (int value);
void eq (void);
void ne (void);
void lt (void);
void le (void);
void gt (void);
void ge (void);
void jmp (int value);
void brf (int value);
void brt (int value);
void call (int value);
void ret (void);
void drop (int value);
void pushr (void);
void popr (void);
void debugInstructions(void);
void matchInstruction(int pc);
void debugger(void);
