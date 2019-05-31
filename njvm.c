/* njvm1.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "protofunctions.h"

/* Makro-Deklarationen */
#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10
#define PUSHG 11
#define POPG 12
#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16
#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22
#define JMP 23
#define BRF 24
#define BRT 25
#define CALL 26
#define RET  27
#define DROP 28
#define PUSHR 29
#define POPR 30
#define DUP 31

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
/* 0x00800000 -> 8 checks the sign (+ or -) */
/* 0xFF000000 -> Fills the OpCode with 1 */
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

/**
 * Main Function, which reads all Terminal Arguments
 * Valid Arguments start more specific VM functions
 * @param argcount
 * @param argvector
 * @return
 */
int main(int argc, char *argv[]) {
    unsigned int instr;
    int reader = 0;
    char bin[] = ".bin";
    char debug[] = "--debug";
    FILE *loadedFile = NULL;
    char validBinFile[5];
    unsigned int programHeader[3];

    /* Stops the NinjaVM if there is no input */
    if (argc == 1) {
        printf("Error: no code file specified\n");
        return (EXIT_FAILURE);

        /* Prints the current VM-Version */
    } else if (!strcmp(argv[1], "--version")) {
        printf("Ninja Virtual Machine version %d (compiled Oct  2 2018, 11:20:07)\n", version);
        return (EXIT_SUCCESS);

        /* Prints all valid shell commands */
    } else if (!strcmp(argv[1], "--help")) {
        printf("Usage: ./njvm [options] <code file> \nOptions:\n"
               "  --debug          start virtual machine in debug mode\n"
               "  --version        show version and exit\n"
               "  --help           show this help and exit\n");
        return (EXIT_SUCCESS);

        /* Searches the arguments for a binary file" */
    } else if (argc == 2) {
        if (strstr(argv[1], bin) == NULL) {
            printf("Error: no code file specified\n");
            return (EXIT_FAILURE);
        } else {
            loadedFile = fopen(argv[1], "r");
        }
        if (!loadedFile) {
            printf("Error: Code file '%s' cannot be opened \n", argv[1]);
        }
        /* Checks if the binary file is a valid Ninja-Binary file */
        fread(&validBinFile[reader], sizeof(char), 4, loadedFile);
        if (strncmp(&validBinFile[0], "N", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[1], "J", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[2], "B", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[3], "F", 1) != 0) {
            haltProgram();

        }

        /* Reads the File VM-version */
        fread(&programHeader[0], sizeof(unsigned int), 1, loadedFile);
        if (version < programHeader[0]) {
            printf("Version: %d is not supported!", programHeader[0]);
            return (EXIT_FAILURE);
        }
        /* Reads the amount of instructions inside the File */
        fread(&programHeader[1], sizeof(unsigned int), 1, loadedFile);
        instructionCount = programHeader[1];

        /* Reads the amount of global variables inside the File */
        fread(&programHeader[2], sizeof(unsigned int), 1, loadedFile);
        staticAreaSize = programHeader[2];

        staticPtr = malloc(staticAreaSize * sizeof(unsigned int));
        programMemory = malloc(instructionCount * sizeof(unsigned int));

        fread(programMemory, sizeof(unsigned int), instructionCount, loadedFile);
        fclose(loadedFile);
        printf("Ninja Virtual Machine started\n");

        while (!haltThis) {
            instr = programMemory[pc];
            matchInstruction(instr);
        }
    } else if (argc == 3) {
        if (strstr(argv[1], debug) != NULL) {
            debugMode = true;
        } else if (strstr(argv[2], debug) != NULL) {
            debugMode = true;
        }
        if (strstr(argv[1], bin) != NULL) {
            loadedFile = fopen(argv[1], "rb");
        } else if (strstr(argv[2], bin) != NULL) {
            loadedFile = fopen(argv[2], "rb");
        }
        if (!loadedFile) {
            printf("Error: Code file '%s' cannot be opened \n", argv[1]);
        }

        /* Checks if the binary file is a valid Ninja-Binary file */
        fread(&validBinFile[reader], sizeof(char), 4, loadedFile);
        if (strncmp(&validBinFile[0], "N", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[1], "J", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[2], "B", 1) != 0) {
            haltProgram();
        }
        if (strncmp(&validBinFile[3], "F", 1) != 0) {
            haltProgram();

        }

        /* Reads the File VM-version */
        fread(&programHeader[0], sizeof(unsigned int), 1, loadedFile);
        if (version < programHeader[0]) {
            printf("Version: %d is not supported!", programHeader[0]);
            return (EXIT_FAILURE);
        }
        /* Reads the amount of instructions inside the File */
        fread(&programHeader[1], sizeof(unsigned int), 1, loadedFile);
        instructionCount = programHeader[1];

        /* Reads the amount of global variables inside the File */
        fread(&programHeader[2], sizeof(unsigned int), 1, loadedFile);
        staticAreaSize = programHeader[2];

        staticPtr = malloc(staticAreaSize * sizeof(unsigned int));
        programMemory = malloc(instructionCount * sizeof(unsigned int));

        fread(programMemory, sizeof(unsigned int), instructionCount, loadedFile);
        fclose(loadedFile);
        printf("Ninja Virtual Machine started\n");

        while (!haltThis) {
            instr = programMemory[pc];
            matchInstruction(instr);
        }
        if (debugMode == true) {
            printf("DEBUG: file %s loaded ", "Filename ToDo");
            printf("(code size = %d, ", instructionCount);
            printf("data size = %d)\n", staticAreaSize);
            pc = 0;
            while (pc < instructionCount) {
                instr = programMemory[pc];
                debugger(instr);
                pc++;
            }
        }
    }
    printf("Ninja Virtual Machine stopped\n");
    return (EXIT_SUCCESS);
}

