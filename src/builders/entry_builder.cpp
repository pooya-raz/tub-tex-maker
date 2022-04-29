//
// Created by pooya on 4/26/22.
//

#include "entry_builder.h"
#include "../models/title_type.h"
#include <iostream>

Entry entry_builder::build_entry(TubJson &tubJson) {
    auto corrections_required = std::vector<CorrectionsRequired>();
    auto parseCategory
            {
                    [](const std::string &string) {
                        if (string == "Category:Manuscript-only title") return Category{ManuscriptOnly};
                        if (string == "Category:Edited title") return Category{Edited};
                        if (string == "Category:Non-extant title") return Category{NonExtant};
                        return Category{cCorrectionsRequired};
                    }
            };

    auto parseTitleType
            {
                    [](const std::string &string) {
                        if (string == "Monograph") return TitleType{Monograph};
                        if (string == "Treatise (risāla)") return TitleType{Treatise};
                        if (string == "Commentary (sharḥ)") return TitleType{Commentary};
                        if (string == "Gloss (ḥāshīyah)") return TitleType{Gloss};
                        if (string == "Marginal notes (taʿlīqa)") return TitleType{MarginalNotes};
                        if (string == "Summary (khulāṣa/mukhtaṣar)") return TitleType{Summary};
                        if (string == "Poem (manẓūma)") return TitleType{Poem};
                        if (string == "Refutation (radd)") return TitleType{Refutation};
                        if (string == "Taqrīrāt") return TitleType{Taqrirat};
                        if (string == "Translation") return TitleType{Translation};
                        return TitleType{tCorrectionsRequired};
                    }
            };
    auto parseGregorianDate{
            [](const std::string &string) {
                if (string == "NO DATA") return 0;
                auto year = string.substr(string.find('/') + 1);
                return std::stoi(year);
            }
    };

    /*
     * Get title details
     */
    auto id = tubJson.get("fulltext");
    auto title_arabic = tubJson.at("printouts").at("Title (Arabic)").get(0);
    auto title_transliterated = tubJson.at("printouts").at("Title (transliterated)").get(0);
    auto description = tubJson.at("printouts").at("Has a catalogue description").get(0);
    auto category = parseCategory(tubJson.at("printouts").at("Category").at(0).get("fulltext"));
    auto title_type = parseTitleType(tubJson.at("printouts").at("Book type").get(0));
    /*
     * Get author details
     */
    auto author_name_transliterated = tubJson.at("printouts").at("Full name (transliterated)").get(0);
    auto death_hijri = tubJson.at("printouts").at("Death (Hijri)").get_int(0);
    auto death_gregorian = parseGregorianDate(tubJson.at("printouts").at("Death (Gregorian)").at(0).get("raw"));
    auto death_hijri_text = tubJson.at("printouts").at("Death (Hijri) text").get(0);
    auto death_gregorian_text = tubJson.at("printouts").at("Death (Gregorian) text").get(0);

    /*
     * Check for errors
     */
    if (category == cCorrectionsRequired) corrections_required.push_back(CheckCategory);
    if (title_type == tCorrectionsRequired) corrections_required.push_back(CheckTitleType);
    if (death_hijri == 0 || death_gregorian == 0) corrections_required.push_back(CheckDates);
    /*
     * Build models
     */
    Author author{author_name_transliterated,
                  death_hijri,
                  death_gregorian,
                  death_hijri_text,
                  death_gregorian_text};
    Entry new_entry{id,
                    title_transliterated,
                    title_arabic,
                    description,
                    category,
                    corrections_required,
                    title_type,
                    author};
    return new_entry;
}

std::vector<Entry> entry_builder::build_entries(TubJson &json) {
    std::vector<Entry> entries;
    for (TubJson &entry: json.get_entries()) {
        auto new_entry = build_entry(entry);
        entries.push_back(new_entry);
    }
    return entries;
}
