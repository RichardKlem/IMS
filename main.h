//
// Created by Richa on 02-Dec-20.
//

#ifndef IMS_MAIN_H
#define IMS_MAIN_H

#define YELLOW "\033[0;93m"
#define RED "\033[0;91m"
#define RST "\033[0m"


FILE * outFile = stdout;
FILE * errFile = stdout;


enum EXIT_CODES {
    OK = 0,
    FAILURE = 1,
    BAD_ARG_VALUE = 11,
    UNKNOWN_PARAMETER = 12};

const char * help_text = "\n***Nápověda k CA simuláru***\n"
                         "Překlad:\n"
                         "  - maken\n\n"
                         "Spuštění:\n"
                         "  ./ebola [-i <nazev_rozhrani>| -r <nazev_souboru.pcapng>] [volitelné argumenty]\n"
                         "  Možné parametry POVINNÉ:\n"
                         "    -i <nazev_rozhrani> (Rozhraní, na kterém se bude poslouchat).\n"
                         "  nebo\n"
                         "    -r <nazev_souboru> (Soubor se zachycenými daty).\n"
                         "            Nebude-li ani jeden z těchto parametrů uveden, "
                         "            vypíše zkrácená nápověda se seznam aktivních rozhraní)\n"
                         "  Možné parametry VOLITELNÉ:\n"
                         "    -n | --num int: Počáteční počet nakažených.\n"

                         "  Krátké parametry je možné zadávat ve tvaru \"-n5\" anebo \"-n 5\".\n"
                         "  Dlouhé parametry je nutné zadávat ve tvaru \"--num=5\".\n\n";

#if defined(__APPLE__) || defined(__linux__)
#include <getopt.h>
// Definice dlouhých přepínačů.
static struct option long_options[] =
        {
                {"help",   no_argument,        nullptr, 'h'},
                {"number",    optional_argument,  nullptr, 'n'},
                {"infected",    optional_argument,  nullptr, 'i'},
                {"immune",    optional_argument,  nullptr, 'm'},
                {"row",    optional_argument,  nullptr, 'x'},
                {"col",    optional_argument,  nullptr, 'y'},
                {"time",    optional_argument,  nullptr, 't'},
                {"time-step",    optional_argument,  nullptr, 's'},
                {nullptr, 0, nullptr, 0}
        };
// Definice krátkých přepínačů.
char *short_options = (char*)"hn:i:m:x:y:t:s:";

/**
 * @brief Funkce zpracuje argumenty a nastaví podle nich proměnné.
 * @param argc počet argumentů
 * @param argv ukazatel na pole argumentů
 * @param initInfectionRate ukazatel na proměnnou
 */
void argParse(int argc, char **argv, unsigned int * number, unsigned int * initInfectionRate, unsigned int * initImmuneRate, unsigned int * x, unsigned int * y, unsigned int * time, unsigned int * step) {
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
                    *number = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota počtu lidí. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'i':
                if (p_tmp->status) {
                    *initInfectionRate = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota poměru prvotního nakažení. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'm':
                if (p_tmp->status) {
                    *initImmuneRate = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota poměru imunních jedinců. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'x':
                if (p_tmp->status) {
                    *x = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota počtu řádků. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'y':
                if (p_tmp->status) {
                    *y = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota počtu sloupců. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 't':
                if (p_tmp->status) {
                    *time = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota času. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 's':
                if (p_tmp->status) {
                    *step = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota krokování času. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            default:
                exit(UNKNOWN_PARAMETER);
        }
    }
}

#elif _WIN32
void argParse(int argc, char * argv[], unsigned int * initInfectionRate, unsigned int * x, unsigned int * y, unsigned int * t) {
    *initInfectionRate = 1000;
}
#endif

void argParse(int argc, char * argv[], unsigned int * initInfectionRate, unsigned int * x, unsigned int * y, unsigned int * t);
#endif //IMS_MAIN_H
