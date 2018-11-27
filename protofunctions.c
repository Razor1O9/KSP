#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"


int version = 111;
int calculationStack[9999];
int sp = 0;
bool haltThis;
bool debugMode;
int programMemory[9999];
int globalVars[9999];
int programSize;
int instructionCount;
int pc;
int staticAreaSize;

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
    globalVars[var] = pop();
}
void pushg(int var) {
    if (!stack_Full()) {
        pushg(globalVars[var]);
    }
}
void popr() {

}

void pushr() {

}

void drop(int var) {
 pc++;
 sp = sp - var;
}

void ret() {

}

void call() {

}

void brt() {

}

void brf() {

}

void jmp() {

}

void ge() {

}

void gt() {

}

void le() {

}

void lt() {
    int var1 = pop();
    int var2 = pop();
    pc = pc-2;
    if (var2 < var1) {
        
    }
}

void ne() {
    pc = pc-2;
    if (pop() == (pop())){
        push(false);
    } else {
        push (true);
    }
}

void eq() {
    pc = pc-2;
    if (pop() != pop()){
        push(false);
    } else {
        push(true);
    }
}
void dup(){
    pc++;
    calculationStack[sp] = calculationStack[sp-1];
    sp++;
}

int full_Stack(){
    if (sp != 9999) {
        return false;
    } else {
        return true;
    }
}

int empty_Stack(){
    if (sp == -1) {
        return true;
    } else {
        return false;
    }
}

void haltProgram(void) {
    printf("Programm angehalten");
    haltThis = true;
}
