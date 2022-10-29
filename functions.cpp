#include "functions.hpp"
#include "colors.hpp"


/*!
\file
\brief Исполняемый файл с функциями, необходимыми при сортировке
*/


int list_ctor(LIST* sp){
    assert(sp != NULL);
    sp->capacity = 8;

    sp->data = (Elem_t*) calloc(sp->capacity, sizeof(Elem_t));
    sp->next = (int*) calloc(sp->capacity, sizeof(Elem_t));
    sp->prev = (int*) calloc(sp->capacity, sizeof(Elem_t));
    list_fullfill_poison(sp);
    next_and_prev_index_free(sp);

    sp->data[0] = -1; // зависит от типа Elem_t
    sp->next[0] = 0;
    sp->prev[0] = 0;

    sp->size = 0;
    sp->free = 1;
    
    return NORMAL_RUNNING;
}

int list_fullfill_poison(LIST* sp){
    assert(sp != NULL);
    for (int i = 0; i < (int) sp->capacity; i++){
        sp->data[i] = POISON;
    }
    

    return NORMAL_RUNNING;
}

int next_and_prev_index_free(LIST* sp){
    for (int i = 1; i < (int) sp->capacity; i++){
        sp->prev[i] = i - 1;
        sp->next[i] = i + 1;
    }

    return NORMAL_RUNNING;
}

int list_append(LIST* sp){
    assert(sp != NULL);
    
    return NORMAL_RUNNING;
}


int list_dump(LIST* sp){
    printf("LISTDUMP\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%d ", i);
    }
    printf("|\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("__");
    }
    printf("|\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%c ", sp->data[i]);
    }
    printf("|\n");
    
    return NORMAL_RUNNING;
}