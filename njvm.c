/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "protofunctions.h"

/* Makro-Deklarationen */
#define HALT (0<<24)
#define PUSHC (1<<24)
#define ADD (2<<24)
#define SUB (3<<24)
#define MUL (4<<24)
#define DIV (5<<24)
#define MOD (6<<24)
#define RDINT (7<<24)
#define WRINT (8<<24)
#define RDCHR (9<<24)
#define WRCHR (10<<24)
#define PUSHG (11<<24)
#define POPG (12<<24)
#define ASF (13<<24)
#define RSF (14<<24)
#define PUSHL (15<<24)
#define POPL (16<<24)
#define EQ (17<<24)
#define NE (18<<24)
#define LT (19<<24)
#define LE (20<<24)
#define GT (21<<24)
#define GE (22<<24)
#define JMP (23<<24)
#define BRF (24<<24)
#define BRT (25<<24)
#define CALL (26<<24)
#define RET  (27<<24)
#define DROP (28<<24)
#define PUSHR (29<<24)
#define POPR (30<<24)
#define DUP (31<<24)

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define OPCODE(i) ((i) & 0xFF000000)
/* 0x00800000 -> 8 checks the sign (+ or -) */
/* 0xFF000000 -> Fills the OpCode with 1 */
#define SIGN_EXTEND(i) ((i) & 0x00000000 ? (i) | 0xFF000000 : (i))

int version;
int calculationStack[9999];
int sp;
bool haltThis = false;
bool debugMode = false;
int programMemory[9999];

int instructionCount = 0;
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
    int reader;
    int count;
    unsigned int *instrPtr;
    char bin[] = ".bin";
    char debug[] = "--debug";
    FILE *loadedFile = NULL;
    char validBinFile[5];
    unsigned int programHeader[3];
    printf("Ninja Virtual Machine started\n\n");

    /* Prints the current VM-Version */
    if (!strcmp(argv[1], "--version")) {
        printf("Version = %d \n", version);
        printf("\nNinja Virtual Machine stopped\n");
        return (EXIT_SUCCESS);
    }
    /* Prints all valid shell commands */
    if (!strcmp(argv[1], "--help")) {
        printf("Valid inputs: \n [1] --version \n [2] --help \n [3] 'programname'.bin \n [4] --debug 'programname'.bin \n [5] 'programname.bin' --debug");
        printf("\n\nNinja Virtual Machine stopped\n");
        return (EXIT_SUCCESS);
    }
    /* Searches the arguments for a binary file" */
    if (argc == 2) {
        if (strstr(argv[1], bin) == NULL) {
            printf("\n\nNot a binary file\n");
            return (EXIT_FAILURE);
        } else {
            loadedFile = fopen(argv[1], "r");
        }
        if (!loadedFile) {
            printf("Error: Code file '%s' cannot be opened \n", argv[1]);
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
        instrPtr = malloc(instructionCount * sizeof(unsigned int));
        count = 0;
        do {
            /* reads the File sourcecode */
            fread(&programMemory[count], sizeof(unsigned int), 1, loadedFile);
            instrPtr[count] = programMemory[count];
            int instr = programMemory[count];
            count++;
        } while (count < instructionCount);

        while (!haltThis) {
            for (pc = 0; pc < instructionCount; pc++) {
                matchInstruction(pc);
            }
        }
        if (debugMode == true) {
            debugger();
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
void debugger(void) {
    /*
     * run till end without stop
     * run next instruction
     */
    /* show Stack */
    /* printf(calculationStack); */

    /* show static Variables */
    /* printf(staticPtr); */

    /* list instructions */
    debugInstructions();

    /* exit VM */
    /* exit(EXIT_SUCCESS); */

}


/**
 *
 * @return
 */
void matchInstruction(int pc) {
        int clearedOP = SIGN_EXTEND(programMemory[pc] & 0xFF000000);
        if (clearedOP == PUSHC) {
            push((IMMEDIATE(programMemory[pc])));
            return;
        }
        if (clearedOP == HALT) {
            haltProgram();
            return;
        }
        if (clearedOP == ADD) {
            add();
            return;
        }
        if (clearedOP == SUB) {
            sub();
            return;
        }
        if (clearedOP == MUL) {
            mul();
            return;
        }
        if (clearedOP == DIV) {
            divide();
            return;
        }
        if (clearedOP == MOD) {
            mod();
            return;
        }
        if (clearedOP == RDINT) {
            rdint();
            return;
        }
        if (clearedOP == WRINT) {
            wrint();
            return;
        }
        if (clearedOP == RDCHR) {
            rdchr();
            return;
        }
        if (clearedOP == WRCHR) {
            wrchr();
            return;
        }
        if (clearedOP == PUSHG) {
            pushg(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == POPG) {
            popg(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == ASF) {
            asf(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == RSF) {
            rsf();
            return;
        }
        if (clearedOP == PUSHL) {
            pushl(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == POPL) {
            popl(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == EQ) {
            eq();
            return;
        }
        if (clearedOP == NE) {
            ne();
            return;
        }
        if (clearedOP == LT) {
            lt();
            return;
        }
        if (clearedOP == LE) {
            le();
            return;
        }
        if (clearedOP == GT) {
            gt();
            return;
        }
        if (clearedOP == GE) {
            ge();
            return;
        }
        if (clearedOP == JMP) {
            jmp(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == BRF) {
            brf(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == BRT) {
            brt(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == CALL) {
            call(IMMEDIATE(programMemory[pc]));
            return;
        }
        if (clearedOP == RET) {
            ret();
            return;
        }
        if (clearedOP == PUSHR) {
            pushr();
            return;
        }
        if (clearedOP == POPR) {
            popr();
            return;
        }
        if (clearedOP == DROP) {
            drop(IMMEDIATE(programMemory[pc]));
            return;
        }
    }



/**
 * ONLY DEBUG
 * This method outputs all instructions inside a given program.
 * The listing order is from top to bottom.
 */
void debugInstructions(void) {
    int i;
    for (i = 0; i < instructionCount; i++) {
        switch SIGN_EXTEND(programMemory[i] & 0xFF000000) {
            case HALT:
                printf("%d: HALT\n", i);
                break;
            case PUSHC:
                printf("%d: PUSHC\t %d \n", i, (IMMEDIATE(programMemory[i])));
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
                printf("%d: PUSHG\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case POPG:
                printf("%d: POPG\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case ASF:
                printf("%d: ASF\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case RSF:
                printf("%d: RSF\n", i);
                break;
            case PUSHL:
                printf("%d: PUSHL\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case POPL:
                printf("%d: POPL\t %d \n", i,(IMMEDIATE(programMemory[i])));
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
                printf("%d: JMP\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case BRF:
                printf("%d: BRF\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case BRT:
                printf("%d: BRT\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case CALL:
                printf("%d: CALL\t %d \n", i,(IMMEDIATE(programMemory[i])));
                break;
            case RET:
                printf("%d: RET\n", i);
                break;
            case DROP:
                printf("%d: DROP\t %d \n", i,(IMMEDIATE(programMemory[i])));
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



