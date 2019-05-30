/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "protofunctions.h"

/* Makro-Deklarationen */
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

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define OPCODE(i) ((i) & 0xFF000000)
/* 0x00800000 -> 8 checks the sign (+ or -) */
/* 0xFF000000 -> Fills the OpCode with 1 */
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

int version;
int calculationStack[1000];
int sp;
bool haltThis = false;
bool debugMode = false;
unsigned int *programMemory;

int instructionCount = 0;
unsigned int instr;
int pc = 0;
int staticAreaSize = 0;
int *staticPtr;


/**
 * Main Function, which reads all Terminal Arguments
 * Valid Arguments start more specific VM functions
 * @param argcount
 * @param argvector
 * @return
 */
int main(int argc, char *argv[]) {
    int reader = 0;
    char bin[] = ".bin";
    char debug[] = "--debug";
    FILE *loadedFile = NULL;
    char validBinFile[5];
    unsigned int programHeader[3];
    printf("Ninja Virtual Machine started\n");

    /* Prints the current VM-Version */
    if (!strcmp(argv[1], "--version")) {
        printf("Version = %d \n", version);
        printf("\nNinja Virtual Machine stopped\n");
        return (EXIT_SUCCESS);
    }
    /* Prints all valid shell commands */
    if (!strcmp(argv[1], "--help")) {
        printf("Valid inputs: \n [1] --version \n [2] --help \n [3] 'programname'.bin \n [4] --debug 'programname'.bin \n [5] 'programname.bin' --debug");
        printf("\nNinja Virtual Machine stopped\n");
        return (EXIT_SUCCESS);
    }
    /* Searches the arguments for a binary file" */
    if (argc == 2) {
        if (strstr(argv[1], bin) == NULL) {
            printf("\nNot a binary file\n");
            return (EXIT_FAILURE);
        } else {
            loadedFile = fopen(argv[1], "r");
        }
        if (!loadedFile) {
            printf("Error: Code file '%s' cannot be opened \n", argv[1]);
        }
        while (!haltThis) {
            instr = programMemory[pc];
            matchInstruction(instr);
            printf("%d ", calculationStack[fp]);
        }
    } else if (argc == 3) {
        if (strstr(argv[1], debug) != NULL) {
            debugMode = true;
        } else if (strstr(argv[2], debug) != NULL) {
            debugMode = true;
        }
        if (strstr(argv[1], bin) != NULL) {
            loadedFile = fopen(argv[1], "rb");
        } else if (strstr(argv[2], bin) != NULL) {
            loadedFile = fopen(argv[2], "rb");
        }
        if (!loadedFile) {
            printf("Error: Code file '%s' cannot be opened \n", argv[1]);
        }

        /* Checks if the binary file is a valid Ninja-Binary file */
        fread(&validBinFile[reader], sizeof(char), 4, loadedFile);
        if (strncmp(&validBinFile[0], "N", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[1], "J", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[2], "B", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[3], "F", 1) != 0) {
            haltProgram();

        }

        /* Reads the File VM-version */
        fread(&programHeader[0], sizeof(unsigned int), 1, loadedFile);
        if (version < programHeader[0]) {
            printf("Version: %d is not supported!", programHeader[0]);
            return (EXIT_FAILURE);
        }
        /* Reads the amount of instructions inside the File */
        fread(&programHeader[1], sizeof(unsigned int), 1, loadedFile);
        instructionCount = programHeader[1];

        /* Reads the amount of global variables inside the File */
        fread(&programHeader[2], sizeof(unsigned int), 1, loadedFile);
        staticAreaSize = programHeader[2];

        staticPtr = malloc(staticAreaSize * sizeof(unsigned int));
        programMemory = malloc(instructionCount * sizeof(unsigned int));

        fread(programMemory, sizeof(unsigned int), instructionCount, loadedFile);
        fclose(loadedFile);

        while (!haltThis) {
            instr = programMemory[pc];
            matchInstruction(instr);
        }
        if (debugMode == true) {
            instr = programMemory[0];
            debugger(instr);
        }

    } else {
        printf("No Input \n");
        printf("Ninja Virtual Machine stopped\n");
        return (EXIT_FAILURE);
    }

    printf("Ninja Virtual Machine stopped\n");
    return (EXIT_SUCCESS);
}

/*
 * ToDo implement a debugger with a proper instructionset
 */
void debugger(int instr) {
    /*
     * run till end without stop
     * run next instruction
     */
    /* show Stack */
    /* printf(calculationStack); */

    /* show static Variables */
    /* printf(staticPtr); */

    /* list instructions */
    debugInstructions(instr);

    /* exit VM */
    /* exit(EXIT_SUCCESS); */

}

/**
 *
 * @return
 */
