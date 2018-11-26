#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "njvm.h"
#include "bigint/bigint.h"
#include "bigint/bigint.c"
#include "bigint/support.h"

StackSlot *stack; /*stack */
int stackSize;
int PC; /*program counter */
int SP; /*stack pointer */
int FP; /*frame pointer */
StackSlot *staticDataArea; /*static data area (holds global vars) */
ReturnRegister returnRegister; /*return value register (holds method return values) */


int main(int argc, char *argv [])
{
    
    /*manage parameter input */
  {
        if (strcmp(argv[1], ARG_VERSION) == 0)
        {
            printf("Current Version: %d\n", NJVM_VERSION);
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argv[1], ARG_HELP) == 0)
        {
            printHelp();
            exit(EXIT_SUCCESS);
        }
        else if(argc == 3 && strcmp(argv[2], DEBUG_MODE) == 0)
        {
            stackSize = STACK_SIZE;
            stack = malloc(stackSize * 1024 * sizeof(char));
            loadProgram(argv[1],true);
        }
        else if(argc == 4 && strcmp(argv[2], ARG_STACK_SIZE) == 0)
        {
            stackSize = atoi(argv[3]);
            stack = malloc(stackSize * 1024 * sizeof(char));
            loadProgram(argv[1],false);
        }
        else {
            stackSize = STACK_SIZE;
            stack = malloc(stackSize * 1024 * sizeof(char));
            loadProgram(argv[1],false);
        }


  }
  
  exit(EXIT_SUCCESS);
  
}

/*
 * prints a simple help screen
 */
void printHelp(void)
{
    printf("Execute Programs:\n");
    printf("njvm [program]\t\t\t executes a program\n");
    printf("njvm [program] %s\t executes a program in debug mode\n", DEBUG_MODE);
    printf("\n");
    printf("Direct Arguments: \n");
	printf("njvm %s\tShows the current version of njvm.\n", ARG_VERSION);
	printf("njvm %s\t\tShows this help screen.\n", ARG_HELP);

    printf("\n");
}

