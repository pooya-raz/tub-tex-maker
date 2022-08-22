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
             std::string base_text,
             std::string author_page_title,
             std::string translator_page_title,
             std::string fullurl
) :
        id(std::move(id)),
        title_transliterated(std::move(title_transliterated)),
        title_arabic(std::move(title_arabic)),
        description(std::move(description)),
        category(category),
        corrections_required(std::move(corrections_required)),
        title_type(title_type),
        base_text(std::move(base_text)),
        author_page_title(std::move(author_page_title)),
        translator_page_title(std::move(translator_page_title)),
        fullurl(std::move(fullurl)) {}

std::string Entry::to_latex() {

    /*
     * Create manuscript subsection
     */
    auto manuscripts_to_latex = [this]() {
        std::string manu_latex = "\\textbf{Principal Manuscripts}\n\\begin{itemize}\n";
        if (manuscripts.empty()) {
            manu_latex += "\\item NO DATA\n";

        } else {
            int size = (int) this->manuscripts.size();
            int stop = 5;
            if (size < 5) {
                stop = size;
            }
            for (int i = 0; i < stop; i++) {
                manu_latex += this->manuscripts[i].to_latex();
            }
        }

        manu_latex += "\\end{itemize}\n";
        return manu_latex;
    };

    /*
     * Create edition subsection
     */
    auto editions_to_latex = [this]() {
        if (category == Edited) {
            std::string edition_latex = "\\textbf{Editions}\n\\begin{itemize}\n";
            if (editions.empty()) {
                edition_latex += "\\item NO DATA\n";

            } else {
                for (auto &edition: this->editions) {
                    edition_latex += edition.to_latex();
                }
            }

            edition_latex += "\\end{itemize}\n";
            return edition_latex;
        }
        return std::string();
    };

    /*
     * Create commentaries subsection
     */


    auto commentaries_to_latex = [this]() {

        auto commentary_to_latex = [](const std::shared_ptr<Entry> &entry) {
            return fmt::format("\\item \\emph{{{transliterated_title}}}, {author} {death_dates}\n",
                               fmt::arg("transliterated_title", entry->getTitleTransliterated()),
                               fmt::arg("author", entry->author.getName()),
                               fmt::arg("death_dates", entry->author.getDeathDates())
            );
        };

        if (!commentaries.empty()) {
            std::string commentaries_latex = "\\textbf{Commentaries}\n\\begin{itemize}\n";
            for (const auto &commentary: commentaries) {
                commentaries_latex += commentary_to_latex(commentary);
            }
            commentaries_latex += "\\end{itemize}\n";
            return commentaries_latex;
        } else {
            std::string empty;
            return empty;
        }
    };

    if (title_type == Translation) {
        return fmt::format("\\item {transliterated_title}\n"
                           "        \\newline\n"
                           "        \\textarabic{{{arabic_title}}}\n"
                           "        \\newline\n"
                           "        trans. {translator}\n"
                           "        \\newline\n"
                           "        {death_dates}\n"
                           "        \\newline\n"
                           "        \\newline\n"
                           "        {manuscripts}"
                           "        {editions}"
                           "        {commentaries}"
                           "\n",
                           fmt::arg("fullurl", fullurl),
                           fmt::arg("transliterated_title", title_transliterated),
                           fmt::arg("arabic_title", title_arabic),
                           fmt::arg("translator", translator.getName()),
                           fmt::arg("death_dates", translator.getDeathDates()),
                           fmt::arg("manuscripts", manuscripts_to_latex()),
                           fmt::arg("editions", editions_to_latex()),
                           fmt::arg("commentaries", commentaries_to_latex())
        );
    }

    return fmt::format("\\item \\href{{{fullurl}}}{{{transliterated_title}}}\n"
                       "        \\newline\n"
                       "        \\textarabic{{{arabic_title}}}\n"
                       "        \\newline\n"
                       "        {author}\n"
                       "        \\newline\n"
                       "        {death_dates}\n"
                       "        \\newline\n"
                       "        \\newline\n"
                       "        {manuscripts}"
                       "        {editions}"
                       "        {commentaries}"
                       "\n",
                       fmt::arg("fullurl", fullurl),
                       fmt::arg("transliterated_title", title_transliterated),
                       fmt::arg("arabic_title", title_arabic),
                       fmt::arg("author", author.getName()),
                       fmt::arg("death_dates", author.getDeathDates()),
                       fmt::arg("manuscripts", manuscripts_to_latex()),
                       fmt::arg("editions", editions_to_latex()),
                       fmt::arg("commentaries", commentaries_to_latex())
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

Author &Entry::getAuthor() {
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

const std::string &Entry::getBaseText() const {
    return base_text;
}

const std::vector<CorrectionsRequired> &Entry::getCorrectionsRequired() const {
    return corrections_required;
}

const std::string &Entry::getAuthorPageTitle() const {
    return author_page_title;
}

void Entry::setAuthor(Author n_author) {
    Entry::author = n_author;
}

void Entry::addCorrectionsRequired(CorrectionsRequired correctionsRequired) {
    corrections_required.push_back(correctionsRequired);
}

Author &Entry::getTranslator() {
    return translator;
}

void Entry::setTranslator(Author n_translator) {
    Entry::translator = n_translator;
}

const std::string &Entry::getTranslatorPageTitle() const {
    return translator_page_title;
}

const std::string &Entry::getFullurl() const {
    return fullurl;
}
