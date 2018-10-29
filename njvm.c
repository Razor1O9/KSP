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
    for (int i = 0; i < argcount; i++) {
        if (!strcmp(programMemory[i], "--version")) {
            printf("Version = ", version, "\n");
        } else if (!strcmp(programMemory[i], "--help")) {
            printf("Valid inputs: \n --version \n --help\n --program1 \n --program2 \n --program3 \n");
        } else if (!strcmp(programMemory[i], "--1")) {
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
            listInstructions();
            matchInstruction();
        } else if (!strcmp(programMemory[i], "--2")) {
            source[0] = PUSHC | IMMEDIATE(-2);
            source[1] = RDINT;
            source[2] = MUL;
            source[3] = PUSHC | IMMEDIATE(3);
            source[4] = ADD;
            source[5] = WRINT;
            source[6] = PUSHC | '\n';
            source[7] = WRCHR;
            source[8] = HALT;
            listInstructions();
            matchInstruction();
        } else if (!strcmp(programMemory[i], "--3")) {
            source[0] = RDCHR;
            source[1] = WRINT;
            source[2] = PUSHC | '\n';
            source[3] = WRCHR;
            source[4] = HALT;
            listInstructions();
            matchInstruction();
        }
    }
    printf("End of input reached\n");
    printf("Ninja Virtual Machine stopped\n");
    return EXIT_SUCCESS;
}

/**
 * This method contains instructions for calculations
 * Instructions are performored if the given opCode matches with an instruction inside the method.
 * @param opCode
 */
void calculate(int opCode) {
    if (opCode == ADD) {
        add();
    }
    if (opCode == SUB) {
        sub();
    }
    if (opCode == MUL) {
        mul();
    }
    if (opCode == DIV) {
        divide();
    }
    if (opCode == MOD) {
        mod();
    }
}

/**
 * This method contains instructions for read- and write data manipulation.
 * Instructions are performored if the opCode matches with an instruction inside the method.
 * @param opCode
 */
void data(int opCode) {
    if (opCode == PUSHC) {
        push(SIGN_EXTEND(IMMEDIATE(source[opCode])));
    }
    if (opCode == RDINT) {
        rdint();
    }
    if (opCode == WRINT) {
        wrint();
    }
    if (opCode == RDCHR) {
        rdchr();
    }
    if (opCode == WRCHR) {
        wrchr();
    }
}

void end(int opCode) {
    if (opCode == HALT) {
        halt();
    }
}

/**
 *
 * @return
 */
matchInstruction() {
    for (pc = 0; pc < programMemory; pc++) {
        if (programMemory[pc] == PUSHC) {
            pc++;
            source == programMemory[pc];
            calculationStack[pc] = source;
        } else if (programMemory[pc] == HALT) {
            break;
        } else if (programMemory[pc] == ADD) {
            calculate(ADD);
        } else if (programMemory[pc] == SUB) {
            calculate(SUB);
        } else if (programMemory[pc] == MUL) {
            calculate(MUL);
        } else if (programMemory[pc] == DIV) {
            calculate(DIV);
        } else if (programMemory[pc] == MOD) {
            calculate(MOD);
        } else if (programMemory[pc] == RDINT) {
            data(RDINT);
        } else if (programMemory[pc] == WRINT) {
            data(WRINT);
        } else if (programMemory[pc] == RDCHR) {
            data(RDCHR);
        } else if (programMemory[pc] == WRCHR) {
            data(WRCHR);
        }
    }

}

/**
 * This method outputs all instructions inside a given program.
 * The listing order is from top to bottom.
 */
listInstructions() {
    int i;
    for (i = 0;; i++) {
        switch (source[i] & 0xFF000000) {
            case HALT:
                printf("%d: HALT\n", i);
                break;
            case PUSHC:
                printf("%d: PUSHC\t %d \n", i, SIGN_EXTEND(IMMEDIATE(source[i])));
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
        if ((source[i] & 0xFF000000) == HALT) { break; }
    }
}


/**
 * This methods pushes a given variable on top of the stack.
 * @param var
 */
push(int var) {
    if (sp < 9999) {
        calculationStack[sp] = var;
    } else {
        printf("Kein freier Speicher im Stack vorhanden\n");
        exit(-1);
    }
}

/**
 * This method removes the top variable from the stack.
 * It returns the new stack, without the removed variable.
 * @return
 */
pop() {
    if (sp > 0) {
        sp--;
    } else {
        printf("Keine Elemente im Stack vorhanden\n");
        exit(-1);
    }
    return calculationStack[sp];
}

add() {
    int var1 = pop();
    int var2 = pop();
    push(var1 + var2);
}

sub() {
    int var1 = pop();
    int var2 = pop();
    push(var2 - var1);
}

mul() {
    int var1 = pop();
    int var2 = pop();
    push(var2 * var1);
}

divide() {
    int var1 = pop();
    int var2 = pop();
    push(var2 / var1);
}

mod() {
    int var1 = pop();
    int var2 = pop();
    push(var2 % var1);
}

rdint() {
    int var;
    scanf("%i", &var);
    push(var);
}

wrint() {
    printf("%i", pop());
}

rdchr() {
    char var;
    scanf("%c", &var);
    push(var);
}

wrchr() {
    printf("%c", pop());
}