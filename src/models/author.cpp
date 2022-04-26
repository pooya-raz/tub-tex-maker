//
// Created by pooya on 4/26/22.
//

#include "author.h"
Author::Author() = default;
Author::Author(std::string name_transliterated) {
    m_name_transliterated = std::move(name_transliterated);
}

const std::string &Author::getName() const {
    return m_name_transliterated;
}