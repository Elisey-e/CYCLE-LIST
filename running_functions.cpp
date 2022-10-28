#include "running_functions.hpp"


int stack_increase(STACK* st){
    assert(st != NULL);

    if (st->size < st->capacity){
        return ERR_NOT_INCREASED;
    }
    st->data = (Elem_t*) realloc(st->data, st->capacity * 2 * (sizeof(Elem_t)));
    st->capacity *= 2;
    stack_fill_poison(st, 1);
    return NORMAL_RUNNING;
}


int stack_decrease(STACK* st){
    assert(st != NULL);

    if (st->size * 4 > st->capacity - 1){
        return ERR_NOT_DECREASED;
        printf("ts legf\n");
    }
    st->data = (Elem_t*) realloc(st->data, st->capacity / 2 * (sizeof(Elem_t)));
    st->capacity /= 2;
    return NORMAL_RUNNING;
}

int stack_fill_poison(STACK* st, int realloced){
    assert(st != NULL);
    for (size_t i = st->size; i < st->capacity; i++){
        if (st->data[i] != 0 && realloced == 0){
            return ERR_ELEM_PLACE;
        }
        st->data[i] = POISON;

    }
    return NORMAL_RUNNING;

}