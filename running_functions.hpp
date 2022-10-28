#ifndef RUNNING_H
#define RUNNING_H


#include "functions.hpp"


int stack_increase(STACK* st);

int stack_decrease(STACK* st);

int stack_fill_poison(STACK* st, int realloced);

#endif