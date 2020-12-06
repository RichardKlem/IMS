/**
 * @author1: Richard Klem
 * @email1: xklemr00@stud.fit.vutbr.cz
 * @login1: xklemr00
 * @date: 6.11.2020
 */
#include <cstring>
#include <iostream>
#include "my_string.h"

/**
 * Převede řetězec na číslo.
 * @param str Vstupní řetězec.
 * @return int Výstupní struktura obsahující dvojici (status, převedené číslo).
 */
str2int_struct_t str2int (char * str){
    str2int_struct_t result {S2I_FAIL, 0};
    unsigned int num;

    if (str == nullptr)
        return result;

    // Ošetření, že se nevyskytuje žádný NEnumerický znak.
    for (unsigned int i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i]))
            return result;
    }
    long int tmp = strtol(str, nullptr, 10);
    if (tmp < 0)
        return result;

    num = (unsigned int) tmp;

    result = {S2I_OK, num};
    return result;
}