/*
 * ToDo implement a debugger with a proper instructionset
 */
void debugger(int instr) {
    char *commands[6] = {"list", "quit"};
    char *input = (char*) malloc(12);
    printf("DEBUG: step, list, quit?\n");
    scanf("%s", input);

    /*
     * run till end without stop
     * run next instruction
     */
    /* show Stack */
    /* printf(calculationStack); */

    /* show static Variables */
    /* printf(staticPtr); */

    /* list instructions */
    if (strcmp(input, commands[0]) == 0) {
        debugInstructions(instr);
    }
    if (strcmp(input, commands[1]) == 1) {
        while (pc < instructionCount) {
            debugInstructions(instr);
        } haltProgram();
    } else {
        haltProgram();
    }

    /* exit VM */
    /* exit(EXIT_SUCCESS); */

}

/**
 *
 * @return
 */
void matchInstruction(unsigned int instr) {
    int value = SIGN_EXTEND(IMMEDIATE(programMemory[pc]));
    int shift = instr>>24;
    int shifter = (SIGN_EXTEND(IMMEDIATE(shift)));
    if (shift == PUSHC) {
        push(value);
        pc++;
        return;
    }
    if (shift == HALT) {
        haltProgram();
        pc++;
        return;
    }
    if (shift == ADD) {
        add();
        pc++;
        return;
    }
    if (shift == SUB) {
        sub();
        pc++;
        return;
    }
    if (shift == MUL) {
        mul();
        pc++;
        return;
    }
    if (shift == DIV) {
        divide();
        pc++;
        return;
    }
    if (shift == MOD) {
        mod();
        pc++;
        return;
    }
    if (shift == RDINT) {
        rdint();
        pc++;
        return;
    }
    if (shift == WRINT) {
        wrint();
        pc++;
        return;
    }
    if (shift == RDCHR) {
        rdchr();
        pc++;
        return;
    }
    if (shift == WRCHR) {
        wrchr();
        pc++;
        return;
    }
    if (shift == PUSHG) {
        pushg(value);
        pc++;
        return;
    }
    if (shift == POPG) {
        popg(value);
        pc++;
        return;
    }
    if (shift == ASF) {
        asf(value);
        pc++;
        return;
    }
    if (shift == RSF) {
        rsf();
        pc++;
        return;
    }
    if (shift == PUSHL) {
        pushl(value);
        pc++;
        return;
    }
    if (shift == POPL) {
        popl(value);
        pc++;
        return;
    }
    if (shift == EQ) {
        eq();
        pc++;
        return;
    }
    if (shift == NE) {
        ne();
        pc++;
        return;
    }
    if (shift == LT) {
        lt();
        pc++;
        return;
    }
    if (shift == LE) {
        le();
        pc++;
        return;
    }
    if (shift == GT) {
        gt();
        pc++;
        return;
    }
    if (shift == GE) {
        ge();
        pc++;
        return;
    }
    if (shift == JMP) {
        jmp(shifter);
        pc++;
        return;
    }
    if (shift == BRF) {
        brf(shifter);
        pc++;
        return;
    }
    if (shift == BRT) {
        brt(shifter);
        pc++;
        return;
    }
    if (shift == CALL) {
        call(value);
        pc++;
        return;
    }
    if (shift == RET) {
        ret();
        pc++;
        return;
    }
    if (shift == PUSHR) {
        pushr();
        pc++;
        return;
    }
    if (shift == POPR) {
        popr();
        pc++;
        return;
    }
    if (shift == DROP) {
        drop(value);
        pc++;
        return;
    }
}


