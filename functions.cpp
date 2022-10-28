#include "functions.hpp"
#include "running_functions.hpp"


/*!
\file
\brief Исполняемый файл с функциями, необходимыми при сортировке
*/


int stack_push(STACK* st, Elem_t el){
    assert(st != NULL);

    if (st->size == st->capacity){
        int code = stack_increase(st);
        assert(code == NORMAL_RUNNING);
    }
    st->data[st->size] = el;
    st->size++;
    return NORMAL_RUNNING;
}


int stack_pop(STACK* st, Elem_t* el){
    assert(st != NULL);

    if (st->size == 0){
        return ERR_WHILE_POPPING;
    }
    *el = st->data[--st->size];
    st->data[st->size] = POISON;

    if (4 * st->size < st->capacity - 1){
        int code = stack_decrease(st);
        assert(code == NORMAL_RUNNING);
    }

    return *el;
}

