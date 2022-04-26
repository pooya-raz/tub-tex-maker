//
// Created by pooya on 4/26/22.
//

#include "entry.h"

#include <utility>

Entry::Entry() = default;

Entry::Entry(std::string id, std::string title_transliterated, std::string title_arabic, Author author) {
    m_id = std::move(id);
    m_title_transliterated = std::move(title_transliterated);
    m_title_arabic = std::move(title_arabic);
    m_author = std::move(author);
}

std::string Entry::to_string() {
    return "Title: " + m_title_transliterated + "\n" +
           m_title_arabic +
           "Author " + m_author.getName();

}

const std::string &Entry::getId() const {
    return m_id;
}

const std::string &Entry::getMTitleTransliterated() const {
    return m_title_transliterated;
}

const std::string &Entry::getMTitleArabic() const {
    return m_title_arabic;
}

const Author &Entry::getMAuthor() const {
    return m_author;
}
