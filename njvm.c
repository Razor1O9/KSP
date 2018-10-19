/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <protofunctions.h>

// Makro-Deklarationen
#define <HALT><0>
#define <PUSHC>(<int>)<1>
#define <ADD><2>
#define <SUB><3>
#define <MUL><4>
#define <DIV><5>
#define <MOD><6>
#define <RDINT><7>
#define <WRINT><8>
#define <RDCHR><9>
#define <WRCHR><10>


int programMemory[9999]; // Befehlsliste
int pc; // program counter

int calculationStack[9999]; // Rechnerstack
int si; // stack index

unsigned int zahl; // natürliche Zahl
char letter; // character

void calculate(int opCode) {
    if (opCode == 2) {
        calculationStack [si-1] = calculationStack[si-1] + calculationStack [si];
    }
    if (opCode == 3) {
        calculationStack [si-1] = calculationStack[si-1] - calculationStack [si];
    }
    if (opCode == 4) {
        calculationStack [si-1] = calculationStack[si-1] * calculationStack [si];
    }
    if (opCode == 5) {
        calculationStack [si-1] = calculationStack[si-1] / calculationStack [si];
    }
    if (opCode == 6) {
        // ToDo Ganzzahldivision
        calculationStack [si-1] = calculationStack[si-1] / calculationStack [si];
    }
}

void data(int opCode) {
    if (opCode == 7) {
        // zahl einlesen
    }
    if (opCode == 8) {
        printf(zahl);
        si--;
    }
    if (opCode == 9) {
        // char einlesen
    }
    if (opCode == 9) {
        printf(letter);
        si--;
    }
}
int main(int argcount, char *argvector[]) {


    printf("Ninja Virtual Machine started\n");
    for (pc = 0; pc < argcount; pc++) {
        if (programMemory[pc] ==  PUSHC){
            pc++;
            zahl = programMemory[pc];
            calculationStack[pc] = zahl;
        }
        else if (programMemory[pc] ==  HALT){
            exit;
            printf("HALT \n");
        }
        else if (programMemory[pc] ==  ADD){
            calculate( ADD);
            printf("ADD \n");
        }
        else if (programMemory[pc] ==  SUB){
            calculate( SUB);
            printf("SUB \n");
        }
        else if (programMemory[pc] ==  MUL){
            calculate( MUL);
            printf("MUL");
        }
        else if (programMemory[pc] ==  DIV){
            calculate( DIV);
            printf("DIV \n");
        }
        else if (programMemory[pc] ==  MOD){
            calculate( MOD);
            printf("MOD \n");
        }
        else if (programMemory[pc] ==  RDINT){
            data( RDINT);
            printf("RDINT \n");
        }
        else if (programMemory[pc] ==  WRINT){
            data( WRINT);
            printf("WRINT \n");
        }
        else if (programMemory[pc] ==  RDCHR){
            data( RDCHR);
            printf("RDCHR \n");
        }
        else if (programMemory[pc] ==  WRCHR){
            data( WRCHR);
            printf("WRCHR \n");
        }
        else if (!strcmp(argvector[pc], "--version")) {
            printf("Version 1\n");
        }
        else if (!strcmp(argvector[pc], "--help")) {
            printf("Valid inputs: \n --version \n --help\n");
        }
        else if (!strcmp(argvector[pc], "1")) {
            printf("... \n");
        }
        else if (!strcmp(argvector[pc], "2")) {
            printf("... \n");
        }
        else if (!strcmp(argvector[pc], "3")) {
            printf("... \n");
        }
    }
    printf("End of input reached\n");
    printf("Ninja Virtual Machine stopped\n");
    return EXIT_SUCCESS;
}