void loadProgram(const char filename[], bool debug  ) {
    FILE *program = fopen(filename, "r");   /*"r" for reading */
    char *format;
    char *expectedString = "NJBF";
    int version;
    int instrSize;
    unsigned int *instructions; /*unsigned Integer containing the instructions */
    int numVars;
    unsigned int instr;
    int i;

    /* return if program does not exist */
    if (program == NULL) {
        printf("File not found! ");
        exit(EXIT_FAILURE);
    }

    /*Read first 4 bytes and check them for correct format */
    format = (char *) malloc(4);
    fread(format, 1, 4, program);
    if (strcmp(format, expectedString) != 0) {
        printf("Incorrect Format!\n");
        exit(EXIT_FAILURE);
    }

    /*Read next 4 bytes and check them for correct Version */
    fread(&version, 4, 1, program);
    if (version > NJVM_VERSION) {
        printf("Your Version is too old!\n");
        exit(EXIT_FAILURE);
    }

    /*Read next 4 bytes and check for the number of instructions */
    fread(&instrSize, 4, 1, program);
    instructions = (unsigned int *) malloc(instrSize * sizeof(int));

    /*Read next 4 bytes and check for the number of vars in static data area*/
    fread(&numVars, 4, 1, program);
    staticDataArea =  malloc(numVars * sizeof(int));

    /*Read the next 4 bytes n times (based on instrSize) */
    i = 0;
    do {
        fread(&instr, 4, 1, program);
        instructions[i] = instr;
        i++;
    } while (i < instrSize);

    PC = 0;
    SP = 0;

    if (debug == true) {
        char *commands[6] = {"inspect", "list", "breakpoint", "step", "run", "quit"};
        char *input = (char*) malloc(12);
        long int breakpoint = -1;
        printf("DEBUG: file %s loaded ", filename);
        printf("(code size = %d, ", instrSize);
        printf("data size = %d)\n", numVars);

        printf("Ninja Virtual Machine started\n");

        /* performs one step after another till user writes "run" or "quit" represented by commands[4] and commands[5] */
        while (strcmp(input, commands[5]) != 0) {

            listInstruction(instructions[PC--]);
            printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
            scanf("%s", input);

            /* inspect */
            if (strcmp(input, commands[0]) == 0)
            {
                printf("DEBUG [inspect]: stack, data?\n");
                scanf("%s", input);

                /* inspect stack */
                if(strcmp(input, "stack") == 0) {
                    int SP_output = SP;
                    if(FP == SP){
                        printf("FP, SP --> [%d]: (xxxxxx) xxxxxx\n",SP_output);
                        SP_output--;
                    }
                    else {
                        printf("SP   -->   [%d]: (xxxxxx) xxxxxx\n", SP_output);
                        SP_output--;
                    }
                    do{
                        if(FP == SP_output) {
                            printf("FP    -->  [%d]: ", FP);
                            if(stack[SP_output].isObjRef == true){
                                printf("(objref) %p\n", (void *)&stack[FP].u.objRef);
                            } else if(stack[SP_output].isObjRef == false){
                                printf("(number) %d\n", stack[FP].u.number);
                            }
                        }
                        else if(SP_output >= 0){
                            printf("           [%d]: ", SP_output);
                            if(stack[SP_output].isObjRef == true){
                                printf("(objref) %p\n", (void *)&stack[SP_output].u.objRef);
                            } else if(stack[SP_output].isObjRef == false){
                                printf("(number) %d\n", stack[SP_output].u.number);
                            }
                        }
                        SP_output--;
                    }while (SP_output >= 0);
                    printf(" -- bottom of stack --\n");
                }

                /* inspect data */
                else if(strcmp(input, "data") == 0) {
                    int a = 0;
                    while(a < numVars) {
                        printf("data[%d]: ", a);
                        printf("(objref) %p\n", (void *)&staticDataArea[a++].u.objRef);
                    }
                    printf("   ---  end of data   ---\n");
                }
                continue;
            }

            /* list */
            if (strcmp(input, commands[1]) == 0) {

                int temp = PC;
                PC = 0;
                listProgram(instructions,instrSize);
                PC = temp;
                printf(" --- end of list ---\n");
                continue;
            }

            /* breakpoint */
            if (strcmp(input, commands[2]) == 0) {
                long int test;
                if(breakpoint == -1)
                    printf("DEBUG [breakpoint]: cleared\n");
                else {
                    printf("DEBUG [breakpoint]: %d\n", (int) breakpoint);
                }
                printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
                scanf("%s", input);
                test = strtol(input, NULL,10);
                while(test == 0 && strcmp(input, "ret") != 0){
                    printf("Invalid command, try again!\n");
                    scanf("%s", input);
                    test = strtol(input, NULL, 10);
                }
                if(strcmp(input, "ret") == 0){
                    printf("DEBUG: no changes made\n");
                    continue;
                } else {
                    if(test == -1){
                        breakpoint = test;
                        printf("DEBUG [breakpoint]: cleared\n");
                    } else {
                        breakpoint = test;
                        printf("DEBUG [breakpoint]: now set at %d\n", (int) breakpoint);
                    }
                }
                continue;
            }

            /* step     */
            else if (strcmp(input, commands[3]) == 0) {
                makeDebugStep(instructions, numVars, 1);
                continue;
            }

            /* run      */
            else if (strcmp(input, commands[4]) == 0) {
                /*if no breakpoint was set */
                if(breakpoint == -1) {
                    executeProgram(instructions, numVars);
                    fclose(program);
                    printf("Ninja Virtual Machine stopped\n");
                    exit(EXIT_SUCCESS);
                } else if(breakpoint > 0) {
                    makeDebugStep(instructions, numVars, (int) breakpoint - PC);
                } else {
                    printf("DEBUG [breakpoint]: set below zero, please set it above zero to continue!\n");
                }

            }
        }
    }

    /* debug = false ->> execute program normal */
    else {
        printf("Ninja Virtual Machine started\n");
        executeProgram(instructions, numVars);
    }

    /* finish execution */
    printf("Ninja Virtual Machine stopped\n");
    fclose(program);
}



