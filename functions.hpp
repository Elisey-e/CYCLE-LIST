#ifndef EVGENY_H
#define EVGENY_H


#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ASSERT(cond)\
    do {            \
	    if (!(cond)){\
		    printf("\tError in line %d\n\tof the file %s\n\tcondinion (%s) is false\n", __LINE__, __FILE__, #cond);\
            exit(1);}\
    } while(0)

#define SAVE_VARIBLE_NAME(varible) (const char*) #varible

enum TYPE_EL
{
    NORMAL_RUNNING = 10,
    ERR_NOT_INCREASED = 10 + 1,
    ERR_NOT_DECREASED = 10 + 2,
    ERR_WHILE_POPPING = 10 + 3,
    ERR_ELEM_PLACE = 10 + 4,
    PROBLEMS_WERE_NOT_DETECTED = 10 + 5,
};

enum SPECIAL_TYPES
{
    POISON = -666,
};

/*!
    \file
    \brief Заголовочный файл с прототипами функций.
*/

typedef int Elem_t;

typedef struct stack{
    Elem_t* data;
    size_t size;
    size_t capacity;
}   STACK;

int stack_ctor(STACK* stack);

int stack_push(STACK* st, Elem_t el);

int stack_pop(STACK* st, Elem_t* el);

int stack_dump(STACK* stack, const char* name, const char* status);

int stack_logdump(STACK* stack, const char* name, const char* status);

int stack_dtor(STACK* stack);

#endif