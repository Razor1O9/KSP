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

int version = 1; // The current version
int programMemory[9999]; // List of all Program Instructions
int pc; // Program Counter Variable for Instructions

int calculationStack[9999]; // Stack for Calculation
int sp; // Stack Pointer Variable for Calculations

unsigned int source[9999]; // natürliche Zahl
char letter; // character


/**
 * Main Function, which reads all Terminal Arguments
 * Valid Arguments start more specific VM functions
 * @param argcount
 * @param argvector
 * @return
 */
int main(int argcount, char *argvector[]) {

    printf("Ninja Virtual Machine started\n");
    for (argcount = 0; argcount < argvector; argcount++) {
        if (!strcmp(programMemory[argcount], "--version")) {
            printf("Version = ", version, "\n");
        } else if (!strcmp(programMemory[argcount], "--help")) {
            printf("Valid inputs: \n --version \n --help\n --program1 \n --program2 \n --program3 \n");
        } else if (!strcmp(programMemory[argcount], "1")) {
            source[0] = PUSHC | IMMEDIATE(3);
            source[1] = PUSHC | IMMEDIATE(4);
            source[2] = ADD;
            source[3] = PUSHC | IMMEDIATE(10);
            source[4] = PUSHC | IMMEDIATE(6);
            source[5] = SUB;
            source[6] = MUL;
            source[7] = WRINT;
            source[8] = PUSHC | IMMEDIATE(10);
            source[9] = WRCHR;
            source[10] = HALT;
        } else if (!strcmp(programMemory[argcount], "2")) {
            source[0]=PUSHC|IMMEDIATE(-2);
            source[1]=RDINT;
            source[2]=MUL;
            source[3]=PUSHC|IMMEDIATE(3);
            source[4]=ADD;
            source[5]=WRINT;
            source[6]=PUSHC|'\n';
            source[7]=WRCHR;
            source[8]=HALT;
        } else if (!strcmp(programMemory[argcount], "3")) {
            source[0]=RDCHR;
            source[1]=WRINT;
            source[2]=PUSHC|'\n';
            source[3]=WRCHR;
            source[4]=HALT;
        }
    }
    printf("End of input reached\n");
    printf("Ninja Virtual Machine stopped\n");
    return EXIT_SUCCESS;
}

/**
 *
 * @param opCode
 */
void calculate(int opCode) {
    if (opCode == ADD) {
        calculationStack[sp - 1] = calculationStack[sp - 1] + calculationStack[sp];
    }
    if (opCode == SUB) {
        calculationStack[sp - 1] = calculationStack[sp - 1] - calculationStack[sp];
    }
    if (opCode == MUL) {
        calculationStack[sp - 1] = calculationStack[sp - 1] * calculationStack[sp];
    }
    if (opCode == DIV) {
        calculationStack[sp - 1] = calculationStack[sp - 1] / calculationStack[sp];
    }
    if (opCode == MOD) {
        calculationStack[sp - 1] = calculationStack[sp - 1] / calculationStack[sp];
    }
}

/**
 *
 * @param opCode
 */
void data(int opCode) {
    if (opCode == RDINT) {
        // zahl einlesen
    }
    if (opCode == WRINT) {
        printf(source);
        sp--;
    }
    if (opCode == RDCHR) {
        // char einlesen
    }
    if (opCode == WRCHR) {
        printf(letter);
        sp--;
    }
}

/**
 *
 * @return
 */
int matchInstruction() {
    for (pc = 0; pc < programMemory; pc++) {
        if (programMemory[pc] == PUSHC) {
            pc++;
            source = programMemory[pc];
            calculationStack[pc] = source;
        } else if (programMemory[pc] == HALT) {
            exit;
            printf("HALT \n");
        } else if (programMemory[pc] == ADD) {
            calculate(ADD);
            printf("ADD \n");
        } else if (programMemory[pc] == SUB) {
            calculate(SUB);
            printf("SUB \n");
        } else if (programMemory[pc] == MUL) {
            calculate(MUL);
            printf("MUL");
        } else if (programMemory[pc] == DIV) {
            calculate(DIV);
            printf("DIV \n");
        } else if (programMemory[pc] == MOD) {
            calculate(MOD);
            printf("MOD \n");
        } else if (programMemory[pc] == RDINT) {
            data(RDINT);
            printf("RDINT \n");
        } else if (programMemory[pc] == WRINT) {
            data(WRINT);
            printf("WRINT \n");
        } else if (programMemory[pc] == RDCHR) {
            data(RDCHR);
            printf("RDCHR \n");
        } else if (programMemory[pc] == WRCHR) {
            data(WRCHR);
            printf("WRCHR \n");
        }
    }
}