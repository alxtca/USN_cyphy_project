#include "language.h"

std::string choose_language()
{
    while (true) {
        std::cout << "Choose language (EN) / Velg Språk (NO)" << std::endl
            << "1: English (EN)" << std::endl
            << "2: Norsk (NO)" << std::endl;
        std::string language_choice;
        std::cin >> language_choice;
        std::string chosen_language;

        if (language_choice == "1") {
            chosen_language = "EN";
            return chosen_language;
        }
        else if (language_choice == "2") {
            chosen_language = "NO";
            return chosen_language;
        }
        else std::cout << "Non valid input / Ikke gyldig innskrevet verdi" << std::endl;
    }
}
