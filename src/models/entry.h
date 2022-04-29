//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_H
#define TUB_PDF_MAKER_ENTRY_H

#include <string>
#include <utility>
#include <fmt/core.h>
#include <vector>
#include "author.h"
#include "../models/title_type.h"

class Entry
{
private:
    std::string m_id {};
    std::string m_title_transliterated {};
    std::string m_title_arabic {};
    std::string m_description {};
    Category m_category {};
    std::vector<CorrectionsRequired> m_corrections_required {};
    Author m_author {};

public:
    Entry();

    Entry(std::string id, std::string title_transliterated, std::string title_arabic, std::string description, Category category, std::vector<CorrectionsRequired> correctionsRequired, Author author);

    [[nodiscard]] const std::string &getId() const;

    [[nodiscard]] const std::string &getTitleTransliterated() const;

    [[nodiscard]] const std::string &getTitleArabic() const;

    [[nodiscard]] const std::string &getDescription() const;

    [[nodiscard]] const Author &getAuthor() const;

    [[nodiscard]] const Category &getCategory() const;

    [[nodiscard]] const std::vector<CorrectionsRequired> &getCorrectionsRequired() const;

    std::string to_latex();

};

#endif //TUB_PDF_MAKER_ENTRY_H
