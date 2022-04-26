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

std::string Author::getDeathDates() const {
    std::string hijri = "NO DATA";
    std::string gregorian = "NO DATA";

    if(m_death_hijri != 0){
        hijri = std::to_string(m_death_hijri);
    }
    if(m_death_hijri_text != "NO DATA")
    {
        hijri = m_death_hijri_text;
    }

    if(m_death_gregorian != 0)
    {
        gregorian = std::to_string(m_death_gregorian);
    }
    if(m_death_gregorian_text != "NO DATA")
    {
        gregorian = m_death_gregorian_text;
    }

    return fmt::format("(d. {hijri}/{gregorian})",
                       fmt::arg("hijri",hijri),
                       fmt::arg("gregorian",gregorian)
    );




}

