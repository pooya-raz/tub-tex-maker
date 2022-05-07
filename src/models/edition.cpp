//
// Created by pooya on 5/7/22.
//

#include "edition.h"

#include <utility>

Edition::Edition(std::string title, std::string editor, std::string editionType,
                 std::string publisher, std::string city, int yearHijri, int yearGregorian,
                 std::string yearHijriText, std::string yearGregorianText):
        title(std::move(title)), editor(std::move(editor)),
        edition_type(std::move(editionType)),
        publisher(std::move(publisher)),
        city(std::move(city)),
        year_hijri(yearHijri),
        year_gregorian(yearGregorian),
        year_hijri_text(std::move(yearHijriText)),
        year_gregorian_text(std::move(yearGregorianText)) {}

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

    return fmt::format("\\item \\emph{{{title}}}{editor}, {edition_type}, {publisher}, {city}, {dates}",
                       fmt::arg("title", title),
                       fmt::arg("editor", editor),
                       fmt::arg("edition_type", edition_type),
                       fmt::arg("city", city),
                       fmt::arg("dates", getDates())
    );
}