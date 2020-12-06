/**
 * @author1: Richard Klem
 * @email1: xklemr00@stud.fit.vutbr.cz
 * @login1: xklemr00
 * @date: 6.11.2020
 */
#ifndef PROJ2_MY_STRING_H
#define PROJ2_MY_STRING_H
enum STR2INT_STATUS_CODE {S2I_FAIL, S2I_OK};
struct str2int_struct_t{
    STR2INT_STATUS_CODE status;
    unsigned int num;
};
str2int_struct_t str2int(char * str);
#endif //PROJ2_MY_STRING_H
