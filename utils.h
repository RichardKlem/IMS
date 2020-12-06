/**
 * @author1: Martin Haderka
 * @author2: Richard Klem
 * @email1: xhader00@stud.fit.vutbr.cz
 * @email2: xklemr00@stud.fit.vutbr.cz
 * @login1: xhader00
 * @login2: xklemr00
 * @date: 6.11.2020
 */

#ifndef IMS_UTILS_H
#define IMS_UTILS_H
#include <chrono>
#include <random>

/**
 * @brief Enum struktura direction představuje směry, kam se může člověk vydat v dalším kroku.
 */
enum direction {
    FORWARD,
    RIGHT,
    BACK,
    LEFT,
    STAY
};

/**
 * @brief Funkce vrací pseudo-náhodné číslo ze zadaného intervalu podle algoritmu
 * @param a leva mez intervalu
 * @param b prava mez intervalu
 * @return pseudo-nahodne cislo ze zadaneho intervalu
 */
static unsigned long randIMS(unsigned long a, unsigned long b) {
    typedef std::mt19937 rng_type;
    std::uniform_int_distribution<rng_type::result_type> udist(a, b);
    rng_type rng(chrono::steady_clock::now().time_since_epoch().count());
    rng_type::result_type random_number = udist(rng);
    return random_number;
}

#endif //IMS_UTILS_H
