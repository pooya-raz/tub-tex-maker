//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_AUTHOR_H
#define TUB_PDF_MAKER_AUTHOR_H
#include <string>
#include <fmt/core.h>

class Author
{
private:
    std::string name_transliterated {};
    int death_hijri {};
    int death_gregorian {};
    int death_shamsi {};
    std::string death_hijri_text {};
    std::string death_gregorian_text {};
    std::string death_shamsi_text {};
public:
    Author();

    Author(std::string name_transliterated,
           int death_hijri,
           int death_gregorian,
	   int death_shamsi,
           std::string death_hijri_text,
           std::string death_gregorian_text,
	   std::string death_shamsi_text);

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] int getMDeathHijri() const;

    [[nodiscard]] int getMDeathGregorian() const;

    [[nodiscard]] const std::string &getMDeathHijriText() const;

    [[nodiscard]] const std::string &getMDeathGregorianText() const;

    std::string getDeathDates() const;

    void setDeathHijri(int deathHijri);
};


#endif //TUB_PDF_MAKER_AUTHOR_H
