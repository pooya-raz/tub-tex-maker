//
// Created by pooya on 4/26/22.
//

#include "entry_builder.h"
#include "../models/title_type.h"
#include <iostream>

Entry entry_builder::build_entry(TubJson tubJson) {
    auto parseCategory
            {
                    [](const std::string& string)
                    {
                        try{
                            if(string == "Category:Manuscript-only title" ) return Category {ManuscriptOnly};
                            if(string == "Category:Edited title") return Category {Edited};
                            if(string == "Category:Non-extant title") return Category {NonExtant};
                            throw "Unknown category: " + string;
                        }
                        catch (const char* exception){
                            std::cerr << "Error: " << exception <<std::endl;
                        }
                    }
            };

    auto parseGregorianDate {
        [](const std::string& string)
        {
            if(string == "NO DATA") return 0;
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
    auto category= parseCategory(tubJson.at("printouts").at("Category").at(0).get("fulltext"));
    /*
     * Get author details
     */
    auto author_name_transliterated = tubJson.at("printouts").at("Full name (transliterated)").get(0);
    auto death_hijri = tubJson.at("printouts").at("Death (Hijri)").get_int(0);
    auto death_gregorian = parseGregorianDate(tubJson.at("printouts").at("Death (Gregorian)").at(0).get("raw"));
    auto death_hijri_text = tubJson.at("printouts").at("Death (Hijri) text").get(0);
    auto death_gregorian_text= tubJson.at("printouts").at("Death (Gregorian) text").get(0);

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
                    author};
    return new_entry;
}

std::vector<Entry> entry_builder::build_entries(TubJson json) {
    std::vector<Entry> entries;
    for (const TubJson &entry: json.get_entries()) {
        auto new_entry = build_entry(entry);
        entries.push_back(new_entry);
    }
    return entries;
}
