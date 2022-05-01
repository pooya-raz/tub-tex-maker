//
// Created by pooya on 4/26/22.
//

#include "entry.h"

Entry::Entry() = default;

Entry::Entry(std::string id,
             std::string title_transliterated,
             std::string title_arabic,
             std::string description,
             Category category,
             std::vector<CorrectionsRequired> corrections_required,
             TitleType title_type,
             Author author):
    id(std::move(id)),
    title_transliterated(std::move(title_transliterated)),
    title_arabic(std::move(title_arabic)),
    author(std::move(author)),
    description(std::move(description)),
    corrections_required(std::move(corrections_required)),
    title_type(title_type),
    category(category)
    {}

std::string Entry::to_latex() {

    return fmt::format("\\item \\textbf{{{transliterated_title}}}\n"
                                    "        \\newline\n"
                                    "        \\textarabic{{{arabic_title}}}\n"
                                    "        \\newline\n"
                                    "        {author}\n"
                                    "        \\newline\n"
                                    "        {death_dates}\n"
                                    "        \\newline\n"
                                    "        \\newline\n"
                                    "        \\textbf{{Description}}\n"
                                    "        \\newline\t\n"
                                    "        {description}\n"
                                    "        \\newline\n"
                                    "        \\newline",
                                    fmt::arg("transliterated_title",title_transliterated),
                                    fmt::arg("arabic_title",title_arabic),
                                    fmt::arg("author",author.getName()),
                                    fmt::arg("death_dates",author.getDeathDates()),
                                    fmt::arg("description",description)
                                    );
}

const std::string &Entry::getId() const {
    return id;
}

const std::string &Entry::getTitleTransliterated() const {
    return title_transliterated;
}

const std::string &Entry::getTitleArabic() const {
    return title_arabic;
}

const Author &Entry::getAuthor() const {
    return author;
}

const std::string &Entry::getDescription() const {
    return description;
}


const Category &Entry::getCategory() const {
    return category;
}


const TitleType &Entry::getTitleType() const {
    return title_type;
}

const std::vector<CorrectionsRequired> &Entry::getCorrectionsRequired() const {
    return corrections_required;
}