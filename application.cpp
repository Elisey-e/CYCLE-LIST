#include "functions.hpp"


/*!
\file
\brief Главный файл проекта с функцией main
\authors Zhdanov_EA
*/

//Написать функцию сбора ошибок, упаковки их в лог
//Сортировка в реальном порядке следования


int main ()
{
    LIST sp_main = {};
    int last_index = 0;
    list_ctor(&sp_main, 8);

    

    //list_append_after(&sp_main, 'A', 0, &last_index);
    //list_append_after(&sp_main, 'B', 1, &last_index);
    //list_append_before(&sp_main, 'C', 2, &last_index);
    //list_append_before(&sp_main, 'D', 0, &last_index);

    for (int i = 0; i < 7; i++){
        list_append_after(&sp_main, 'A' + (char) i, i, &last_index);
    }

    list_dump(&sp_main);
    printf("\n\n\n");

    //list_find_index(&sp_main, 'A', &last_index);
    //printf("A[%d]\n", last_index);

    //list_find_index(&sp_main, 'B', &last_index);
    //printf("B[%d]\n", last_index);
    

    //list_dump(&sp_main);
    list_dtor(&sp_main);

    return 0;
}
