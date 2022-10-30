#include "functions.hpp"
#include "colors.hpp"


/*!
\file
\brief Исполняемый файл с функциями, необходимыми при сортировке
*/


int list_ctor(LIST* sp, size_t capacity){
    assert(sp != NULL);
    sp->capacity = capacity;
    sp->size = 1;
    sp->free = 1;

    sp->data = (Elem_t*) calloc(sp->capacity, sizeof(Elem_t));
    sp->next = (INDEX*) calloc(sp->capacity, sizeof(INDEX));
    sp->prev = (INDEX*) calloc(sp->capacity, sizeof(INDEX));
    list_fullfill_poison(sp);
    next_and_prev_index_free(sp);

    sp->data[0] = -1; // зависит от типа Elem_t
    sp->next[0] = {0, false};
    sp->prev[0] = {0, false};
    
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
    for (int i = sp->free; i < (int) sp->capacity; i++){
        sp->prev[i] = {i - 1, true};
        sp->next[i] = {i + 1, true};
    }
    sp->next[(int) sp->capacity - 1] = {0, true};

    return NORMAL_RUNNING;
}

int list_append_before(LIST* sp, Elem_t el, int anchor, int* new_index){
    assert(sp != NULL);
    assert(sp->size <= sp->capacity && "stack_overfilled");

    if (sp->size + 1 == sp->capacity){
        list_increase(sp);
    }



    *new_index = sp->free;
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


int list_append_after(LIST* sp, Elem_t el, int anchor, int* new_index){
    assert(sp != NULL);
    assert(sp->size <= sp->capacity && "stack_overfilled");

    if (sp->size + 1 == sp->capacity){
        list_increase(sp);
    }

    *new_index = sp->free;
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
        printf("%2d ", i);
    }
    printf("|\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("___");
    }
    printf("|\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%2c ", sp->data[i]);
    }
    printf("|\n\nNEXT\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%2d ", sp->next[i].near_el);
    }
    printf("|\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        if (sp->next[i].free == true){
            printf(" - ");
        }
        else{
            printf(" + ");
        }
    }
    printf("|\n\nPREV\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        printf("%2d ", sp->prev[i].near_el);
    }
    printf("|\n|");
    for (int i = 0; i < (int) sp->capacity; i++){
        if (sp->prev[i].free == true){
            printf(" - ");
        }
        else{
            printf(" + ");
        }
    }
    printf("|\n");

    printf("free=%d; \n", sp->free);
    
    return NORMAL_RUNNING;
}


int list_dtor(LIST* sp){
    free(sp->data);
    free(sp->next);
    free(sp->prev);

    return NORMAL_RUNNING;
}


int list_pop(LIST* sp, int anchor){
    assert(sp != NULL);

    if (sp->size * 4 <= sp->capacity){
        list_decrease(sp);
    }

    sp->next[sp->prev[anchor].near_el].near_el = sp->next[anchor].near_el;
    sp->prev[sp->next[anchor].near_el].near_el = sp->prev[anchor].near_el;

    assert(sp->prev[sp->next[anchor].near_el].free == false);
    assert(sp->next[sp->prev[anchor].near_el].free == false);
    
    sp->next[anchor] = {sp->free, true};
    sp->prev[sp->free] = {anchor, true};
    sp->prev[anchor].free = true;

    sp->data[anchor] = POISON;
    sp->free = anchor;
    sp->size--;

    return NORMAL_RUNNING;
}

int list_find_index(LIST* sp, Elem_t el, int* index){
    assert(sp != NULL);
    int i = 0;

    while (sp->data[i] != el){
        i++;
        if (i == (int) sp->capacity){
            *index = DONT_EXIST;
            return NORMAL_RUNNING;
        }
    }

    *index = i;

    return NORMAL_RUNNING;
}


int list_increase(LIST* sp){
    assert(sp != NULL);

    if (sp->size + 1 < sp->capacity){
        return ERR_NOT_INCREASED;
    }

    LIST new_sp;
    list_ctor(&new_sp, sp->capacity * 2);

    for (int i = 0; i < (int) sp->capacity; i++){
        new_sp.data[i] = sp->data[i];
        new_sp.next[i] = sp->next[i];
        new_sp.prev[i] = sp->prev[i];
    }

    new_sp.free = sp->free;
    new_sp.size = sp->size;

    next_and_prev_index_free(&new_sp);

    list_dtor(sp);

    *sp = new_sp;

    return NORMAL_RUNNING;
}

int list_decrease(LIST* sp){
    assert(sp != NULL);

    if ((sp->size + 1) * 4 > sp->capacity && sp->capacity / 2 < 4){
        return ERR_NOT_DECREASED;
    }

    LIST new_sp;
    list_ctor(&new_sp, sp->capacity / 2);

    for (int i = 0; i < (int) sp->capacity / 2; i++){
        new_sp.data[i] = sp->data[i];
        new_sp.next[i] = sp->next[i];
        new_sp.prev[i] = sp->prev[i];
    }

    new_sp.free = sp->free;
    new_sp.size = sp->size;

    new_sp.next[sp->capacity - 1] = {0, true};

    list_dtor(sp);

    *sp = new_sp;

    return NORMAL_RUNNING;

}

int list_append_head(LIST* sp, Elem_t el, int* new_index){
    return NORMAL_RUNNING;
}

int list_append_tail(LIST* sp, Elem_t el, int* new_index){
    return NORMAL_RUNNING;
}

int list_gen_head_index(LIST* sp){
    return NORMAL_RUNNING;
}

int list_gen_tail_index(LIST* sp){
    return NORMAL_RUNNING;
}

int list_find_name_by_index(LIST* sp, int index){
    return NORMAL_RUNNING;
}