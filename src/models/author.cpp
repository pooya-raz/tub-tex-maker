//
// Created by pooya on 4/26/22.
//

#include "author.h"
Author::Author() = default;

const std::string &Author::getName() const {
    return m_name_transliterated;
}

Author::Author(std::string name_transliterated,
               int death_hijri,
               int death_gregorian,
               std::string death_hijri_text,
               std::string death_gregorian_text) {
    m_name_transliterated = std::move(name_transliterated);
    m_death_hijri = death_hijri;
    m_death_gregorian = death_gregorian;
    m_death_hijri_text = std::move(death_hijri_text);
    m_death_gregorian_text= std::move(death_gregorian_text);
}

int Author::getMDeathHijri() const {
    return m_death_hijri;
}

int Author::getMDeathGregorian() const {
    return m_death_gregorian;
}

const std::string &Author::getMDeathHijriText() const {
    return m_death_hijri_text;
}

const std::string &Author::getMDeathGregorianText() const {
    return m_death_gregorian_text;
}

