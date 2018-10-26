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

int programMemory[9999]; // Befehlsliste
int pc; // program counter

int calculationStack[9999]; // Rechnerstack
int si; // stack index

unsigned int zahl; // natürliche Zahl
char letter; // character


int main(int argcount, char *argvector[]) {

    printf("Ninja Virtual Machine started\n");
    for (argcount = 0; argcount < argvector; argcount++) {
        if (!strcmp(programMemory[argcount], "--version")) {
            printf("Version 1\n");
        } else if (!strcmp(programMemory[argcount], "--help")) {
            printf("Valid inputs: \n --version \n --help\n");
        } else if (!strcmp(programMemory[argcount], "1")) {
            printf("... \n");
        } else if (!strcmp(programMemory[argcount], "2")) {
            printf("... \n");
        } else if (!strcmp(programMemory[argcount], "3")) {
            printf("... \n");
        }
    }
    printf("End of input reached\n");
    printf("Ninja Virtual Machine stopped\n");
    return EXIT_SUCCESS;
}


void calculate(int opCode) {
    if (opCode == ADD) {
        calculationStack[si - 1] = calculationStack[si - 1] + calculationStack[si];
    }
    if (opCode == SUB) {
        calculationStack[si - 1] = calculationStack[si - 1] - calculationStack[si];
    }
    if (opCode == MUL) {
        calculationStack[si - 1] = calculationStack[si - 1] * calculationStack[si];
    }
    if (opCode == DIV) {
        calculationStack[si - 1] = calculationStack[si - 1] / calculationStack[si];
    }
    if (opCode == MOD) {
        calculationStack[si - 1] = calculationStack[si - 1] / calculationStack[si];
    }
}

void data(int opCode) {
    if (opCode == RDINT) {
        // zahl einlesen
    }
    if (opCode == WRINT) {
        printf(zahl);
        si--;
    }
    if (opCode == RDCHR) {
        // char einlesen
    }
    if (opCode == WRCHR) {
        printf(letter);
        si--;
    }
}

int matchInstruction() {
    for (pc = 0; pc < programMemory; pc++) {
        if (programMemory[pc] == PUSHC) {
            pc++;
            zahl = programMemory[pc];
            calculationStack[pc] = zahl;
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