/*
 * prints all instructions in program
 */
void listProgram(unsigned int instructions [], int instrSize){

    while(PC < instrSize){
        listInstruction(instructions[PC]);
    }

}

/*
 * converts instruction to string and prints it
 */
void listInstruction(unsigned int instruction){
    switch(instruction >> 24) {
        case HALT:
        {
            printf("HALT\n");
            PC++;
            break;
        }
        case PUSHC:
        {
            printf("PUSHC %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;

        }
        case ADD:
        {
            printf("ADD\n");
            PC++;
            break;
        }
        case SUB:
        {
            printf("SUB\n");
            PC++;
            break;
        }
        case MUL:
        {
            printf("MUL\n");
            PC++;
            break;
        }
        case DIV:
        {
            printf("DIV\n");
            PC++;
            break;
        }
        case MOD:
        {
            printf("MOD\n");
            PC++;
            break;
        }
        case RDINT:
        {
            printf("RDINT\n");
            PC++;
            break;
        }
        case WRINT:
        {
            printf("WRINT\n");
            PC++;
            break;
        }
        case RDCHR:
        {
            printf("RDCHAR\n");
            PC++;
            break;
        }
        case WRCHR:
        {
            printf("WRCHAR\n");
            PC++;
            break;
        }
        case PUSHG:
        {
            printf("PUSHG %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case POPG:
        {
            printf("POPG %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case ASF:
        {
            printf("ASF %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case RSF:
        {
            printf("RSF\n");
            PC++;
            break;
        }
        case PUSHL:
        {
            printf("PUSHL %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case POPL:
        {
            printf("POPL %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case EQ:
        {
            printf("EQ\n");
            PC++;
            break;
        }
        case NE:
        {
            printf("NE\n");
            PC++;
            break;
        }
        case LT:
        {
            printf("LT\n");
            PC++;
            break;
        }
        case LE:
        {
            printf("LE\n");
            PC++;
            break;
        }
        case GT:
        {
            printf("GT\n");
            PC++;
            break;
        }
        case GE:
        {
            printf("GE\n");
            PC++;
            break;
        }
        case JMP:
        {
            printf("JMP %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case BRF:
        {
            printf("BRF %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case BRT:
        {
            printf("BRT %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case CALL:
        {
            printf("CALL %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }case RET:
        {
            printf("BRT \n");
            PC++;
            break;
        }
        case DROP:
        {
            printf("DROP %d\n", (SIGN_EXTEND(instruction & 0x00FFFFFF)));
            PC++;
            break;
        }
        case PUSHR:
        {
            printf("BRT \n");
            PC++;
            break;
        }
        case POPR:
        {
            printf("BRT \n");
            PC++;
            break;
        }
        default:
        {
            printf("Not defined!");
            PC++;
        }
    }
}

/*
 * executes all instructions
 */
void executeProgram(unsigned int instructions [], int staticDataArea_size){
    while(instructions[PC] != HALT){
        execInstruction(instructions[PC], staticDataArea_size);
    }
}

/*
 * executes n commands depending on the size of 'steps'
 */
void makeDebugStep(unsigned int instructions [], int staticDataArea_size, long int steps) {
    while (instructions[PC] != HALT && steps != 0) {
        execInstruction(instructions[PC], staticDataArea_size);
        steps--;
    }
}

/*
 * executes single instruction
 */
void execInstruction(unsigned int instruction_binary, int staticDataArea_size){
    switch(instruction_binary >> 24){
        case PUSHC:
        {
            StackSlot slot;
            slot.isObjRef = true;
            bigFromInt(immediate_value(instruction_binary));
            /*
            unnötig?
            slot.u.objRef = malloc(sizeof(unsigned int) + sizeof(int));
            slot.u.objRef->size = sizeof(int);
             */
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case ADD:
        {
            StackSlot slot;
            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            bigAdd();
            slot.isObjRef = true;
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case SUB:
        {
            StackSlot slot;
            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            bigSub();
            slot.isObjRef = true;
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case MUL:
        {
            StackSlot slot;
            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            bigMul();

            slot.isObjRef = true;
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case DIV:
        {
            StackSlot slot;
            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            if(*(int*)bip.op2->data == 0){
                printf("You are trying to divide with zero. Operation aborted.\n");
                exit(121);
            }

            bigDiv();
            slot.isObjRef = true;
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case MOD:
        {
            StackSlot slot;
            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            bigDiv();

            slot.isObjRef = true;
            slot.u.objRef = bip.rem;
            push(slot);
            PC++;
            break;
        }
        case RDINT:
        {
            StackSlot slot;
            bigRead(stdin);
            slot.isObjRef = true;
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case WRINT:
        {
            bip.op1 = popObjRef();
            bigPrint(stdout);
            PC++;
            break;
        }
        case RDCHR:
        {
            StackSlot slot;
            char chr[1];
            slot.isObjRef = true;
            scanf("%c", chr);
            bigFromInt(chr[0]);
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case WRCHR:
        {
            int num;
            bip.op1 = popObjRef();
            num = bigToInt();
            printf("%c", num);
            PC++;
            break;
        }
        case PUSHG:
        {
            int n = immediate_value(instruction_binary);

            if(n >= staticDataArea_size || n < 0){
                printf("Out of bounds. You're not pointing to an index within the static data area!\n");
            }
            else {
                push(staticDataArea[n]);
            }
            PC++;
            break;
        }
        case POPG:
        {
            int n = immediate_value(instruction_binary);
            if(n >=  staticDataArea_size || n < 0){
                printf("Out of bounds. You're not pointing to an index within the static data area!\n");
            }
            else {
                StackSlot slot;
                slot.isObjRef = true;
                slot.u.objRef = popObjRef();
                staticDataArea[n] = slot;
            }
            PC++;
            break;
        }
        case ASF:
        {
            int n = immediate_value(instruction_binary);
            if(n > STACK_SIZE - 2){
                printf("Stack is too small to hold this stack frame!\n");
            } else if (n < 0){
                printf("Cannot create a stack frame smaller than 1!\n");
            } else {
                StackSlot slot;
                slot.isObjRef = false;
                slot.u.number = FP;
                push(slot);
                FP = SP;
                SP = SP + n; /*allocate new stack frame on stack by size 'n' */
            }
            PC++;
            break;
        }
        case RSF:
        {
            SP = FP;
            FP = popNumber();
            PC++;
            break;
        }
        case PUSHL:
        {
            int n = immediate_value(instruction_binary);
            push(stack[FP + n]);
            PC++;
            break;
        }
        case POPL:
        {
            StackSlot val;
            val.isObjRef = true;
            val.u.objRef= popObjRef();
            stack[FP + immediate_value(instruction_binary)] = val;
            PC++;
            break;
        }
        case EQ:
        {
            StackSlot slot;
            int num;
            slot.isObjRef = true;

            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            num = bigCmp();

            bigFromInt(num == 0 ? 1 : 0);

            slot.u.objRef = bip.res;

            push(slot);
            PC++;
            break;
        }
        case NE:
        {
            StackSlot slot;
            int num;
            slot.isObjRef = true;

            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            num = bigCmp();

            bigFromInt(num != 0 ? 1 : 0);

            slot.u.objRef = bip.res;

            push(slot);
            PC++;
            break;
        }
        case LT:
        {
            StackSlot slot;
            int num;
            int num2;
            slot.isObjRef = true;

            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            num = bigCmp();
            num2 = num < 0 ? 1 : 0;

            bigFromInt(num2);

            slot.u.objRef = bip.res;

            push(slot);
            PC++;
            break;
        }
        case LE:
        {
            StackSlot slot;
            int num;
            slot.isObjRef = true;

            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            num = bigCmp();

            bigFromInt(num <= 0 ? 1 : 0);

            slot.u.objRef = bip.res;

            push(slot);
            PC++;
            break;
        }
        case GT:
        {
            StackSlot slot;
            int num;
            slot.isObjRef = true;

            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            num = bigCmp();

            bigFromInt(num > 0 ? 1 : 0);

            slot.u.objRef = bip.res;

            push(slot);
            PC++;
            break;
        }
        case GE:
        {
            StackSlot slot;
            int num;
            slot.isObjRef = true;

            bip.op2 = popObjRef();
            bip.op1 = popObjRef();

            num = bigCmp();

            bigFromInt(num >= 0 ? 1 : 0);

            slot.u.objRef = bip.res;

            push(slot);
            PC++;
            break;
        }
        case JMP:
        {
            PC = immediate_value(instruction_binary);;
            break;
        }
        case BRF:
        {
            int num;
            bip.op1 = popObjRef();
            num = bigToInt();
            if(num == 0){
                PC = immediate_value(instruction_binary);;
            }
            else if(num == 1){
                PC++;
            }
            else {
                printf("No valid input for boolean (has to be '0' or '1'\n");
                PC++;
            }
            break;
        }
        case BRT:
        {
            int num;
            bip.op1 = popObjRef();
            num = bigToInt();
            if(num == 1){
                PC = immediate_value(instruction_binary);
            }
            else if (num == 0){
                PC++;
            }
            else {
                printf("No valid input for boolean (has to be '0' or '1'\n");
                PC++;
            }
            break;
        }
        case CALL:
        {
            StackSlot slot;
            slot.isObjRef = false;
            slot.u.number = PC + 1;
            push(slot);
            PC = immediate_value(instruction_binary);
            break;
        }case RET:
        {
            int n = popNumber();
            PC = n;
            break;
        }
        case DROP:
        {
            int n = immediate_value(instruction_binary);
            int i = 0;
            while(i < n){
                popObjRef();
                i++;
            }
            PC++;
            break;
        }
        case PUSHR:
        {
            StackSlot slot;
            slot.isObjRef = true;
            slot.u.objRef = malloc(sizeof(unsigned int) + sizeof(int));
            slot.u.objRef->size = sizeof(int);
            slot.u.objRef = returnRegister.this[--returnRegister.size];
            push(slot);
            PC++;
            break;
        }
        case POPR:
        {
            returnRegister.this[returnRegister.size++] = popObjRef();
            PC++;
            break;
        }
        case DUP:
        {
            StackSlot slot;
            slot.isObjRef = true;
            slot.u.objRef = popObjRef();
            push(slot);
            push(slot);
            PC++;
            break;
        }
        case NEW:
        {
            StackSlot slot;
            slot.isObjRef = true;
            slot.u.objRef = newCompoundObject(immediate_value(instruction_binary));
            push(slot);
            PC++;
            break;
        }
        case GETF:
        {
            StackSlot slot;
            slot.u.objRef = popObjRef();
            slot.isObjRef = true;
            slot.u.objRef = *((ObjRef *)slot.u.objRef->data + immediate_value(instruction_binary));
            push(slot);
            PC++;
            break;
        }
        case PUTF:
        {
            ObjRef objRef;
            ObjRef objRef2;
            objRef = popObjRef();
            objRef2 = popObjRef();
            *((ObjRef *)objRef2->data + immediate_value(instruction_binary)) = objRef;
            PC++;
            break;
        }
        case NEWA:
        {
            StackSlot slot;
            ObjRef objRef;
            int size;
            objRef = popObjRef();
            bip.op1 = objRef;
            size = bigToInt();
            slot.isObjRef = true;
            slot.u.objRef = newCompoundObject(size);
            push(slot);
            PC++;
            break;
        }
        case GETFA:
        {
            StackSlot slot;
            int size;
            bip.op1 = popObjRef();
            size = bigToInt();
            slot.u.objRef = popObjRef();
            slot.u.objRef = *((ObjRef *)slot.u.objRef->data + size);
            slot.isObjRef = true;
            push(slot);
            PC++;
            break;
        }
        case PUTFA:
        {
            ObjRef objRef;
            ObjRef objRef2;
            int size;
            objRef = popObjRef();
            bip.op1 = popObjRef();
            size = bigToInt();
            objRef2 = popObjRef();
            *((ObjRef *)objRef2->data + size) = objRef;
            PC++;
            break;
        }
        case GETSZ:
        {
            StackSlot slot;
            ObjRef objRef;
            objRef = popObjRef();
            slot.isObjRef = true;

            if(IS_PRIM(objRef)) {
                bigFromInt(-1);
                slot.u.objRef = bip.res;
            }
            else {
                bigFromInt(GET_SIZE(objRef));
                slot.u.objRef = bip.res;
            }
            push(slot);
            PC++;
            break;
        }
        case PUSHN:
        {
            StackSlot slot;
            slot.isObjRef = false;
            slot.u.objRef = NULL;
            push(slot);
            PC++;
            break;
        }
        case REFEQ:
        {
            StackSlot slot;
            ObjRef objRef;
            ObjRef objRef2;
            objRef = popObjRef();
            objRef2 = popObjRef();

            if(objRef == objRef2) {
                bigFromInt(1);
                slot.isObjRef = true;
            }
            else {
                bigFromInt(0);
                slot.isObjRef = false;
            }
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        case REFNE:
        {
            StackSlot slot;
            ObjRef objRef;
            ObjRef objRef2;
            objRef = popObjRef();
            objRef2 = popObjRef();

            if(objRef != objRef2) {
                bigFromInt(1);
                slot.isObjRef = true;
            }
            else {
                bigFromInt(0);
                slot.isObjRef = false;
            }
            slot.u.objRef = bip.res;
            push(slot);
            PC++;
            break;
        }
        default:
        {
            printf("Not defined!\n");
            PC++;
        }
    }
}

void push(StackSlot slot){
    if(SP > stackSize * 1024){
        printf("Stack is full, push cannot be performed!\n");
        exit(EXIT_FAILURE);
    }
        else if(SP < 0){
        printf("Stack pointer is below zero, push cannot be performed!\n");
        exit(EXIT_FAILURE);
    }
        else {
        stack[SP++] = slot;
    }
}

ObjRef popObjRef (){
    StackSlot slot;
    if(SP > 0){
        slot = stack[--SP];
    } else {
        printf("Stack is empty, nothing to pop!\n");
    }
    return slot.u.objRef;
}

int popNumber(){
    StackSlot slot;
    if(SP > 0){
        slot = stack[--SP];
    } else {
        printf("Stack is empty, nothing to pop!\n");
    }
    return slot.u.number;
}

int immediate_value(unsigned int binary) {
    return (SIGN_EXTEND(binary & 0x00FFFFFF));
}

void fatalError(char* msg) {
    printf("Fatal Error: %s", msg);
    exit(102);
}

ObjRef newPrimObject(int dataSize) {
    ObjRef objRef = malloc(sizeof(unsigned int) + dataSize * sizeof(unsigned char));
    objRef->size = dataSize;
    return objRef;
}

ObjRef newCompoundObject(int objRefSize) {
    ObjRef objRef = malloc(sizeof(unsigned int) + objRefSize * sizeof(ObjRef));
    int counter = 0;
    objRef->size = objRefSize | MSB;

    do{
        *((ObjRef *)objRef->data + counter++) = NULL;
    } while(counter < GET_SIZE(objRef));

    return objRef;
}
