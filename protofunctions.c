#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"
#include "bigint/build/include/bigint.h"

int version = 6;
Stackslot calculationStack[1000];
int  fp = 0;
ObjRef regADD = 0;
bool haltThis = false;
bool debugMode = false;
int breakpoint_pos = 0;
bool breakpoint = false;
unsigned int *programMemory;
int instructionCount=0;
int pc=0;
int dc=0;
unsigned int staticAreaSize=0;
ObjRef *staticPtr;
int sp;

bool is_object(int i) {
    if(calculationStack[i].isObjRef == true)
        return true;
    return false;
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
void pushObject(ObjRef var) {
    if (sp < 1000) {
        calculationStack[sp].u.objRef = var;
        calculationStack[sp].isObjRef = true;
        sp++;
    } else {
        haltProgram();
    }
}

/**
 * This method removes the top variable from the stack. duc
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
    bip.op1 = pop().u.objRef;
    bip.op2 = pop().u.objRef;
    bigAdd();
    pushObject(bip.res);
}

void sub(void) {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    bigSub();
    pushObject(bip.res);
}

void mul() {
    bip.op1 = pop().u.objRef;
    bip.op2 = pop().u.objRef;
    bigMul();
    pushObject(bip.res);
}

void divide() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    bigDiv();
    pushObject(bip.res);
}

void mod() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    bigDiv();
    pushObject(bip.rem);
}

void rdint() {
    int var;
    scanf("%d", &var);
    bigFromInt(var);
    pushObject(bip.res);
}

void wrint() {
    bip.op1 = pop().u.objRef;
    bigPrint(stdout);
}

void rdchr() {
    char var;
    scanf("%c", &var);
    bigFromInt(var);
    pushObject(bip.res);
}

void wrchr() {
    bip.op1 = pop().u.objRef;
    printf("%c", bigToInt());
}

void popg(int var) {
    staticPtr[var] = pop().u.objRef;
}

void pushg(int var) {
    if (sp != 1000) {
        pushObject(staticPtr[var]);
    }
}
void asf (int value) {
    pushNumber(fp);
    fp = sp;
    sp = sp + value;
}
void rsf () {
    sp = fp;
    fp = pop().u.number;
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
    pushObject(regADD);
}

void drop(int var) {
    sp = sp - var;
}

void ret() {
    bip.op1 = pop().u.objRef;
    pc = bigToInt();
}

void call(int value) {
    bigFromInt(pc);
    pushObject(bip.res);
    pc = value-1;
}

void brt(int value) {
    bip.op1 = pop().u.objRef;
    if(bigToInt() == 1)
        pc = value;
}

void brf(int value) {
    bip.op1 = pop().u.objRef;
    if(bigToInt() == 0)
        pc = value;
}

void jmp(int value) {
    pc = value;
}

void ge() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    if(bigCmp() >= 0)
        bigFromInt(1);
    else
        bigFromInt(0);
    pushObject(bip.res);

    /*int var1 = *(int *) (pop().u.objRef->data);*/
    /*int var2 = *(int *) (pop().u.objRef->data);*/
    /*pc = pc -2;*/
    /*if (var2 >= var1){*/
    /*    pushObject(true);*/
    /*} else {*/
    /*    pushObject(false);*/
    /*}*/
}

void gt() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    if(bigCmp() > 0)
        bigFromInt(1);
    else
        bigFromInt(0);
    pushObject(bip.res);
//    int var1 = *(int *) (pop().u.objRef->data);
//    int var2 = *(int *) (pop().u.objRef->data);
//    pc = pc -2;
//    if (var2 > var1){
//        pushObject(true);
//    } else {
//        pushObject(false);
//    }
}

void le() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    if(bigCmp() <= 0)
        bigFromInt(1);
    else
        bigFromInt(0);
    pushObject(bip.res);
    /*int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var2 <= var1) {
        pushObject(true);
    } else {
        pushObject(false);
    }*/

}

void lt() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    if(bigCmp() < 0)
        bigFromInt(1);
    else
        bigFromInt(0);
    pushObject(bip.res);
    /*int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var2 < var1) {
        pushObject(true);
    } else {
        pushObject(false);
    }*/
}

void ne() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    if(bigCmp() == 0)
        bigFromInt(0);
    else
        bigFromInt(1);
    pushObject(bip.res);
    /*int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var1 == var2) {
        pushObject(false);
    } else {
        pushObject(true);
    }*/
}

void eq() {
    bip.op2 = pop().u.objRef;
    bip.op1 = pop().u.objRef;
    if(bigCmp() == 0)
        bigFromInt(1);
    else
        bigFromInt(0);
    pushObject(bip.res);
    /*int var1 = *(int *) (pop().u.objRef->data);
    int var2 = *(int *) (pop().u.objRef->data);
    pc = pc - 2;
    if (var1 != var2) {
        pushObject(false);
    } else {
        pushObject(true);
    }*/
}

void haltProgram(void) {
    haltThis = true;
}
