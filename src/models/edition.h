//
// Created by pooya on 5/7/22.
//

#ifndef TUB_PDF_MAKER_EDITION_H
#define TUB_PDF_MAKER_EDITION_H
#include <string>
#include <fmt/core.h>

class Edition {

private:
    std::string title;
    std::string editor;
    std::string edition_type;
    std::string publisher;
    std::string city;
    int year_hijri{};
    int year_gregorian{};
    std::string year_hijri_text{};
    std::string year_gregorian_text{};
public:
    Edition(std::string title, std::string editor, std::string editionType,
            std::string publisher, std::string city, int yearHijri, int yearGregorian,
            std::string yearHijriText, std::string yearGregorianText);

    std::string to_latex();
};


#endif //TUB_PDF_MAKER_EDITION_H
