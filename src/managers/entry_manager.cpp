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


    /*
     * Get title details
     */
    auto id = json.get("fulltext");
    auto fullurl = json.get("fullurl");
    auto title_arabic = json.at("printouts").at("Title (Arabic)").get(0);
    auto title_transliterated = json.at("printouts").at("Title (transliterated)").get(0);
    auto description = json.at("printouts").at("Has a catalogue description").get(0);
    auto category = parseCategory(json.at("printouts").at("Category").at(0).get("fulltext"));
    auto title_type = parseTitleType(json.at("printouts").at("Book type").get(0));
    auto base_text = json.at("printouts").at("Has base text").at(0).get("fulltext");
    auto author_page_title = json.at("printouts").at("Has author(s)").at(0).get("fulltext");
    auto translator_page_title = json.at("printouts").at("Has translator(s)").get(0);
    /*
     * Check for errors
     */
    if (category == cCorrectionsRequired) corrections_required.push_back(CheckCategory);
    if (title_type == tCorrectionsRequired) corrections_required.push_back(CheckTitleType);

    auto new_entry = std::make_shared<Entry>(
            id,
            title_transliterated,
            title_arabic,
            description,
            category,
            corrections_required,
            title_type,
            base_text,
            author_page_title,
            translator_page_title,
            fullurl
    );
    return new_entry;
}

void EntryManager::add_entries(TubJson &json) {
    for (TubJson &entry: json.get_results()) {
        auto new_entry = add_entry(entry);
        entries.push_back(new_entry);
        entryMap[new_entry->getTitleType()].push_back(new_entry);
    }
}

Manuscript EntryManager::add_manuscript(TubJson &json) {
    auto location = json.at("printouts").at("Has a location").get(0);
    auto year_hijri = json.at("printouts").at("Has year(Hijri)").get_int_hijri(0);
    auto year_gregorian = json.at("printouts").at("Has year(Gregorian)").get_int(0);
    auto year_hijri_text = json.at("printouts").at("Has year(Hijri) text").get(0);
    auto year_gregorian_text = json.at("printouts").at("Has year(Gregorian) text").get(0);
    auto year_shamsi = json.at("printouts").at("Has year(Shamsi)").get_int(0);
    auto year_shamsi_text = json.at("printouts").at("Has year(Shamsi) text").get(0);
    auto city = json.at("printouts").at("Located in a city").at(0).get("fulltext");
    auto manuscript_number = json.at("printouts").at("Manuscript number").get(0);
    auto manuscript_of_title = json.at("printouts").at("Manuscript of title").at(0).get("fulltext");
    auto sort = createSort(year_hijri, year_gregorian, year_shamsi);

    return {location,
            year_hijri,
            year_gregorian,
            year_shamsi,
            year_hijri_text,
            year_gregorian_text,
            year_shamsi_text,
            city,
            manuscript_number,
            manuscript_of_title,
            sort};
}

void EntryManager::add_manuscripts(TubJson &json) {
    for (TubJson &manuscript: json.get_results()) {
        auto new_manuscript = add_manuscript(manuscript);
        for (auto &entry: entries) {
            if (new_manuscript.getManuscriptOfTitle() == entry->getId()) {
                entry->manuscripts.push_back(new_manuscript);
            }
        }
    }
}


EntryVec &EntryManager::getEntries() {
    return entries;
}

EntryMap &EntryManager::getEntryMap() {
    return entryMap;
}

Edition EntryManager::add_edition(TubJson &json) {
    auto title_transliterated = json.at("printouts").at("Title (transliterated)").get(0);
    auto title_arabic = json.at("printouts").at("Title (Arabic)").get(0);
    auto editor = json.at("printouts").at("Has editor(s)").get(0);
    auto edition_type = json.at("printouts").at("Edition type").get(0);
    auto publisher = json.at("printouts").at("Has a publisher").get(0);
    auto city = json.at("printouts").at("City").at(0).get("fulltext");
    auto year_hijri = json.at("printouts").at("Has year(Hijri)").get_int_hijri(0);
    auto year_gregorian = json.at("printouts").at("Has year(Gregorian)").get_int(0);
    auto year_shamsi = json.at("printouts").at("Has year(Shamsi)").get_int(0);
    auto year_hijri_text = json.at("printouts").at("Has year(Hijri) text").get(0);
    auto year_gregorian_text = json.at("printouts").at("Has year(Gregorian) text").get(0);
    auto year_shamsi_text = json.at("printouts").at("Has year(Shamsi) text").get(0);
    auto description = json.at("printouts").at("Has a description").get(0);
    auto published_edition_of_title = json.at("printouts").at("Published edition of title").at(0).get("fulltext");
    auto sort = createSort(year_hijri, year_gregorian, year_shamsi);
    return {title_transliterated,
            title_arabic,
            editor,
            edition_type,
            publisher,
            city,
            year_hijri,
            year_gregorian,
            year_shamsi,
            year_hijri_text,
            year_gregorian_text,
            year_shamsi_text,
            description,
            published_edition_of_title,
            sort};
}

