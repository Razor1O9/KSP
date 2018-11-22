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
void debugInstructions(void);
void matchInstruction(void);

