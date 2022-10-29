#include "functions.hpp"


/*!
\file
\brief Главный файл проекта с функцией main
\authors Zhdanov_EA
*/



int main ()
{
    LIST sp_main = {};
    list_ctor(&sp_main);

    list_dump(&sp_main);

    list_append_after(&sp_main, 'A', 0);
    list_append_after(&sp_main, 'B', 1);
    list_append_before(&sp_main, 'C', 2);
    list_append_before(&sp_main, 'D', 0);

    list_dump(&sp_main);
    list_dtor(&sp_main);

    return 0;
}
