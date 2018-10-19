/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <protofunctions.h>
#define <PUSHC>(<int>)<1>
#define <HALT><0>
#define <ADD><2>
#define <SUB><3>
#define <MUL><4>
#define <DIV><5>
#define <MOD><6>
#define <RDINT><7>
#define <WRINT><8>
#define <RDCHR><9>
#define <WRCHR><10>

int main(int argcount, char *argvector[]) {
    int[9999] programMemory;
    int[9999] calculationStack;
    int programCounter = 0; // test
    int i;
    int sum
    printf("Ninja Virtual Machine started\n");
    sum = ADD ( stack1 + stack2 );
    for(i=0; i < argcount; i++) {
        if(!strcmp(argvector[i], "--version")) {
            printf("Version 1\n");
        }
        else if(!strcmp(argvector[i], "--help")) {
            printf("Valid inputs: \n --version \n --help\n");
        }
        else if(!strcmp(argvector[i], "1")) {
            printf("... \n");
        }
        else if(!strcmp(argvector[i], "2")) {
            printf("... \n");
        }
        else if(!strcmp(argvector[i], "3")) {
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
 * /