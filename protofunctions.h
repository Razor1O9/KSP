#ifndef PROTOFUNCTIONS_H_
#define PROTOFUNCTIONS_H_

// is this object a primitve object?
# define MSB                (1 << (8 * sizeof ( unsigned int) - 1))
# define IS_PRIM(objRef)  (((objRef)->size & MSB) == 0)


#define GET_SIZE(objRef) ((objRef)->size & ~MSB)

#define GET_REFS(objRef) ((ObjRef *)(objRef)->data)

/* Prototyp Funktionen */
typedef enum { false, true } bool;

typedef struct {
    unsigned int size; /* byte count of payload data */
    unsigned char data [1]; /* payload data , size as needed */
} *ObjRef;

typedef struct {
    bool isObjRef; /* slot used for object reference? */
    union {
        ObjRef objRef; /* used if isObjRef=TRUE */
        int *number; /* used if isObjRef=FALSE */
    } u;
} StackSlot;

extern int version ; /* The current version */
extern int *staticPtr; /* Lists all global Variables */
extern StackSlot calculationStack[]; /* Stack for Calculation */
extern int sp; /* Stack Pointer Variable for Calculations */
extern int fp;
extern int regADD;
extern int staticAreaSize;
extern int instructionCount;
extern bool haltThis;
extern bool debugMode;
extern bool breakpoint;
extern int breakpoint_pos;
extern unsigned int *programMemory; /* List of all Program Instructions */
extern int pc; /* Program Counter Variable for Instructions */
extern int dc; /* Program Counter Variable for Debugging */

void haltProgram (void);
void push (void*);
void *pop (void);
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
