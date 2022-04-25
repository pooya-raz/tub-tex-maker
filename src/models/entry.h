//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_H
#define TUB_PDF_MAKER_ENTRY_H

#include <string>
struct Author
{
    std::string name_transliterated {};
    std::string name_arabic {};
};

struct Entry
{
    std::string title_transliteration {};
    std::string title_arabic {};
    std::string id {};
    Author author {};
};


#endif //TUB_PDF_MAKER_ENTRY_H
