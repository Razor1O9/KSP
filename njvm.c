#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bigint/build/include/bigint.h"
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
    char *filename = "";
    char *command = "";
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
            printf("Version: %d is not supported!\n", programHeader[0]);
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
            pc++;
        }
    } else if (argc == 3) {
        if (strstr(argv[1], debug) != NULL) {
            debugMode = true;
            filename = argv[2];
        } else if (strstr(argv[2], debug) != NULL) {
            debugMode = true;
            filename = argv[1];
        } else {
            if (strstr(argv[1], bin) != NULL) {
                command = argv[2];
                printf("Error: unknown option '%s', try './njvm --help'\n", command);
                return EXIT_FAILURE;
            }
            if (strstr(argv[2], bin) != NULL) {
                command = argv[1];
                printf("Error: unknown option '%s', try './njvm --help'\n", command);
                return EXIT_FAILURE;
            }
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
            printf("Version: %d is not supported!\n", programHeader[0]);
            return (EXIT_FAILURE);
        }
        /* Reads the amount of instructions inside the File */
        fread(&programHeader[1], sizeof(unsigned int), 1, loadedFile);
        instructionCount = programHeader[1];

        /* Reads the amount of global variables inside the File */
        fread(&programHeader[2], sizeof(unsigned int), 1, loadedFile);
        staticAreaSize = programHeader[2];

        staticPtr = malloc(staticAreaSize * sizeof(ObjRef));
        programMemory = malloc(instructionCount * sizeof(unsigned int));

        fread(programMemory, sizeof(unsigned int), instructionCount, loadedFile);
        fclose(loadedFile);
        printf("Ninja Virtual Machine started\n");

        while (!haltThis) {
            if (debugMode == true) {
                printf("DEBUG: file %s loaded ", filename);
                printf("(code size = %d, ", instructionCount);
                printf("data size = %d)\n", staticAreaSize);
                for (int i = 0; i < instructionCount; i++) {
                    if (debugMode == false) {
                        /* small Hack :) */
                        i = instructionCount;
                    } else {
                        instr = programMemory[dc];
                        debugger(instr);
                        dc++;
                    }
                }
            } else {
                if (dc == breakpoint) {
                    if (debugMode == true) {
                        printf("DEBUG: file %s loaded ", filename);
                        printf("(code size = %d, ", instructionCount);
                        printf("data size = %d)\n", staticAreaSize);
                        for (int i = 0; i < instructionCount; i++) {
                            if (debugMode == false) {
                                /* small Hack :) */
                                i = instructionCount;
                            } else {
                                instr = programMemory[dc];
                                debugger(instr);
                                dc++;
                            }
                        }
                    } else {
                        instr = programMemory[pc];
                        matchInstruction(instr);
                        pc++;
                    }

                } else {
                    instr = programMemory[pc];
                    matchInstruction(instr);
                    pc++;
                }
            }

        }
    }
    printf("Ninja Virtual Machine stopped\n");
    return (EXIT_SUCCESS);
}

