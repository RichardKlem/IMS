//
// Created by Richard Klem on 24.04.20.
//
#include <cstring>
#include <iostream>
#include "my_string.h"

/**
 * Převede řetězec na číslo
 * @param str vstupní řetězec
 * @return int výstupní struktura obsahující dvojici (status, číslo)
 */
str2int_struct_t str2int (char * str){
    str2int_struct_t result {S2I_FAIL, 0};
    unsigned int num;

    if (str == nullptr)
        return result;

    // ošetření, že se nevyskytuje žádný NEnumerický znak
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