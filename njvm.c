/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"

/* Makro-Deklarationen */
#define HALT 0
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
#define TEST2 (11<<24
#define TEST3 (12<<24)
#define TEST4 (13<<24)
#define TEST5 (14<<24)
#define TEST6 (15<<24)
#define TEST7 (16<<24)
#define TEST8 (17<<24)
#define TEST9 (18<<24)
#define TEST10 (19<<24)
#define TEST11 (20<<24)
#define TEST12 (21<<24)
#define TEST13 (22<<24)
#define TEST14 (23<<24)
#define TEST15 (24<<24)

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))


bool haltThis = false;
bool debugMode = false;
int programMemory[9999];
int programSize = 0;
int instructionCount = 0;
int pc = 0;
int staticAreaSize = 0;

/**
 * Main Function, which reads all Terminal Arguments
 * Valid Arguments start more specific VM functions
 * @param argcount
 * @param argvector
 * @return
 */
int main(int argcount, char *argvector[]) {
    int a;
    int b;
    unsigned int *ptr;
    unsigned int *staticPtr;
    int i;
    FILE *loadedFile;
    char validBinFile[5];
    int programHeader[3];
    printf("Ninja Virtual Machine started\n");
    for (i = 0; i < argcount; i++) {
        if (!strcmp(argvector[1], NULL)) {
            printf("No Input \n");
            printf("Ninja Virtual Machine stopped\n");
            EXIT_FAILURE;
        }
        if (!strcmp(argvector[1], "--version")) {
            printf("Version = %d \n", version);
            printf("Ninja Virtual Machine stopped\n");
            EXIT_SUCCESS;
        }
        if (!strcmp(argvector[1], "--help")) {
            printf("Valid inputs: \n --version");
            printf("Ninja Virtual Machine stopped\n");
            EXIT_SUCCESS;
        }
        if (strstr(argvector[i], (const char *) (".bin" != NULL))) {
            if (strstr((const char *) argvector, (const char *) ("--debug" != NULL))) {
                debugMode = true;
                if (debugMode == true) {
                    debugInstructions();
                }
            }
            loadedFile = fopen((const char *) argvector, "r");
            if (!loadedFile) {
                printf("Error: Code file '%s' cannot be opened \n", argvector[1]);
                exit(1);
            }
            /* Lese alles als Stream ein, bis Ende des Programms (loadedFile) erreicht ist. */
            for (a = 0; a < argcount; a++) {
                fread(&validBinFile[a], sizeof(char), 4,
                      loadedFile); /* &programHeader = Pointer auf X, sizeOf(unsigned int) = 16 / 32 Bit, Array-Size, Thing to be read */
                if (strncmp(&validBinFile[0], "NJBF", 4) != 0) {
                    haltProgram();
                }
            }

            for (b = 0; b < argcount; b++) {
                fread(&programHeader[i], sizeof(unsigned int), 3,
                      loadedFile); /* läuft von Stelle 0 bis Stelle 2 von ProgramHeader */
                if (version < programHeader[b]) {
                    printf("Version: %d is not supported!", programHeader[0]);
                    exit(1);
                }
                instructionCount = programHeader[1];
                staticAreaSize = programHeader[2];
                staticPtr = (unsigned int *) malloc(staticAreaSize * sizeof(unsigned int));
                ptr = (unsigned int *) malloc(instructionCount * sizeof(unsigned int));
                fread(ptr, sizeof(unsigned int), (size_t) instructionCount, loadedFile);
                fread(staticPtr, sizeof(unsigned int), (size_t) staticAreaSize, loadedFile);
                while (!haltThis) {
                    matchInstruction();
                }
            }


        }
    }
    printf("Ninja Virtual Machine stopped\n");
    return EXIT_SUCCESS;
}


/**
 *
 * @return
 */
void matchInstruction(void) {
    for (pc = 0; pc < programSize; pc++) {
        if (programMemory[pc] == PUSHC) {
            push(SIGN_EXTEND(IMMEDIATE(programMemory[pc])));
            pc++;
        } else if (programMemory[pc] == HALT) {
            break;
        } else if (programMemory[pc] == ADD) {
            add();
        } else if (programMemory[pc] == SUB) {
            sub();
        } else if (programMemory[pc] == MUL) {
            mul();
        } else if (programMemory[pc] == DIV) {
            divide();
        } else if (programMemory[pc] == MOD) {
            mod();
        } else if (programMemory[pc] == RDINT) {
            rdint();
        } else if (programMemory[pc] == WRINT) {
            wrint();
        } else if (programMemory[pc] == RDCHR) {
            rdchr;
        } else if (programMemory[pc] == WRCHR) {
            wrchr;
        } else if (programMemory[pc] == TEST3) {
            wrchr;
        } else if (programMemory[pc] == TEST4) {
            wrchr;
        } else if (programMemory[pc] == TEST5) {
            wrchr;
        } else if (programMemory[pc] == TEST6) {
            wrchr;
        } else if (programMemory[pc] == TEST7) {
            wrchr;
        } else if (programMemory[pc] == TEST8) {
            wrchr;
        } else if (programMemory[pc] == TEST9) {
            wrchr;
        } else if (programMemory[pc] == TEST11) {
            wrchr;
        } else if (programMemory[pc] == TEST12) {
            wrchr;
        } else if (programMemory[pc] == TEST13) {
            wrchr;
        } else if (programMemory[pc] == TEST14) {
            wrchr;
        } else if (programMemory[pc] == TEST15) {
            wrchr;
        }
    }
}


/**
 * ONLY DEBUG
 * This method outputs all instructions inside a given program.
 * The listing order is from top to bottom.
 */
void debugInstructions(void) {
    int i;
    for (i = 0;; i++) {
        switch (programMemory[i] & 0xFF000000) {
            case HALT:
                printf("%d: HALT\n", i);
                break;
            case PUSHC:
                printf("%d: PUSHC\t %d \n", i, SIGN_EXTEND(IMMEDIATE(programMemory[i])));
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
            default:
                printf("Wert ungültig \n");
        }
        if ((programMemory[i] & 0xFF000000) == HALT) { break; }
    }
}

