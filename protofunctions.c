#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protofunctions.h"
#include "bigint/src/bigint.h"
#include "bigint/src/support.h"

int version = 4;
StackSlot calculationStack[1000];
ObjRef *reg;
int fp = 0;
bool haltThis = false;
bool debugMode = false;
int breakpoint_pos = 0;
bool breakpoint = false;
unsigned int *programMemory;
int instructionCount = 0;
int pc = 0;
int dc = 0;
int staticAreaSize = 0;
int *staticPtr;
int sp;

/**
 * This methods pushes a given variable on top of the stack.
 * @param var
 */
void push(void *var) {
    StackSlot member = {0};
    member.u.number = malloc(sizeof(int));
    member.u.objRef = malloc(sizeof(unsigned int) + sizeof(int));
    if (member.u.objRef != NULL) {
        member.isObjRef = true;
        if (sp < 1000) {
            calculationStack[sp].u.number = var;
            sp++;
        } else {
            haltProgram();
        }
    } else {
        member.isObjRef = false;
        if (sp < 1000) {
            calculationStack[sp].u.objRef = var;
            sp++;
        } else {
            haltProgram();
        }
    }
}

/**
 * This method removes the top variable from the stack.
 * It returns the new stack, without the removed variable.
 * @return
 */

void *pop() {
    StackSlot member = {0};
    ObjRef cache;
    int numCache;
    if (member.u.objRef != NULL) {
        member.isObjRef = true;
        if (sp > 0) {
            cache = calculationStack[sp].u.objRef;
            calculationStack[sp].u.objRef = NULL;
            sp--;
        } else {
            haltProgram();
        }
        return cache;
    } else {
        member.isObjRef = false;
        if (sp > 0) {
            numCache = calculationStack[sp].u.number;
            calculationStack[sp].u.number = NULL;
            sp--;
        } else {
            haltProgram();
        }
        return numCache;
    }


}

void add(void) {
    int var1 = (int) pop();
    int var2 = (int) pop();
    push((void *) (var2 + var1));
}

void sub(void) {
    int var1 = (int) pop();
    int var2 = (int) pop();
    push((void *) (var2 - var1));
}

void mul() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    push((void *) (var2 * var1));
}

void divide() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    push((void *) (var2 / var1));
}

void mod() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    push((void *) (var2 % var1));
}

void rdint() {
    int var;
    scanf("%d", &var);
    push((void *) var);
}

void wrint() {
    printf("%d", (int) pop());
}

void rdchr() {
    char var;
    scanf("%c", &var);
    push((void *) var);
}

void wrchr() {
    printf("%c", (int) pop());
}

void popg(int var) {
    staticPtr[var] = (int) pop();
}

void pushg(int var) {
    if (sp != 1000) {
        push((void *) staticPtr[var]);
    }
}

void asf(int value) {
    push((void *) fp);
    fp = sp;
    sp = sp + value;
}

void rsf() {
    sp = fp;
    fp = (int) pop();
}


void pushl(int value) {
    if (sp != 1000) {
        calculationStack[sp].u.number = calculationStack[fp + value].u.number;
        sp = sp + 1;
    }
}

void popl(int value) {
    calculationStack[fp + value].u.number = pop();
}

void popr() {
    reg[0] = pop();
}

void pushr() {
    push((void *) (int) reg[0]);
}

void drop(int var) {
    sp = sp - var;
}

void ret() {
    pc = (int) pop();
}

void call(int value) {
    push((void *) pc);
    pc = value - 1;
}

void brt(int value) {
    if ((int) pop() == 1) {
        pc = value;
    }
}

void brf(int value) {
    if (pop() == 0) {
        pc = value;
    }
}

void jmp(int value) {
    pc = value;
}

void ge() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    pc = pc - 2;
    if (var2 >= var1) {
        push((void *) true);
    } else {
        push((void *) false);
    }
}

void gt() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    pc = pc - 2;
    if (var2 > var1) {
        push((void *) true);
    } else {
        push((void *) false);
    }
}

void le() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    pc = pc - 2;
    if (var2 <= var1) {
        push((void *) true);
    } else {
        push((void *) false);
    }

}

void lt() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    pc = pc - 2;
    if (var2 < var1) {
        push((void *) true);
    } else {
        push((void *) false);
    }
}

void ne() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    pc = pc - 2;
    if (var1 == var2) {
        push((void *) false);
    } else {
        push((void *) true);
    }
}

void eq() {
    int var1 = (int) pop();
    int var2 = (int) pop();
    pc = pc - 2;
    if (var1 != var2) {
        push((void *) false);
    } else {
        push((void *) true);
    }
}

void haltProgram(void) {
    haltThis = true;
}
