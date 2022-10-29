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
};

enum SPECIAL_TYPES
{
    POISON = '#', // зависит от типа Elem_t
};

/*!
    \file
    \brief Заголовочный файл с прототипами функций.
*/

typedef char Elem_t;

typedef struct list{
    Elem_t* data;
    int* next;
    int* prev;
    size_t size;
    size_t capacity;
    int free;
}   LIST;

int list_ctor(LIST* sp);

int list_fullfill_poison(LIST* sp);

int next_and_prev_index_free(LIST* sp);

int list_append(LIST* sp);

int list_dump(LIST* sp);

#endif