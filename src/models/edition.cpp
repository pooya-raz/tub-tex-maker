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
                 std::string year_hijri_text,
                 std::string year_gregorian_text,
                 std::string description,
                 std::string published_edition_of_title
                 ):
        title_transliterated(std::move(title_transliterated)),
        title_arabic(std::move(title_arabic)),
        editor(std::move(editor)),
        edition_type(std::move(edition_type)),
        publisher(std::move(publisher)),
        city(std::move(city)),
        year_hijri(year_hijri),
        year_gregorian(year_gregorian),
        year_hijri_text(std::move(year_hijri_text)),
        year_gregorian_text(std::move(year_gregorian_text)),
        description(std::move(description)),
        published_edition_of_title(std::move(published_edition_of_title)){}

        std::string Edition::to_latex() {
    auto getDates= [this](){
        std::string hijri = "NO DATA";
        std::string gregorian = "NO DATA";

        if(year_hijri != 0){
            hijri = std::to_string(year_hijri);

        }
        if(year_hijri_text != "NO DATA")
        {
            hijri = year_hijri_text;
        }

        if(year_gregorian != 0)
        {
            gregorian = std::to_string(year_gregorian);
        }
        if(year_gregorian_text != "NO DATA")
        {
            gregorian = year_gregorian_text;
        }

        return fmt::format("{hijri}/{gregorian}",
                           fmt::arg("hijri",hijri),
                           fmt::arg("gregorian",gregorian)
        );
    };

    return fmt::format("\\item \\emph{{{title}}}, {editor}, {edition_type}, {publisher}, {city}, {dates}\n",
                       fmt::arg("title", title_transliterated),
                       fmt::arg("editor", editor),
                       fmt::arg("edition_type", edition_type),
                       fmt::arg("publisher", publisher),
                       fmt::arg("city", city),
                       fmt::arg("dates", getDates())
    );
}

std::string Edition::getPublishedEditionOfTitle() {
    return published_edition_of_title;
}

