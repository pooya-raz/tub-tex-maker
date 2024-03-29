//
// Created by pooya on 5/7/22.
//

#include "edition.h"

#include <utility>

Edition::Edition(std::string title_transliterated,
                 std::string title_arabic,
                 std::string editor,
                 std::string edition_type,
                 std::string publisher,
                 std::string city,
                 int year_hijri,
                 int year_gregorian,
                 int year_shamsi,
                 std::string year_hijri_text,
                 std::string year_gregorian_text,
                 std::string year_shamsi_text,
                 std::string description,
                 std::string published_edition_of_title,
                 double sort
) :
        title_transliterated(std::move(title_transliterated)),
        title_arabic(std::move(title_arabic)),
        editor(std::move(editor)),
        edition_type(std::move(edition_type)),
        publisher(std::move(publisher)),
        city(std::move(city)),
        year_hijri(year_hijri),
        year_gregorian(year_gregorian),
        year_shamsi(year_shamsi),
        year_hijri_text(std::move(year_hijri_text)),
        year_gregorian_text(std::move(year_gregorian_text)),
        year_shamsi_text(std::move(year_shamsi_text)),
        description(std::move(description)),
        published_edition_of_title(std::move(published_edition_of_title)),
        sort(sort) {}

std::string Edition::to_latex() {
    return fmt::format("\\item \\emph{{{title}}}{editor}{edition_type} ({city} {publisher}, {dates})\n",
                       fmt::arg("title", title_transliterated),
                       fmt::arg("editor", Edition::create_tex(editor, f_editor)),
                       fmt::arg("edition_type", create_tex(edition_type, f_edition_type)),
                       fmt::arg("publisher", Edition::create_tex(publisher, f_publisher)),
                       fmt::arg("city", Edition::create_tex(city, f_city)),
                       fmt::arg("dates", getDates())
    );
}

std::string Edition::create_tex(const std::string &value, Field field) {
    switch (field) {
        case f_editor:
            return (value == "NO DATA") ? "" : ", ed. " + value;
        case f_edition_type: 
            return (value == "Modern print" || value == "NO DATA") ? "" : ", " + value;
        case f_city:
            return (value == "NO DATA") ? "n.plac.," : value + ":";
        case f_publisher:
            return (value == "NO DATA") ? "n.pub." : value;
    }
}

std::string Edition::getDates() {
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
        return fmt::format("{shamsi}Sh/{gregorian}",
                           fmt::arg("shamsi", shamsi),
                           fmt::arg("gregorian", gregorian));
    }

    if (shamsi != "NO DATA" && year_gregorian == 0) {
        return fmt::format("{shamsi}Sh",
                           fmt::arg("shamsi", shamsi));
    }
    if (year_hijri == 9999 && year_gregorian != 0) {
        return gregorian;
    }

    return fmt::format("{hijri}/{gregorian}",
                       fmt::arg("hijri", hijri),
                       fmt::arg("gregorian", gregorian)
    );
}

std::string Edition::getPublishedEditionOfTitle() {
    return published_edition_of_title;
}

const std::string &Edition::getTitleTransliterated() const {
    return title_transliterated;
}

const std::string &Edition::getTitleArabic() const {
    return title_arabic;
}

const std::string &Edition::getDescription() const {
    return description;
}

double Edition::getSort() const {
    return sort;
}

