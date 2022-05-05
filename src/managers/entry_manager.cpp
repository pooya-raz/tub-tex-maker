//
// Created by pooya on 4/26/22.
//

#include "entry_manager.h"
#include <iostream>

std::shared_ptr<Entry> EntryManager::add_entry(TubJson &json) {
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
    auto id = json.get("fulltext");
    auto title_arabic = json.at("printouts").at("Title (Arabic)").get(0);
    auto title_transliterated = json.at("printouts").at("Title (transliterated)").get(0);
    auto description = json.at("printouts").at("Has a catalogue description").get(0);
    auto category = parseCategory(json.at("printouts").at("Category").at(0).get("fulltext"));
    auto title_type = parseTitleType(json.at("printouts").at("Book type").get(0));
    /*
     * Get author details
     */
    auto author_name_transliterated = json.at("printouts").at("Full name (transliterated)").get(0);
    auto death_hijri = json.at("printouts").at("Death (Hijri)").get_int(0);
    auto death_gregorian = parseGregorianDate(json.at("printouts").at("Death (Gregorian)").at(0).get("raw"));
    auto death_hijri_text = json.at("printouts").at("Death (Hijri) text").get(0);
    auto death_gregorian_text = json.at("printouts").at("Death (Gregorian) text").get(0);

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
    auto new_entry = std::make_shared<Entry>(
            id,
                    title_transliterated,
                    title_arabic,
                    description,
                    category,
                    corrections_required,
                    title_type,
                    author);
    return new_entry;
}

void EntryManager::add_entries(TubJson &json) {
    for (TubJson &entry: json.get_results()) {
        auto new_entry = add_entry(entry);
        entries.push_back(new_entry);
        if(new_entry->getAuthor().getMDeathHijri() > 0){
            entryMap[new_entry->getTitleType()].push_back(new_entry);
        }
    }
}

Manuscript EntryManager::add_manuscript(TubJson &json) {
    auto location = json.at("printouts").get("Has a location");
    auto year_hijri = json.at("printouts").at("Has year(Hijri)").get_int(0);
    auto year_gregorian = json.at("printouts").at("Has year(Gregorian)").get_int(0);
    auto year_hijri_text = json.at("printouts").at("Has year(Hijri) text").get(0);
    auto year_gregorian_text = json.at("printouts").at("Has year(Gregorian) text").get(0);
    auto city = json.at("printouts").get("Located in a city");
    auto manuscript_number= json.at("printouts").get("Manuscript number");
    auto manuscript_of_title= json.at("printouts").get("Manuscript of title");

    return {location, year_hijri, year_gregorian, year_hijri_text, year_gregorian_text, city, manuscript_number,manuscript_of_title};
}

void EntryManager::add_manuscripts(TubJson &json) {
    for (TubJson &manuscript: json.get_results()){
        auto new_manuscript = add_manuscript(manuscript);
        for (auto &entry: entries){
            if(new_manuscript.getManuscriptOfTitle() == entry->getId()){
                entry->manuscripts.push_back(new_manuscript);
            }
        }
    }
}


EntryVec& EntryManager::getEntries() {
    return entries;
}

EntryMap& EntryManager::getEntryMap() {
    return entryMap;
}
