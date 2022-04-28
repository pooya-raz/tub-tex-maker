//
// Created by pooya on 4/26/22.
//

#include "entry.h"

Entry::Entry() = default;

Entry::Entry(std::string id,
             std::string title_transliterated,
             std::string title_arabic,
             std::string description,
             Category category,
             Author author) {
    m_id = std::move(id);
    m_title_transliterated = std::move(title_transliterated);
    m_title_arabic = std::move(title_arabic);
    m_author = std::move(author);
    m_description = std::move(description);
    m_category = category;
}

std::string Entry::to_string() {

    return fmt::format("\\item \\\\textbf{{{transliterated_title}}}\n"
                                    "        \\\\newline\n"
                                    "        \\\\textarabic{{{arabic_title}}}\n"
                                    "        \\\\newline\n"
                                    "        {author}\n"
                                    "        \\\\newline\n"
                                    "        {death_dates}\n"
                                    "        \\\\newline\n"
                                    "        \\\\newline\n"
                                    "        \\\\textbf{{Description}}\n"
                                    "        \\\\newline\t\n"
                                    "        {description}\n"
                                    "        \\\\newline\n"
                                    "        \\\\newline",
                                    fmt::arg("transliterated_title",m_title_transliterated),
                                    fmt::arg("arabic_title",m_title_arabic),
                                    fmt::arg("author",m_author.getName()),
                                    fmt::arg("death_dates",m_author.getDeathDates()),
                                    fmt::arg("description",m_description)
                                    );
}

const std::string &Entry::getId() const {
    return m_id;
}

const std::string &Entry::getTitleTransliterated() const {
    return m_title_transliterated;
}

const std::string &Entry::getTitleArabic() const {
    return m_title_arabic;
}

const Author &Entry::getAuthor() const {
    return m_author;
}

const std::string &Entry::getDescription() const {
    return m_description;
}

const Category &Entry::getCategory() const {
    return m_category;
}