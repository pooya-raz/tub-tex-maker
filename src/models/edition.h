//
// Created by pooya on 5/7/22.
//

#ifndef TUB_PDF_MAKER_EDITION_H
#define TUB_PDF_MAKER_EDITION_H
#include <string>
#include <fmt/core.h>

class Edition {

private:
    std::string title_transliterated;
    std::string title_arabic;
    std::string editor;
    std::string edition_type;
    std::string publisher;
    std::string city;
    int year_hijri{};
    int year_gregorian{};
    std::string year_hijri_text{};
    std::string year_gregorian_text{};
    std::string description{};
    std::string published_edition_of_title{};
public:
    Edition(std::string title_transliterated,
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
            std::string published_edition_of_title);

    std::string to_latex();
    std::string getPublishedEditionOfTitle();
    [[nodiscard]] const std::string &getTitleTransliterated() const;

    [[nodiscard]] const std::string &getTitleArabic() const;

    [[nodiscard]] const std::string &getEditor() const;

    [[nodiscard]] const std::string &getEditionType() const;

    [[nodiscard]] const std::string &getPublisher() const;

    [[nodiscard]] const std::string &getCity() const;

    [[nodiscard]] int getYearHijri() const;

    [[nodiscard]] int getYearGregorian() const;

    [[nodiscard]] const std::string &getYearHijriText() const;

    [[nodiscard]] const std::string &getYearGregorianText() const;

    [[nodiscard]] const std::string &getDescription() const;

};


#endif //TUB_PDF_MAKER_EDITION_H
