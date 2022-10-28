#include "functions.hpp"
#include "running_functions.hpp"


int stack_ctor(STACK* stack){
    stack->capacity = 8;
    stack->data = (Elem_t*) calloc(stack->capacity, sizeof(Elem_t));;
    stack->size = 0;
    stack_fill_poison(stack, 1);

    return 0;
}

int stack_dtor(STACK* stack){
    free(stack->data);
    stack->capacity = 0;
    stack->size = 0;

    return PROBLEMS_WERE_NOT_DETECTED;
}

int stack_dump(STACK* stack, const char* name, const char* status){
    if (stack == NULL){
        printf("STACK DOESN'T EXIST\n");
        return NORMAL_RUNNING;
    }

    printf("<STACKDUMP>\n");
    printf("stack \"%s\" (%s) [0x%0x]\n", name, status, (unsigned int) (size_t) stack);
    printf("{\n");
    printf("\tdata[%d] = [0x%0x]\n", (int) stack->capacity, (unsigned int) (size_t) stack->data);
    printf("\t{\n");
    for (size_t i = 0; i < stack->capacity; i++){
        char stared = ' ';
        if (i < stack->size){
            stared = '*';
        }
        printf("\t%6c\t[%d] = %d", stared, (int) i, stack->data[i]); // Работает только для целых чисел
        if (stared == ' '){
            printf("\tFREE");
        }
        printf("\n");
    }
    printf("\t};\n");
    printf("\tsize = %d;\n\tcapacity = %d;\n", (int) stack->size, (int) stack->capacity);
    printf("};\n");

    return NORMAL_RUNNING;
}


int stack_logdump(STACK* stack, const char* name, const char* status){
    FILE* logfile = fopen("file.log", "w");
    if (stack == NULL){
        fprintf(logfile, "STACK DOESN'T EXIST\n");
        return NORMAL_RUNNING;
    }
    
    fprintf(logfile, "<STACKDUMP>\n");
    fprintf(logfile, "stack \"%s\" (%s) [0x%0x]\n", name, status, (unsigned int) (size_t) stack);
    fprintf(logfile, "{\n");
    fprintf(logfile, "\tdata[%d] = [0x%0x]\n", (int) stack->capacity, (unsigned int) (size_t) stack->data);
    fprintf(logfile, "\t{\n");
    for (size_t i = 0; i < stack->capacity; i++){
        char stared = ' ';
        if (i < stack->size){
            stared = '*';
        }
        fprintf(logfile, "\t%6c\t[%d] = %d", stared, (int) i, stack->data[i]); // Работает только для целых чисел
        if (stared == ' '){
            fprintf(logfile, "\tFREE");
        }
        fprintf(logfile, "\n");
    }
    fprintf(logfile, "\t};\n");
    fprintf(logfile, "\tsize = %d;\n\tcapacity = %d;\n", (int) stack->size, (int) stack->capacity);
    fprintf(logfile, "};\n");

    return NORMAL_RUNNING;
}