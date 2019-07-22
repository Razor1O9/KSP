#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"

int version = 4;
int calculationStack[1000];
int  fp = 0;
int regADD = 0;
bool haltThis = false;
bool debugMode = false;
int breakpoint_pos = 0;
bool breakpoint = false;
unsigned int *programMemory;
int instructionCount=0;
int pc=0;
int dc=0;
int staticAreaSize=0;
int *staticPtr;
int sp;

// This method greate a Object get memory from heap
ObjRef createObject(int value) {
    ObjRef o = malloc(sizeof(unsigned int) + sizeof(int));
    if(o == NULL) {
        printf("memory is full");
        exit(1);
    }
    o->size = sizeof(int);
    *(int*) (o->data) = value;
    return o;
}

/**
 * This method pushes only numbers on top of the stack.
 * @param var
 */
void pushNumber(int var) {
    if (sp < 1000) {
        calculationStack[sp].u.number = var;
        calculationStack[sp].isObjRef = false;
        sp++;
    } else {
        haltProgram();
    }
}

// This method pushes only Object on the top of stack
void pushObject(int var) {
    if (sp < 1000) {
        calculationStack[sp].u.objRef = createObject(var);
        calculationStack[sp].isObjRef = true;
        sp++;
    } else {
        haltProgram();
    }
}

/**
 * This method removes the top variable from the stack.
 * It returns the new stack, without the removed variable.
 * @return
 */
Stackslot pop() {
    Stackslot value;
    if (sp > 0) {
        sp--;
        value = calculationStack[sp];
    } else {
        haltProgram();
    }
    return value;
}

void add(void) {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    push(var2 + var1);
}

void sub(void) {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pushObject(var2 - var1);
}

void mul() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pushObject(var2 * var1);
}

void divide() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pushObject(var2 / var1);
}

void mod() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pushObject(var2 % var1);
}

void rdint() {
    int var;
    scanf("%d", &var);
    pushObject(var);
}

void wrint() {
    printf("%d", *(int *) (pop().u.objRef->data));
}

void rdchr() {
    char var;
    scanf("%c", &var);
    pushObject(var);
}

void wrchr() {
    printf("%c", *(int *) (pop().u.objRef->data));
}

void popg(int var) {
    staticPtr[var] = pop().u.objRef;
}

void pushg(int var) {
    if (sp != 1000) {
        push(*(int *) (staticPtr[var]->data));
    }
}
void asf (int value) {
    pushNumber(fp);
    fp = sp;
    sp = sp + value;
}
void rsf () {
    sp = fp;
    fp = *(int *) (pop().u.objRef->data);
}



void pushl (int value) {
    if (sp != 1000) {
        calculationStack[sp] = calculationStack[fp + value];
        sp = sp + 1;
    }
}
void popl (int value) {
    calculationStack[fp + value] = pop();
}

void popr() {
    regADD = calculationStack[sp-1].u.objRef;
}

void pushr() {
    push(*(int *) (regADD->data));
}

void drop(int var) {
    sp = sp - var;
}

void ret() {
    pc = *(int *) (pop().u.objRef->data);
}

void call(int value) {
    pushNumber(pc);
    pc = value-1;
}

void brt(int value) {
    if (*(int *) (pop().u.objRef->data) == 1) {
        pc = value;
    }
}

void brf(int value) {
    if (*(int *) (pop().u.objRef->data) == 0) {
        pc = value;
    }
}

void jmp(int value) {
    pc = value;
}

void ge() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc -2;
    if (var2 >= var1){
        pushObject(true);
    } else {
        pushObject(false);
    }
}

void gt() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc -2;
    if (var2 > var1){
        push(true);
    } else {
        push(false);
    }
}

void le() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var2 <= var1) {
        push(true);
    } else {
        push(false);
    }

}

void lt() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var2 < var1) {
        push(true);
    } else {
        push(false);
    }
}

void ne() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var1 == var2) {
        push(false);
    } else {
        push(true);
    }
}

void eq() {
    int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var1 != var2) {
        push(false);
    } else {
        push(true);
    }
}

void haltProgram(void) {
    haltThis = true;
}
