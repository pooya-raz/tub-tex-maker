//
// Created by pooya on 4/26/22.
//

#include "author.h"

Author::Author() = default;

const std::string &Author::getName() const {
    return name_transliterated;
}

Author::Author(std::string name_transliterated,
               int death_hijri,
               int death_gregorian,
               int death_shamsi,
               std::string death_hijri_text,
               std::string death_gregorian_text,
	       std::string death_shamsi_text) :
        name_transliterated(std::move(name_transliterated)),
        death_hijri(death_hijri),
        death_gregorian(death_gregorian),
	death_shamsi(death_shamsi),
        death_hijri_text(std::move(death_hijri_text)),
        death_gregorian_text(std::move(death_gregorian_text)),
	death_shamsi_text(std::move(death_shamsi_text)){
}

int Author::getMDeathHijri() const {
    return death_hijri;
}

int Author::getMDeathGregorian() const {
    return death_gregorian;
}

const std::string &Author::getMDeathHijriText() const {
    return death_hijri_text;
}

const std::string &Author::getMDeathGregorianText() const {
    return death_gregorian_text;
}

void Author::setDeathHijri(int deathHijri) {
    death_hijri = deathHijri;
}

std::string Author::getDeathDates() const {
    std::string hijri = "NO DATA";
    std::string gregorian = "NO DATA";
	std::string shamsi = "NO DATA";

    if (death_hijri != 9999) {
        hijri = std::to_string(death_hijri);
    }
    if (death_hijri_text != "NO DATA") {
        hijri = death_hijri_text;
    }

    if (death_gregorian != 0) {
        gregorian = std::to_string(death_gregorian);
    }
    if (death_gregorian_text != "NO DATA") {
        int first_digit = 0;
        std::string only_digits;
        for (int i = 0; char c: death_gregorian_text) {
            if (std::isdigit(c)) {
                first_digit = i;
                break;
            }
            i++;
        }
        gregorian = death_gregorian_text.substr(first_digit);
    }

	if (death_shamsi != 0) {
		shamsi = std::to_string(death_shamsi);
	}
	if (death_shamsi_text != "NO DATA") {
		 int first_digit = 0;
        std::string only_digits;
        for (int i = 0; char c: death_shamsi_text) {
            if (std::isdigit(c)) {
                first_digit = i;
                break;
            }
            i++;
        }
        shamsi = death_shamsi_text.substr(first_digit);
	}


    if (gregorian != "NO DATA" && shamsi != "NO DATA") {
        return fmt::format("(d. {shamsi}Sh/{gregorian})",
                           fmt::arg("shamsi", shamsi),
                           fmt::arg("gregorian", gregorian)
        );
	}

    if (std::isdigit(hijri[0]) && shamsi != "NO DATA") {
        return fmt::format("(d. {hijri}/{shamsi}Sh)",
                           fmt::arg("hijri", hijri),
                           fmt::arg("shamsi", shamsi)
        );
	}

    if (std::isdigit(hijri[0])) {
        return fmt::format("(d. {hijri}/{gregorian})",
                           fmt::arg("hijri", hijri),
                           fmt::arg("gregorian", gregorian)
        );
    }
    if (hijri.substr(0, 5) == "after") {
        return fmt::format("(d. {hijri}/{gregorian})",
                           fmt::arg("hijri", hijri),
                           fmt::arg("gregorian", gregorian)
        );
    }
        if (hijri.substr(0, 6) == "before") {
        return fmt::format("(d. {hijri}/{gregorian})",
                           fmt::arg("hijri", hijri),
                           fmt::arg("gregorian", gregorian)
        );
    }
    if (hijri.substr(0, 2) == "c.") {
        return fmt::format("(d. {hijri}/{gregorian})",
                           fmt::arg("hijri", hijri),
                           fmt::arg("gregorian", gregorian)
        );
    }
    return fmt::format("({hijri}/{gregorian})",
                       fmt::arg("hijri", hijri),
                       fmt::arg("gregorian", gregorian)
    );


}
