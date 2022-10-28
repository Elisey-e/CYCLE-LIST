#include "functions.hpp"


/*!
\file
\brief Главный файл проекта с функцией main
\authors Zhdanov_EA
*/



/*!
	\brief Главная функция проекта.

    <main> производит считывание текста из файла, сортирует его различными способами и методами и записывает результат в папку output проекта
*/

int main ()
{
    long long int errors = 0;
    Elem_t popping_elem = 0;
    STACK stack_main = {};
    stack_ctor(&stack_main);
    for (int i = 0; i <= 30; i++){
        stack_push(&stack_main, i);
    }
    
    stack_logdump(&stack_main, SAVE_VARIBLE_NAME(stack_main), "ok");

    return 0;
}
