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

int main(int argcount, char *argvector[]) {
    int[9999] programMemory;
    int[9999] calculationStack;
    int pc; // program counter
    unsigned int zahl; // natürliche Zahl

    printf("Ninja Virtual Machine started\n");
    for(pc=0; pc < argcount; pc++) {
        if (programMemory [pc] ==  PUSHC){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  HALT){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  ADD){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  SUB){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  MUL){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  DIV){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  MOD){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  RDINT){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  WRINT){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  RDCHR){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if (programMemory [pc] ==  WRCHR){
            // ToDo Befehl weitergeben und mit Stack rechnen
            printf("BEFEHL");
        }
        if(!strcmp(argvector[pc], zahl)) {
            calculationStack[pc] = zahl;
        }
        if(!strcmp(argvector[pc], "--version")) {
            printf("Version 1\n");
        }
        else if(!strcmp(argvector[pc], "--help")) {
            printf("Valid inputs: \n --version \n --help\n");
        }
        else if(!strcmp(argvector[pc], "1")) {
            printf("... \n");
        }
        else if(!strcmp(argvector[pc], "2")) {
            printf("... \n");
        }
        else if(!strcmp(argvector[pc], "3")) {
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