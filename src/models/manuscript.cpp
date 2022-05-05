//
// Created by pooya on 5/5/22.
//

#include "manuscript.h"

Manuscript::Manuscript() = default;

Manuscript::Manuscript(
        std::string location,
        int year_hijri,
        int year_gregorian,
        std::string year_hijri_text,
        std::string year_gregorian_text,
        std::string city,
        std::string manuscript_number,
        std::string manuscript_of_title) :
        location(std::move(location)),
        year_hijri(year_hijri),
        year_gregorian(year_gregorian),
        year_hijri_text(std::move(year_hijri_text)),
        year_gregorian_text(std::move(year_gregorian_text)),
        city(std::move(city)),
        manuscript_number(std::move(manuscript_number)),
        manuscript_of_title(std::move(manuscript_of_title)) {}

const std::string &Manuscript::getManuscriptOfTitle() const {
    return manuscript_of_title;
}
