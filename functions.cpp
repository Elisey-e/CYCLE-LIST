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
    sp->next = (INDEX*) calloc(sp->capacity, sizeof(INDEX));
    sp->prev = (INDEX*) calloc(sp->capacity, sizeof(INDEX));
    list_fullfill_poison(sp);
    next_and_prev_index_free(sp);

    sp->data[0] = -1; // зависит от типа Elem_t
    sp->next[0] = {0, false};
    sp->prev[0] = {0, false};

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
        sp->prev[i] = {i - 1, true};
        sp->next[i] = {i + 1, true};
    }
    sp->next[(int) sp->capacity - 1] = {0, true};

    return NORMAL_RUNNING;
}

int list_append_before(LIST* sp, Elem_t el, int anchor){
    assert(sp != NULL);

    int new_ind = sp->free;
    int free_new = sp->next[new_ind].near_el;
    sp->data[new_ind] = el;
    sp->next[new_ind] = {anchor, false};;
    sp->prev[new_ind] = {sp->prev[anchor].near_el, false};
    
    sp->next[sp->prev[new_ind].near_el] = {new_ind, false};
    sp->prev[sp->next[new_ind].near_el] = {new_ind, false};

    sp->size++;
    sp->free = free_new;



    return NORMAL_RUNNING;
}


int list_append_after(LIST* sp, Elem_t el, int anchor){
    assert(sp != NULL);

    int new_ind = sp->free;
    int free_new = sp->next[new_ind].near_el;
    sp->data[new_ind] = el;
    sp->next[new_ind] = {sp->next[anchor].near_el, false};;
    sp->prev[new_ind] = {anchor, false};
    
    sp->next[sp->prev[new_ind].near_el] = {new_ind, false};
    sp->prev[sp->next[new_ind].near_el] = {new_ind, false};

    sp->size++;
    sp->free = free_new;

    
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
    printf("|\n\nNEXT\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%d ", sp->next[i].near_el);
    }
    printf("|\n\nPREV\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%i ", sp->prev[i].near_el);
    }
    printf("|\n");

    printf("free=%d; \n", sp->free);
    
    return NORMAL_RUNNING;
}


int list_dtor(LIST* sp){
    free(sp->data);

    return NORMAL_RUNNING;
}


