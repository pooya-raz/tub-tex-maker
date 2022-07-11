//
// Created by pooya on 5/5/22.
//

#include "manuscript.h"

Manuscript::Manuscript() = default;

Manuscript::Manuscript(
        std::string location,
        int year_hijri,
        int year_gregorian,
        int year_shamsi,
        std::string year_hijri_text,
        std::string year_gregorian_text,
        std::string year_shamsi_text,
        std::string city,
        std::string manuscript_number,
        std::string manuscript_of_title) :
        location(std::move(location)),
        year_hijri(year_hijri),
        year_gregorian(year_gregorian),
        year_shamsi(year_shamsi),
        year_hijri_text(std::move(year_hijri_text)),
        year_gregorian_text(std::move(year_gregorian_text)),
        year_shamsi_text(std::move(year_shamsi_text)),
        city(std::move(city)),
        manuscript_number(std::move(manuscript_number)),
        manuscript_of_title(std::move(manuscript_of_title)) {}

const std::string &Manuscript::getManuscriptOfTitle() const {
    return manuscript_of_title;
}


std::string Manuscript::getDates() const {
    std::string hijri = "NO DATA";
    std::string gregorian = "NO DATA";
    std::string shamsi = "NO DATA";

    if (year_hijri != 9999) {
        hijri = std::to_string(year_hijri);

    }
    if (year_hijri_text != "NO DATA") {
        hijri = year_hijri_text;
    }

    if (year_gregorian != 0) {
        gregorian = std::to_string(year_gregorian);
    }
    if (year_gregorian_text != "NO DATA") {
        gregorian = year_gregorian_text;
    }
    if (year_shamsi != 0) {
        shamsi = std::to_string(year_shamsi);
    }
    if (year_shamsi_text != "NO DATA") {
        shamsi = year_shamsi_text;
    }

    if (shamsi != "NO DATA" && year_gregorian != 0) {
        return fmt::format("dated {shamsi}Sh/{gregorian}",
                           fmt::arg("shamsi", shamsi),
                           fmt::arg("gregorian", gregorian));
    }
    if (shamsi != "NO DATA" && year_gregorian == 0) {
        return fmt::format("dated {shamsi}Sh",
                           fmt::arg("shamsi", shamsi));
    }
    if (hijri == "NO DATA" && shamsi == "NO DATA" && year_gregorian != 0) {
        return fmt::format("dated {gregorian}",
                           fmt::arg("gregorian", gregorian));
    }

    if (hijri == "NO DATA" && gregorian == "NO DATA" && shamsi == "NO DATA") {
        return "undated manuscript";
    }

    return fmt::format("dated {hijri}/{gregorian}",
                       fmt::arg("hijri", hijri),
                       fmt::arg("gregorian", gregorian)
    );
}

std::string Manuscript::to_latex() const {
    return fmt::format("\\item {location}, {city} (\\#{manuscript_number}), {dates}\n",
                       fmt::arg("location", location),
                       fmt::arg("city", city),
                       fmt::arg("manuscript_number", manuscript_number),
                       fmt::arg("dates", getDates()));
}

const std::string &Manuscript::getLocation() const {
    return location;
}

int Manuscript::getYearHijri() const {
    return year_hijri;
}

int Manuscript::getYearGregorian() const {
    return year_gregorian;
}

const std::string &Manuscript::getYearHijriText() const {
    return year_hijri_text;
}

const std::string &Manuscript::getYearGregorianText() const {
    return year_gregorian_text;
}

const std::string &Manuscript::getCity() const {
    return city;
}

const std::string &Manuscript::getManuscriptNumber() const {
    return manuscript_number;
}
