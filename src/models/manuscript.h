//
// Created by pooya on 5/5/22.
//

#ifndef TUB_PDF_MAKER_MANUSCRIPT_H
#define TUB_PDF_MAKER_MANUSCRIPT_H

#include <string>
#include <fmt/core.h>


class Manuscript {
private:
    std::string location{};
    int year_hijri{};
    int year_gregorian{};
    int year_shamsi{};
    std::string year_hijri_text{};
    std::string year_gregorian_text{};
    std::string year_shamsi_text{};
    std::string city{};
    std::string manuscript_number{};
    std::string manuscript_of_title{};

public:
    Manuscript();

    Manuscript(
            std::string location,
            int year_hijri,
            int year_gregorian,
            int year_shamsi,
            std::string year_hijri_text,
            std::string year_gregorian_text,
            std::string year_shamsi_text,
            std::string city,
            std::string manuscript_number,
            std::string manuscript_of_title
    );

    [[nodiscard]] const std::string &getManuscriptOfTitle() const;

    [[nodiscard]] const std::string &getLocation() const;

    [[nodiscard]] int getYearHijri() const;

    [[nodiscard]] int getYearGregorian() const;

    [[nodiscard]] const std::string &getYearHijriText() const;

    [[nodiscard]] const std::string &getYearGregorianText() const;

    [[nodiscard]] const std::string &getCity() const;

    [[nodiscard]] const std::string &getManuscriptNumber() const;

    [[nodiscard]] std::string getDates() const;

    [[nodiscard]] std::string to_latex() const;
};


#endif //TUB_PDF_MAKER_MANUSCRIPT_H
