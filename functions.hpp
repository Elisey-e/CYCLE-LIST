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
    ERR_NOT_POPPED = 10 + 3,
};

enum SPECIAL_TYPES
{
    POISON = '#', // зависит от типа Elem_t
    DONT_EXIST = -1,
};

/*!
    \file
    \brief Заголовочный файл с прототипами функций.
*/

typedef char Elem_t;

typedef struct Index_t{
    int near_el;
    bool free;
}   INDEX;

typedef struct list{
    Elem_t* data;
    INDEX* next;
    INDEX* prev;
    size_t size;
    size_t capacity;
    int free;
}   LIST;



int list_ctor(LIST* sp, size_t capacity);

int list_fullfill_poison(LIST* sp);

int next_and_prev_index_free(LIST* sp);

int list_append_before(LIST* sp, Elem_t el, int anchor, int* new_index);

int list_append_after(LIST* sp, Elem_t el, int anchor, int* new_index);

int list_dump(LIST* sp);

int list_dtor(LIST* sp);

int list_pop(LIST* sp, int anchor);

int list_find_index(LIST* sp, Elem_t el, int* index);

int list_increase(LIST* sp);

int list_decrease(LIST* sp);

#endif