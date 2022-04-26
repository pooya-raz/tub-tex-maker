//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_H
#define TUB_PDF_MAKER_ENTRY_H

#include <string>
#include "author.h"

class Entry
{
private:
    std::string m_id {};
    std::string m_title_transliterated {};
    std::string m_title_arabic {};
    Author m_author {};

public:
    Entry();

    Entry(std::string id, std::string title_transliterated, std::string title_arabic, Author author);

    const std::string &getId() const;

    const std::string &getMTitleTransliterated() const;

    const std::string &getMTitleArabic() const;

    const Author &getMAuthor() const;

    std::string to_string();

};

#endif //TUB_PDF_MAKER_ENTRY_H
