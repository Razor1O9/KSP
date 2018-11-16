/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"

// Makro-Deklarationen
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
#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))


/**
 * Main Function, which reads all Terminal Arguments
 * Valid Arguments start more specific VM functions
 * @param argcount
 * @param argvector
 * @return
 */
int main(int argcount, char *argvector[]) {
    printf("Ninja Virtual Machine started\n");
    for (int i = 0; i < argcount; i++) {
        if (!strcmp(argvector[i], "--version")) {
            printf("Version = %d \n", version);
        } else if (!strcmp(argvector[i], "--help")) {
            printf("Valid inputs: \n --version \n --help\n --program1 \n --program2 \n --program3 \n");
            printf("End of input reached\n");
            printf("Ninja Virtual Machine stopped\n");
            return EXIT_SUCCESS;
        } else {
            FILE *loadedFile;
            loadedFile = fopen(argvector, "r");
            if (!loadedFile) {
                printf("Error: cannot open code file '%s'\n", argvector[1]);
                exit(99);
            }
            // Lese alles als Stream ein, bis Ende des Programms (loadedFile) erreicht ist.
            int programHeader[100];
            //if (strncmp(programHeader[0], "NJBF", 4)) {
            if (fread(&programHeader[0], sizeof(unsigned int), 4, loadedFile) !=
                4) { // &programHeader = Pointer auf X, sizeOf(unsigned int) = 16 / 32 Bit, Array-Size, Thing to be read
                haltProgram();
            }
            if (fread(&programHeader[1], sizeof(int), 4, loadedFile) != 4) {
                haltProgram();  // Versionsnummer nicht drüber!

            }
            if (fread(&programHeader[2], sizeof(unsigned int), 4, loadedFile) != 4) {
                haltProgram();
            } else {
                instructionCount = programHeader[2];
            }

            if (fread(&programHeader[3], sizeof(unsigned int), 4, loadedFile) != 4) {
                haltProgram();
            } else {
                staticAreaSize = programHeader[3];
            }
            int count;
            for (count = 0; count < instructionCount; count++) {
                fread(&programMemory[count], sizeof(unsigned int), instructionCount, loadedFile);
            }
        }
        if (debugMode == true) {
            debugInstructions();
        }
        while (!haltThis) {
            matchInstruction();

        }
        exit(-1);

    }

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

