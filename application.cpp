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

    return 0;
}
