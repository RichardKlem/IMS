/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */
#ifndef IMS_MAIN_H
#define IMS_MAIN_H

#include "my_string.h"

#define RED "\033[0;91m"
#define RST "\033[0m"

enum EXIT_CODES {
    OK = 0,
    FAILURE = 1,
    BAD_ARG_VALUE = 11,
    UNKNOWN_PARAMETER = 12};

const char * helpText = "\n***Nápověda k CA simuláru***\n"
                         "Překlad:\n"
                         "  - make\n\n"
                         "Spuštění:\n"
                         "  ./covid [-i <nazev_rozhrani>| -r <nazev_souboru.pcapng>] [volitelné argumenty]\n"
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
#include <sstream>

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
                {"forward-p",    optional_argument,  nullptr, 'f'},
                {"right-p",    optional_argument,  nullptr, 'r'},
                {"back-p",    optional_argument,  nullptr, 'b'},
                {"left-p",    optional_argument,  nullptr, 'l'},
                {"stay-p",    optional_argument,  nullptr, 'z'},
                {"dump_dir",    optional_argument,  nullptr, 'd'},
                {nullptr, 0, nullptr, 0}
        };
// Definice krátkých přepínačů.
char *short_options = (char*)"hn:i:m:x:y:t:s:f:r:b:l:z:d:";

/**
 * @brief Funkce zpracuje argumenty a nastaví podle nich proměnné.
 * @param argc počet argumentů
 * @param argv ukazatel na pole argumentů
 * @param initInfectionRate ukazatel na proměnnou
 */
void argParse(int argc, char **argv, unsigned int * number, unsigned int * initInfectionRate,
              unsigned int * initImmuneRate, unsigned int * x, unsigned int * y, unsigned int * time,
              unsigned int * step, unsigned int * forwardP, unsigned int * rightP, unsigned int * leftP,
              unsigned int * backP, unsigned int * stayP, string * dumpDir) {
    int c, option_index;
    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
    {
        str2int_struct_t tmp = str2int(optarg);
        str2int_struct_t *p_tmp = &tmp;
        stringstream tmpString;
        switch (c)
        {
            case 'h':
                cout << helpText;
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
            case 'f':
                if (p_tmp->status) {
                    *forwardP = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota pravdědopodobnosti pohybu dopředu. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'r':
                if (p_tmp->status) {
                    *rightP = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota pravdědopodobnosti pohybu doprava. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'b':
                if (p_tmp->status) {
                    *backP = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota pravdědopodobnosti pohybu dozadu. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'l':
                if (p_tmp->status) {
                    *leftP = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota pravdědopodobnosti pohybu doleva. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'z':
                if (p_tmp->status) {
                    *stayP = p_tmp->num;
                }
                else {
                    cerr << endl << RED <<"   Nesprávná hodnota pravdědopodobnosti setrvání na místě. Hodnota musí být ostře větší než 0." << RST<< endl << endl;
                    exit(BAD_ARG_VALUE);
                }
                break;
            case 'd':
                tmpString << optarg;
                tmpString >> *dumpDir;
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
