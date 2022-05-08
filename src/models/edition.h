//
// Created by pooya on 5/7/22.
//

#ifndef TUB_PDF_MAKER_EDITION_H
#define TUB_PDF_MAKER_EDITION_H
#include <string>
#include <fmt/core.h>

class Edition {

private:
    std::string title_transliterated;
    std::string title_arabic;
    std::string editor;
    std::string edition_type;
    std::string publisher;
    std::string city;
    int year_hijri{};
    int year_gregorian{};
    std::string year_hijri_text{};
    std::string year_gregorian_text{};
    std::string description{};
    std::string published_edition_of_title{};
public:
    Edition(std::string title_transliterated,
            std::string title_arabic,
            std::string editor,
            std::string edition_type,
            std::string publisher,
            std::string city,
            int year_hijri,
            int year_gregorian,
            std::string year_hijri_text,
            std::string year_gregorian_text,
            std::string description,
            std::string published_edition_of_title);

    std::string to_latex();
    std::string getPublishedEditionOfTitle();
};


#endif //TUB_PDF_MAKER_EDITION_H