void matchInstruction(unsigned int instr) {
    int shift = instr>>24;
    if (shift == PUSHC) {
        push(SIGN_EXTEND(IMMEDIATE(instr)));
        pc++;
        return;
    }
    if (shift == HALT) {
        haltProgram();
        pc++;
        return;
    }
    if (shift == ADD) {
        add();
        pc++;
        return;
    }
    if (shift == SUB) {
        sub();
        pc++;
        return;
    }
    if (shift == MUL) {
        mul();
        pc++;
        return;
    }
    if (shift == DIV) {
        divide();
        pc++;
        return;
    }
    if (shift == MOD) {
        mod();
        pc++;
        return;
    }
    if (shift == RDINT) {
        rdint();
        pc++;
        return;
    }
    if (shift == WRINT) {
        wrint();
        pc++;
        return;
    }
    if (shift == RDCHR) {
        rdchr();
        pc++;
        return;
    }
    if (shift == WRCHR) {
        wrchr();
        pc++;
        return;
    }
    if (shift == PUSHG) {
        pushg(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == POPG) {
        popg(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == ASF) {
        asf(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == RSF) {
        rsf();
        pc++;
        return;
    }
    if (shift == PUSHL) {
        pushl(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == POPL) {
        popl(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == EQ) {
        eq();
        pc++;
        return;
    }
    if (shift == NE) {
        ne();
        pc++;
        return;
    }
    if (shift == LT) {
        lt();
        pc++;
        return;
    }
    if (shift == LE) {
        le();
        pc++;
        return;
    }
    if (shift == GT) {
        gt();
        pc++;
        return;
    }
    if (shift == GE) {
        ge();
        pc++;
        return;
    }
    if (shift == JMP) {
        jmp(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == BRF) {
        brf(SIGN_EXTEND(IMMEDIATE(shift)));
        pc++;
        return;
    }
    if (shift == BRT) {
        brt(SIGN_EXTEND(IMMEDIATE(programMemory[pc])));
        pc++;
        return;
    }
    if (shift == CALL) {
        call(SIGN_EXTEND(IMMEDIATE(programMemory[pc])));
        pc++;
        return;
    }
    if (shift == RET) {
        ret();
        pc++;
        return;
    }
    if (shift == PUSHR) {
        pushr();
        pc++;
        return;
    }
    if (shift == POPR) {
        popr();
        pc++;
        return;
    }
    if (shift == DROP) {
        drop(SIGN_EXTEND(IMMEDIATE(programMemory[pc])));
        pc++;
        return;
    }
}


/**
 * ONLY DEBUG
 * This method outputs all instructions inside a given program.
 * The listing order is from top to bottom.
 */
void debugInstructions(unsigned int inst) {
    int i;
    for (i = 0; i < instructionCount; i++) {
        switch SIGN_EXTEND(inst & 0xFF000000) {
            case HALT:
                printf("%d: HALT\n", i);
                break;
            case PUSHC:
                printf("%d: PUSHC\t %u \n", i, (SIGN_EXTEND(IMMEDIATE(programMemory[i]))));
                break;
            case ADD:
                printf("%d: ADD\n", i);
                break;
            case SUB:
                printf("%d: SUB\n", i);
                break;
            case MUL:
                printf("%d: MUL\n", i);
                break;
            case DIV:
                printf("%d: DIV1\n", i);
                break;
            case MOD:
                printf("%d: MOD\n", i);
                break;
            case RDINT:
                printf("%d: RDINT\n", i);
                break;
            case WRINT:
                printf("%d: WRINT\n", i);
                break;
            case RDCHR:
                printf("%d: RDCHR\n", i);
                break;
            case WRCHR:
                printf("%d: WRCHR\n", i);
                break;
            case PUSHG:
                printf("%d: PUSHG\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case POPG:
                printf("%d: POPG\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case ASF:
                printf("%d: ASF\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case RSF:
                printf("%d: RSF\n", i);
                break;
            case PUSHL:
                printf("%d: PUSHL\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case POPL:
                printf("%d: POPL\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case EQ:
                printf("%d: EQ\n", i);
                break;
            case NE:
                printf("%d: NE\n", i);
                break;
            case LT:
                printf("%d: LT\n", i);
                break;
            case LE:
                printf("%d: LE\n", i);
                break;
            case GT:
                printf("%d: GT\n", i);
                break;
            case GE:
                printf("%d: GE\n", i);
                break;
            case JMP:
                printf("%d: JMP\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case BRF:
                printf("%d: BRF\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case BRT:
                printf("%d: BRT\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case CALL:
                printf("%d: CALL\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case RET:
                printf("%d: RET\n", i);
                break;
            case DROP:
                printf("%d: DROP\t %u \n", i, (IMMEDIATE(programMemory[i])));
                break;
            case PUSHR:
                printf("%d: PUSHR\n", i);
                break;
            case POPR:
                printf("%d: POPR\n", i);
                break;
            case DUP:
                printf("%d: DUP\n", i);
                break;
            default:
                printf("Wert ungültig \n");
        }
        if ((programMemory[i] & 0xFF000000) == HALT) { break; }
    }
}


