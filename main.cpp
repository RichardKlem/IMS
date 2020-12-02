#include <iostream>
#include <getopt.h>
#include "CellularAutomaton.h"
#include "my_string.h"
#include "main.h"

/**
 * @brief Funkce zpracuje argumenty a nastaví podle nich proměnné.
 * @param argc počet argumentů
 * @param argv ukazatel na pole argumentů
 * @param initInfectionRate ukazatel na proměnnou
 */
void argParse(int argc, char **argv, unsigned int * initInfectionRate) {
    int c, option_index;
    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
    {
        str2int_struct_t tmp = str2int(optarg);
        str2int_struct_t *p_tmp = &tmp;
        switch (c)
        {
            case 'h':
                fprintf(outFile,"%s", help_text);
                exit (OK);
            case 'n':
                if (p_tmp->status) {
                    if (p_tmp->num < 0) {
                        cout << p_tmp->num << endl;
                        fprintf(errFile, "\n%s   Nesprávná hodnota čísla. Hodnota musí být ostře větší než 0.%s\n\n", RED, RST);
                        exit(BAD_ARG_VALUE);
                    }
                    *initInfectionRate = p_tmp->num;
                }
                else {
                    cout << p_tmp->num << endl;
                    fprintf(errFile, "\n%s   Nesprávná hodnota čísla. Hodnota musí být ostře větší než 0.%s\n\n", RED, RST);
                    exit(BAD_ARG_VALUE);
                }
                break;
            default:
                exit(UNKNOWN_PARAMETER);
        }
    }
}

int main(int argc, char *argv[]) {
    unsigned int initInfectionRate = 0;

    if (argc > 1)
        argParse(argc, argv, &initInfectionRate);

    CellularAutomaton CA(1420, 3550);
    CA.getMatrix()[10][10].setState(1);
    cout << CA.getMatrix().size / initInfectionRate << endl;

    CA.dumpMatrixToFile();

    std::cout << "Hello, World! " << std::endl << CA.getMatrix()[10][10].getState() << std::endl << CA.getMatrix()[10][11].getState();
    return 0;
}
