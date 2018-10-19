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


int programMemory[9999];
int calculationStack[9999];
int pc; // program counter
int si; // stack counter
unsigned int zahl; // natürliche Zahl

void calculate(int opCode) {
    if (opCode == 2) {
        // addition mit stack durchführen
    }
    if (opCode == 3) {
        // subtraktion mit stack durchführen
    }
    if (opCode == 4) {
        // multiplikation stack durchführen
    }
    if (opCode == 5) {
        // division mit stack durchführen
    }
    if (opCode == 6) {
        // ganzzahldivision mit stack durchführen
    }
}

void data(int opCode) {
    if (opCode == 7) {
        // zahl einlesen
    }
    if (opCode == 8) {
        // zahl ausgeben, stack verringern
    }
    if (opCode == 9) {
        // char einlesen
    }
    if (opCode == 9) {
        // char ausgeben, stack verringern
    }
}

unsigned int addNumber(unsigned int value) {
    value = calculationStack[si];
    si++;
}

int main(int argcount, char *argvector[]) {


    printf("Ninja Virtual Machine started\n");
    for (pc = 0; pc < argcount; pc++) {
        if (programMemory[pc] ==  PUSHC){
            addNumber[pc + 1];
            addNumber[pc + 2];
            printf("BEFEHL");
        }
        else if (programMemory[pc] ==  HALT){
            exit;
            printf("HALT");
        }
        else if (programMemory[pc] ==  ADD){
            calculate( ADD);
            printf("ADD");
        }
        else if (programMemory[pc] ==  SUB){
            calculate( SUB);
            printf("SUB");
        }
        else if (programMemory[pc] ==  MUL){
            calculate( MUL);
            printf("MUL");
        }
        else if (programMemory[pc] ==  DIV){
            calculate( DIV);
            printf("DIV");
        }
        else if (programMemory[pc] ==  MOD){
            calculate( MOD);
            printf("MOD");
        }
        else if (programMemory[pc] ==  RDINT){
            data( RDINT);
            printf("RDINT");
        }
        else if (programMemory[pc] ==  WRINT){
            data( WRINT);
            printf("WRINT");
        }
        else if (programMemory[pc] ==  RDCHR){
            data( RDCHR);
            printf("RDCHR");
        }
        else if (programMemory[pc] ==  WRCHR){
            data( WRCHR);
            printf("WRCHR");
        }
        else if (!strcmp(argvector[pc], "--version")) {
            printf("Version 1\n");
        } else if (!strcmp(argvector[pc], "--help")) {
            printf("Valid inputs: \n --version \n --help\n");
        } else if (!strcmp(argvector[pc], "1")) {
            printf("... \n");
        } else if (!strcmp(argvector[pc], "2")) {
            printf("... \n");
        } else if (!strcmp(argvector[pc], "3")) {
            printf("... \n");
        }
    }
    printf("End of input reached\n");
    printf("Ninja Virtual Machine stopped\n");
    return EXIT_SUCCESS;
}



/* ToDo
 * 1. Die Programme 1-3 werden in der Kommandozeile übergeben
 * 2. Mit #define wird die Funktionalität der VM erweitert
 * 3. Anschließend müssen die index-Stellen im counter mit den bekannten Instruktionen gematched werden
 */