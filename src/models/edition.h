//
// Created by pooya on 5/7/22.
//

#ifndef TUB_PDF_MAKER_EDITION_H
#define TUB_PDF_MAKER_EDITION_H

#include <string>
#include <fmt/core.h>

enum Field {
    f_editor, f_edition_type, f_publisher, f_city
};

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
    int year_shamsi{};
    std::string year_hijri_text{};
    std::string year_gregorian_text{};
    std::string year_shamsi_text{};
    std::string description{};
    std::string published_edition_of_title{};
    double sort{};

    static std::string create_tex(const std::string &value, Field field);

public:
    Edition(std::string title_transliterated,
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
            double sort);

    std::string to_latex();

    std::string getPublishedEditionOfTitle();

    [[nodiscard]] const std::string &getTitleTransliterated() const;

    [[nodiscard]] const std::string &getTitleArabic() const;

    [[nodiscard]] const std::string &getDescription() const;

    [[nodiscard]] std::string getDates();

    [[nodiscard]] double getSort() const;

};

#endif //TUB_PDF_MAKER_EDITION_H
