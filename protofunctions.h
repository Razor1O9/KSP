#ifndef PROTOFUNCTIONS_H_
#define PROTOFUNCTIONS_H_

/* Prototyp Funktionen */
typedef enum { false, true } bool;

typedef struct {
    unsigned int size;	/* byte count of payload data */
    unsigned char data [1]; /* payload data , size as needed */
} *ObjRef;

typedef struct {
    unsigned int isObjRef;
    union {
        ObjRef objRef;
        int number;
    } u;
} Stackslot;

extern int version ; /* The current version */
extern int *staticPtr; /* Lists all global Variables */
extern Stackslot calculationStack[]; /* Stack for Calculation */
extern int sp; /* Stack Pointer Variable for Calculations */
extern int fp;
extern Stackslot regADD;
extern Stackslot staticAreaSize;
extern int instructionCount;
extern bool haltThis;
extern bool debugMode;
extern bool breakpoint;
extern int breakpoint_pos;
extern unsigned int *programMemory; /* List of all Program Instructions */
extern int pc; /* Program Counter Variable for Instructions */
extern int dc; /* Program Counter Variable for Debugging */

void haltProgram (void);
void push (int);
Stackslot pop (void);
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
