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
// Definice dlouhých přepínačů.
static struct option long_options[] =
        {
                {"help",   no_argument,        nullptr, 'h'},
                {"num",    optional_argument,  nullptr, 'n'},
                {nullptr, 0, nullptr, 0}
        };
// Definice krátkých přepínačů.
char *short_options = (char*)"hn:";

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

void argParse(int argc, char * argv[], unsigned int * initInfectionRate);
#endif //IMS_MAIN_H
