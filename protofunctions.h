#ifndef PROTOFUNCTIONS_H_
#define PROTOFUNCTIONS_H_



/* Prototyp Funktionen */
/**braucht man nur in der C datei nicht im header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
**/
typedef enum { false, true } bool;

extern int version ; /* The current version */
extern int *staticPtr; /* Lists all global Variables */
extern int calculationStack[]; /* Stack for Calculation */
extern int sp; /* Stack Pointer Variable for Calculations */
extern int fp;
extern int regADD;
extern int staticAreaSize;
extern int instructionCount;
extern bool haltThis;
extern bool debugMode;
extern unsigned int *programMemory; /* List of all Program Instructions */
extern int pc; /* Program Counter Variable for Instructions */

void haltProgram (void);
void push (int);
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
void asf (int);
void rsf ();
void pushl (int);
void popl (int);
void eq (void);
void ne (void);
void lt (void);
void le (void);
void gt (void);
void ge (void);
void jmp (int);
void brf (int);
void brt (int);
void call (int);
void ret (void);
void drop (int);
void pushr (void);
void popr (void);
void debugInstructions(unsigned int);
void matchInstruction(unsigned int);
void debugger(int);


#endif