double EntryManager::createSort(int hijri, int gregorian, int shamsi) {
    if (hijri != 9999) {
        return hijri;
    } else if (gregorian != 0) {
        return (gregorian - 622) * 1.03;
    } else if (shamsi != 0) {
        return shamsi * 1.03;
    } else {
        return 9999;
    }
}

void EntryManager::add_editions(TubJson &json) {
    for (TubJson &edition: json.get_results()) {
        auto new_edition = add_edition(edition);
        for (auto &entry: entries) {
            if (new_edition.getPublishedEditionOfTitle() == entry->getId()) {
                entry->editions.push_back(new_edition);
            }
        }
    }
}

void EntryManager::add_commentaries() {
    for (const auto &entry: entries) {
        if (entry->getBaseText() != "NO DATA") {
            for (auto &base: entries) {
                if (base->getId() == entry->getBaseText()) {
                    base->commentaries.push_back(entry);
                }
            }
        }
    }
}

void EntryManager::sort_all() {


    /*
    * Lambda helper functions for sorting entries and vectors
    */
    auto greaterc = []
            (const std::shared_ptr<Entry> &a, const std::shared_ptr<Entry> &b) {
        //Todo:Remove this and set getAuthor to const. I can't find what is setting the hijri date to 0 for entries without an author.
        if (a->getAuthor().getMDeathHijri() == 0) {
            a->getAuthor().setDeathHijri(9999);
        }
        return (a->getAuthor().getMDeathHijri() < b->getAuthor().getMDeathHijri());
    };
    auto compare_sort = []<typename T>(T a, T b) {
        return (a.getSort() < b.getSort());
    };
    /*
     * Sort all vectors in entries
     */
    for (auto &entry: entries) {
        auto &manuscripts = entry->manuscripts;
        std::sort(manuscripts.begin(), manuscripts.end(), compare_sort);

        auto &editions = entry->editions;
        std::sort(editions.begin(), editions.end(), compare_sort);

        auto &commentaries = entry->commentaries;
        std::sort(commentaries.begin(), commentaries.end(), greaterc);
    }


    for (auto &[key, categories]: entryMap) {
        std::sort(categories.begin(), categories.end(), greaterc);
    }

}


Author EntryManager::add_author(TubJson &json) {

    auto parseGregorianDate{
            [](const std::string &string) {
                if (string == "NO DATA") return 0;
                auto year = string.substr(string.find('/') + 1);
                return std::stoi(year);
            }
    };


    /*
    * Get author details
    */
    auto author_name_transliterated = json.get("fulltext");
    auto death_hijri = json.at("printouts").at("Death (Hijri)").get_int_hijri(0);
    auto death_gregorian = parseGregorianDate(json.at("printouts").at("Death (Gregorian)").at(0).get("raw"));
    auto death_shamsi = json.at("printouts").at("Death (Shamsi)").get_int_hijri(0);
    auto death_hijri_text = json.at("printouts").at("Death (Hijri) text").get(0);
    auto death_gregorian_text = json.at("printouts").at("Death (Gregorian) text").get(0);
    auto death_shamsi_text = json.at("printouts").at("Death (Shamsi) text").get(0);

    /*
     * Build models
     */
    return {author_name_transliterated,
            death_hijri,
            death_gregorian,
			death_shamsi,
            death_hijri_text,
            death_gregorian_text,
			death_shamsi_text};
}

void EntryManager::add_authors(TubJson &json) {
    for (TubJson &author_json: json.get_results()) {
        auto author = add_author(author_json);
        for (auto &entry: entries) {
            if (author.getName() == entry->getAuthorPageTitle()) {
                entry->setAuthor(author);
                if (author.getMDeathHijri() == 0 || author.getMDeathGregorian() == 0)
                    entry->addCorrectionsRequired(CheckDates);
            }
        }
    }

}

void EntryManager::add_translators(TubJson &json) {
    for (TubJson &translator_json: json.get_results()) {
        auto translator = add_author(translator_json);
        for (auto &entry: entries) {
			if (translator.getName() == entry->getTranslatorPageTitle()) {
				entry->setTranslator(translator);
                entry->setAuthor(translator);//This is for sorting purposes
                if (translator.getMDeathHijri() == 0 || translator.getMDeathGregorian() == 0)
                    entry->addCorrectionsRequired(CheckDates);
            }
        }
    }

}
