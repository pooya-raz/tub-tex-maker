//
// Created by pooya on 5/5/22.
//

#ifndef TUB_PDF_MAKER_MANUSCRIPT_H
#define TUB_PDF_MAKER_MANUSCRIPT_H

#include <string>

class Manuscript {
    std::string location{};
    int year_hijri{};
    int year_gregorian{};
    std::string year_hijri_text{};
    std::string year_gregorian_text{};
    std::string city{};
    std::string manuscript_number{};
    std::string manuscript_of_title{};

public:
    Manuscript();

    Manuscript(
            std::string location,
            int year_hijri,
            int year_gregorian,
            std::string year_hijri_text,
            std::string year_gregorian_text,
            std::string city,
            std::string manuscript_number,
            std::string manuscript_of_title
    );
};


#endif //TUB_PDF_MAKER_MANUSCRIPT_H
