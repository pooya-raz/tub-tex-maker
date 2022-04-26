//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_AUTHOR_H
#define TUB_PDF_MAKER_AUTHOR_H
#include <string>

class Author
{
private:
    std::string m_name_transliterated {};
    int m_death_hijri {};
    int m_death_gregorian {};
    std::string m_death_hijri_text {};
    std::string m_death_gregorian_text {};
public:
    Author();

    Author(std::string name_transliterated,
           int death_hijri,
           int death_gregorian,
           std::string death_hijri_text,
           std::string death_gregorian_text);

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] int getMDeathHijri() const;

    [[nodiscard]] int getMDeathGregorian() const;

    [[nodiscard]] const std::string &getMDeathHijriText() const;

    [[nodiscard]] const std::string &getMDeathGregorianText() const;
};


#endif //TUB_PDF_MAKER_AUTHOR_H
