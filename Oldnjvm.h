#include "bigint/bigint.h"

/* Define Arguments */

#define ARG_VERSION "--version"
#define ARG_HELP "--help"
#define DEBUG_MODE "--debug"
#define ARG_STACK_SIZE "--stack"

/* #define IMMEDIATE(x) ((x) & 0x00FFFFFF) */
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))
#define MSB (1 << (8 * sizeof(unsigned int) - 1))
#define IS_PRIM(objRef) (((objRef)->size & MSB) == 0)
#define GET_SIZE(objRef) ((objRef)->size & ~MSB)
#define GET_REFS(objRef) ((ObjRef *)(objRef)->data)

/* VM Version Info */
#define NJVM_VERSION 8

/* stack size*/
#define STACK_SIZE 64

/*make boolean type */
typedef int bool;
#define true 1
#define false 0

typedef struct {
    bool isObjRef;
    union
    {
        ObjRef objRef;
        int number;
    } u;
} StackSlot;

typedef struct {
    ObjRef this[STACK_SIZE];
    int size;
} ReturnRegister;

#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10
#define PUSHG 11
#define POPG 12
#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16
#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22
#define JMP 23
#define BRF 24
#define BRT 25
#define CALL 26
#define RET  27
#define DROP 28
#define PUSHR 29
#define POPR 30
#define DUP 31
#define NEW 32
#define GETF 33
#define PUTF 34
#define NEWA 35
#define GETFA 36
#define PUTFA 37
#define GETSZ 38
#define PUSHN 39
#define REFEQ 40
#define REFNE 41



void printHelp(void);
void loadProgram(const char filename[], int debug);
void listProgram(unsigned int prog [], int instrSize);
void executeProgram(unsigned int instructions [], int staticDataArea_size);
void execInstruction(unsigned int instruction_binary, int staticDataArea_size);
void listInstruction(unsigned int instruction);
void makeDebugStep(unsigned int instructions [], int staticDataArea_size, long int steps);
int immediate_value(unsigned int binary);
void push(StackSlot slot);
ObjRef popObjRef();
int popNumber();
ObjRef newCompoundObject(int objRefSize);