void debugger(int instr) {
    char *commands[6] = {"inspect", "list", "breakpoint", "step", "run", "quit"};
    char *options[3] = {"stack", "data", "object"};
    char *breakpoint_options[2] = {"-1", "ret"};
    char *input = (char *) malloc(12);
    char *inputNum = (char *) malloc(12);

    printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
    scanf("%s", input);

    /* INSPECT ToDo */
    if (strcmp(input, commands[0]) == 0) {
        printf("DEBUG [inspect]: stack, data, object?\n");
        scanf("%s", input);
        if (strcmp(input, options[0]) == 0) {
            int copySP = sp;
            if (fp == sp) {
                printf("FP, SP --> [%d]: (xxxxxx) xxxxxx\n", copySP);
                copySP--;
            } else {
                printf("SP   -->   [%d]: (xxxxxx) xxxxxx\n", copySP);
                copySP--;
            }
            for (int i = copySP; i > 0; i--) {
                if (fp == copySP) {
                    printf("FP    -->  [%d]: ", fp);
                    if (calculationStack[copySP].isObjRef == true) {
                        printf("(objref) %p\n", (void *) &calculationStack[fp].u.objRef);
                    } else if (calculationStack[copySP].isObjRef == false) {
                        printf("(number) %d\n", calculationStack[fp].u.number);
                    }
                } else if (copySP >= 0) {
                    printf("           [%d]: ", copySP);
                    if (calculationStack[copySP].isObjRef == true) {
                        printf("(objref) %p\n", (void *) &calculationStack[copySP].u.objRef);
                    } else if (calculationStack[copySP].isObjRef == false) {
                        printf("(number) %d\n", calculationStack[copySP].u.number);
                    }
                }
                copySP--;
                printf("--- bottom of stack ---\n");
            }
        } else if (strcmp(input, options[1]) == 0) {
            printf("--- end of data ---\n");
            // ToDo
            //printf("%s", (const char *) staticPtr);
        } else if (strcmp(input, options[2]) == 0) {
            printf("Object reference?");
            scanf("%s", input);
            // ToDo
        } else {
            printf("Command invalid");
        }
    }
        /* LIST */
    else if (strcmp(input, commands[1]) == 0) {
        int i = 0;
        int old_dc = dc;
        dc = 0;
        while (i < instructionCount) {
            instr = programMemory[dc];
            debugInstructions(instr);
            dc++;
            i++;
        }
        dc = --old_dc;
        printf("--- end of code ---\n");
    } else if (strcmp(input, commands[2]) == 0) {
        if (breakpoint == false) {
            printf("DEBUG [breakpoint]: cleared\n");
            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
            scanf("%s", inputNum);
            // Breakpoint gets cleared
            if (strcmp(inputNum, breakpoint_options[0]) == 0) {
                breakpoint_pos = 0;
                breakpoint = false;
                printf("DEBUG [breakpoint]: now cleared\n");
                return;
            } else if (strcmp(inputNum, breakpoint_options[1]) == 0) {
                return;
            } else {
                breakpoint_pos = (int) *inputNum - 48;
                if (breakpoint_pos > instructionCount) {
                    printf("DEBUG [breakpoint]: Breakpoint position not valid!\n");
                    breakpoint_pos = 0;
                    breakpoint = false;
                    return;
                } else {
                    /* Set Breakpoint to user input */
                    breakpoint = true;
                    printf("DEBUG [breakpoint]: now set at %d\n", breakpoint_pos);
                    return;
                }
            }

        } else {
            printf("DEBUG [breakpoint]: set at %d\n", breakpoint_pos);
            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
            scanf("%s", inputNum);
            // Breakpoint gets cleared
            if (strcmp((const char *) inputNum, breakpoint_options[0]) == 0) {
                breakpoint_pos = 0;
                breakpoint = false;
                printf("DEBUG [breakpoint]: now cleared\n");
                return;
            } else if (strcmp((const char *) inputNum, breakpoint_options[1]) == 0) {
                return;
            } else {
                breakpoint_pos = (int) *inputNum - 48;
                if (breakpoint_pos > instructionCount) {
                    printf("DEBUG [breakpoint]: Breakpoint position not valid!\n");
                    breakpoint_pos = 0;
                    breakpoint = false;
                    return;
                } else {
                    /* Set Breakpoint to user input */
                    breakpoint = true;
                    printf("DEBUG [breakpoint]: now set at %d\n", breakpoint_pos);
                    return;
                }
            }
        }
    }
/* Step */
    else if (
            strcmp(input, commands[3]
            ) == 0) {
        matchInstruction(instr);
        debugInstructions(instr);
    }
/* RUN */
    else if (
            strcmp(input, commands[4]
            ) == 0) {
        debugMode = false;
    }
/* QUIT*/
    else if (
            strcmp(input, commands[5]
            ) == 0) {
        printf("Ninja Virtual Machine stopped\n");
        exit(EXIT_SUCCESS);
    }
}

/**
 *
 * @return
 */
