//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_H
#define TUB_PDF_MAKER_ENTRY_H

#include <string>
#include <utility>
#include <fmt/core.h>
#include "author.h"

class Entry
{
private:
    std::string m_id {};
    std::string m_title_transliterated {};
    std::string m_title_arabic {};
    std::string m_description {};
    Author m_author {};

public:
    Entry();

    Entry(std::string id, std::string title_transliterated, std::string title_arabic, std::string description, Author author);

    [[nodiscard]] const std::string &getId() const;

    [[nodiscard]] const std::string &getTitleTransliterated() const;

    [[nodiscard]] const std::string &getTitleArabic() const;

    [[nodiscard]] const std::string &getDescription() const;

    [[nodiscard]] const Author &getAuthor() const;

    std::string to_string();

};

#endif //TUB_PDF_MAKER_ENTRY_H