/**
 * ONLY DEBUG
 * This method outputs all instructions inside a given program.
 * The listing order is from top to bottom.
 */

void debugInstructions(unsigned int inst) {
    int value = SIGN_EXTEND(IMMEDIATE(programMemory[pc]));
    switch (inst >> 24) {
        case HALT:
            printf("%d: HALT\n", pc);
            break;
        case PUSHC:
            printf("%d: PUSHC\t %u \n", pc, (value & 0x00FFFFFF));
            break;
        case ADD:
            printf("%d: ADD\n", pc);
            break;
        case SUB:
            printf("%d: SUB\n", pc);
            break;
        case MUL:
            printf("%d: MUL\n", pc);
            break;
        case DIV:
            printf("%d: DIV1\n", pc);
            break;
        case MOD:
            printf("%d: MOD\n", pc);
            break;
        case RDINT:
            printf("%d: RDINT\n", pc);
            break;
        case WRINT:
            printf("%d: WRINT\n", pc);
            break;
        case RDCHR:
            printf("%d: RDCHR\n", pc);
            break;
        case WRCHR:
            printf("%d: WRCHR\n", pc);
            break;
        case PUSHG:
            printf("%d: PUSHG\t %u \n", pc, (value));
            break;
        case POPG:
            printf("%d: POPG\t %u \n", pc, (value));
            break;
        case ASF:
            printf("%d: ASF\t %u \n", pc, (value));
            break;
        case RSF:
            printf("%d: RSF\n", pc);
            break;
        case PUSHL:
            printf("%d: PUSHL\t %u \n", pc, (value));
            break;
        case POPL:
            printf("%d: POPL\t %u \n", pc, (value));
            break;
        case EQ:
            printf("%d: EQ\n", pc);
            break;
        case NE:
            printf("%d: NE\n", pc);
            break;
        case LT:
            printf("%d: LT\n", pc);
            break;
        case LE:
            printf("%d: LE\n", pc);
            break;
        case GT:
            printf("%d: GT\n", pc);
            break;
        case GE:
            printf("%d: GE\n", pc);
            break;
        case JMP:
            printf("%d: JMP\t %u \n", pc, (value));
            break;
        case BRF:
            printf("%d: BRF\t %u \n", pc, (value));
            break;
        case BRT:
            printf("%d: BRT\t %u \n", pc, (value));
            break;
        case CALL:
            printf("%d: CALL\t %u \n", pc, (value));
            break;
        case RET:
            printf("%d: RET\n", pc);
            break;
        case DROP:
            printf("%d: DROP\t %u \n", pc, (value));
            break;
        case PUSHR:
            printf("%d: PUSHR\n", pc);
            break;
        case POPR:
            printf("%d: POPR\n", pc);
            break;
        case DUP:
            printf("%d: DUP\n", pc);
            break;
        default:
            printf("Wert ungültig \n");

            if ((programMemory[pc] & 0xFF000000) == HALT) { break; }
    }
}