void matchInstruction(unsigned int instr) {
    int value = SIGN_EXTEND(IMMEDIATE(programMemory[pc]));
    int shift = instr >> 24;
    if (shift == PUSHC) {
        bigFromInt(value);
        pushObject(bip.res);
        return;
    }
    if (shift == HALT) {
        haltProgram();
        return;
    }
    if (shift == ADD) {
        add();
        return;
    }
    if (shift == SUB) {
        sub();
        return;
    }
    if (shift == MUL) {
        mul();
        return;
    }
    if (shift == DIV) {
        divide();
        pc++;
        return;
    }
    if (shift == MOD) {
        mod();
        return;
    }
    if (shift == RDINT) {
        rdint();
        return;
    }
    if (shift == WRINT) {
        wrint();
        return;
    }
    if (shift == RDCHR) {
        rdchr();
        return;
    }
    if (shift == WRCHR) {
        wrchr();
        return;
    }
    if (shift == PUSHG) {
        pushg(value);
        return;
    }
    if (shift == POPG) {
        popg(value);
        return;
    }
    if (shift == ASF) {
        asf(value);
        return;
    }
    if (shift == RSF) {
        rsf();
        return;
    }
    if (shift == PUSHL) {
        pushl(value);
        return;
    }
    if (shift == POPL) {
        popl(value);
        return;
    }
    if (shift == EQ) {
        eq();
        return;
    }
    if (shift == NE) {
        ne();
        return;
    }
    if (shift == LT) {
        lt();
        return;
    }
    if (shift == LE) {
        le();
        return;
    }
    if (shift == GT) {
        gt();
        return;
    }
    if (shift == GE) {
        ge();
        return;
    }
    if (shift == JMP) {
        jmp(value);
        return;
    }
    if (shift == BRF) {
        brf(value);
        return;
    }
    if (shift == BRT) {
        brt(value);
        return;
    }
    if (shift == CALL) {
        call(value);
        return;
    }
    if (shift == RET) {
        ret();
        return;
    }
    if (shift == PUSHR) {
        pushr();
        return;
    }
    if (shift == POPR) {
        popr();
        return;
    }
    if (shift == DROP) {
        drop(value);
        return;
    }
}


/**
 * ONLY DEBUG
 * This method outputs all instructions inside a given program.
 * The listing order is from top to bottom.
 */

void debugInstructions(unsigned int inst) {
    int value = SIGN_EXTEND(IMMEDIATE(programMemory[dc]));
    switch (inst >> 24) {
        case HALT:
            printf("%d: HALT\n", dc);
            break;
        case PUSHC:
            printf("%d: PUSHC\t %d \n", dc, (value));
            break;
        case ADD:
            printf("%d: ADD\n", dc);
            break;
        case SUB:
            printf("%d: SUB\n", dc);
            break;
        case MUL:
            printf("%d: MUL\n", dc);
            break;
        case DIV:
            printf("%d: DIV1\n", dc);
            break;
        case MOD:
            printf("%d: MOD\n", dc);
            break;
        case RDINT:
            printf("%d: RDINT\n", dc);
            break;
        case WRINT:
            printf("%d: WRINT\n", dc);
            break;
        case RDCHR:
            printf("%d: RDCHR\n", dc);
            break;
        case WRCHR:
            printf("%d: WRCHR\n", dc);
            break;
        case PUSHG:
            printf("%d: PUSHG\t %d \n", dc, (value));
            break;
        case POPG:
            printf("%d: POPG\t %d \n", dc, (value));
            break;
        case ASF:
            printf("%d: ASF\t %d \n", dc, (value));
            break;
        case RSF:
            printf("%d: RSF\n", dc);
            break;
        case PUSHL:
            printf("%d: PUSHL\t %d \n", dc, (value));
            break;
        case POPL:
            printf("%d: POPL\t %d \n", dc, (value));
            break;
        case EQ:
            printf("%d: EQ\n", dc);
            break;
        case NE:
            printf("%d: NE\n", dc);
            break;
        case LT:
            printf("%d: LT\n", dc);
            break;
        case LE:
            printf("%d: LE\n", dc);
            break;
        case GT:
            printf("%d: GT\n", dc);
            break;
        case GE:
            printf("%d: GE\n", dc);
            break;
        case JMP:
            printf("%d: JMP\t %d \n", dc, (value));
            break;
        case BRF:
            printf("%d: BRF\t %d \n", dc, (value));
            break;
        case BRT:
            printf("%d: BRT\t %d \n", dc, (value));
            break;
        case CALL:
            printf("%d: CALL\t %d \n", dc, (value));
            break;
        case RET:
            printf("%d: RET\n", dc);
            break;
        case DROP:
            printf("%d: DROP\t %d \n", dc, (value));
            break;
        case PUSHR:
            printf("%d: PUSHR\n", dc);
            break;
        case POPR:
            printf("%d: POPR\n", dc);
            break;
        case DUP:
            printf("%d: DUP\n", dc);
            break;
        default:
            printf("Wert ungültig \n");

            if ((programMemory[pc] & 0xFF000000) == HALT) { break; }
    }
}
