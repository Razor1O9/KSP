#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"


int version = 4;
int calculationStack[9999];
int sp = 0;
int fp = 0;
int regADD = 0;
bool haltThis;
bool debugMode;
unsigned int programMemory[9999];
int programSize;
int instructionCount;
int pc;
int staticAreaSize;
int *staticPtr;

/**
 * This methods pushes a given variable on top of the stack.
 * @param var
 */
void push(int var) {
    if (sp < 9999) {
        calculationStack[sp] = var;
    } else {
        printf("Kein freier Speicher im Stack vorhanden\n");
        haltProgram();
    }
}

/**
 * This method removes the top variable from the stack.
 * It returns the new stack, without the removed variable.
 * @return
 */
int pop() {
    if (sp > 0) {
        sp--;
        pc++;
    } else {
        printf("Keine Elemente im Stack vorhanden\n");
        haltProgram();
    }
    return calculationStack[sp];
}

void add(void) {
    int var1 = pop();
    int var2 = pop();
    push(var2 + var1);
    pc += 1;
}

void sub(void) {
    int var1 = pop();
    int var2 = pop();
    push(var2 - var1);
    pc += 1;
}

void mul() {
    int var1 = pop();
    int var2 = pop();
    push(var2 * var1);
    pc += 1;
}

void divide() {
    int var1 = pop();
    int var2 = pop();
    push(var2 / var1);
    pc += 1;
}

void mod() {
    int var1 = pop();
    int var2 = pop();
    push(var2 % var1);
    pc += 1;
}

void rdint() {
    int var;
    scanf("%d", &var);
    push(var);
    pc += 1;
}

void wrint() {
    printf("%d", pop());
    pc += 1;
}

void rdchr() {
    char var;
    scanf("%c", &var);
    push(var);
    pc += 1;
}

void wrchr() {
    printf("%c", pop());
    pc += 1;
}

void popg(int var) {
    staticPtr[var] = pop();
}

void pushg(int var) {
    if (sp != 9999) {
        pushg(staticPtr[var]);
    }
}
void asf (int value) {
    push(fp);
    fp = sp;
    sp = sp + value;
}
void rsf () {
    sp = fp;
    fp = pop();
}



void pushl (int value) {
    pc++;
    if (sp != 9999) {
        calculationStack[sp] = calculationStack[fp +value];
        sp = sp +1;
    } else {
        EXIT_FAILURE;
    }
}
void popl (int value) {
    calculationStack[fp + value] = pop();
}

void popr() {
    pc++;
    regADD = calculationStack[sp-1];
}

void pushr() {
    push(regADD);
}

void drop(int var) {
    pc++;
    sp = sp - var;
}

void ret() {
    pc = pop();
}

void call(int value) {
    push(pc++);
    pc = value;
}

void brt(int value) {
    if (pop() == 1){
        pc = value;
    } else {
        EXIT_FAILURE;
    }
}

void brf(int value) {
    if (pop() == 0){
        pc = value;
    } else {
        EXIT_FAILURE;
    }
}

void jmp(int value) {
    pc = value;
}

void ge() {
    int var1 = pop();
    int var2 = pop();
    pc = pc -2;
    if (var2 >= var1){
        push(true);
    } else {
        push(false);
    }
}

void gt() {
    int var1 = pop();
    int var2 = pop();
    pc = pc -2;
    if (var2 > var1){
        push(true);
    } else {
        push(false);
    }
}

void le() {
    int var1 = pop();
    int var2 = pop();
    pc = pc - 2;
    if (var2 <= var1) {
        push(true);
    } else {
        push(false);
    }

}

void lt() {
    int var1 = pop();
    int var2 = pop();
    pc = pc - 2;
    if (var2 < var1) {
        push(true);
    } else {
        push(false);
    }
}

void ne() {
    int var1 = pop();
    int var2 = pop();
    pc = pc - 2;
    if (var1 == var2) {
        push(false);
    } else {
        push(true);
    }
}

void eq() {
    int var1 = pop();
    int var2 = pop();
    pc = pc - 2;
    if (var1 != var2) {
        push(false);
    } else {
        push(true);
    }
}

void haltProgram(void) {
    printf("Programm angehalten");
    haltThis = true;
}
