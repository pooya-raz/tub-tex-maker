//
// Created by pooya on 4/26/22.
//

#include "entry.h"

Entry::Entry() = default;

Entry::Entry(std::string id, std::string title_transliterated, std::string title_arabic, Author author) {
    m_id = std::move(id);
    m_title_transliterated = std::move(title_transliterated);
    m_title_arabic = std::move(title_arabic);
    m_author = std::move(author);
}

std::string Entry::to_string() {
    std::string latex = fmt::format("Title: {} ",m_title_transliterated);
    return latex;
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
