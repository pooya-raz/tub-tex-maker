//
// Created by Christopher Razavian on 10/07/2022.
//
#include <gtest/gtest.h>
#include "entry.h"
#include "author.h"
#include "manuscript.h"

TEST(EntryAllFields, BasicTest) {

    Author author = Author(
            "Name Transliterated",
            0,
            0,
            "8th century",
            "14th century");
    Manuscript manuscript = Manuscript(
            "Location",
            700,
            1300,
            0,
            "NO DATA",
            "NO DATA",
            "NO DATA",
            "City",
            "Manuscript Number",
            "Manuscript of Title"
    );
    std::vector<Manuscript> manuscripts = {manuscript};
    std::vector<CorrectionsRequired> corrections_required = {};

    Entry entry = Entry(
            "1",
            "Title Transliterated",
            "Title Arabic",
            "Description",
            Edited,
            corrections_required,
            Monograph,
            "Base Text",
            "Author Title Page");
    entry.setAuthor(author);
    entry.manuscripts = manuscripts;

    auto expected = "\\item Title Transliterated\n        \\newline\n        \\textarabic{Title Arabic}\n        \\newline\n        Name Transliterated\n        \\newline\n        (d. 8th century/14th century)\n        \\newline\n        \\newline\n        \\textbf{Principal Manuscripts}\n\\begin{itemize}\n\\item Location, City (\\#Manuscript Number), dated 700/1300\n\\end{itemize}\n        \\textbf{Editions}\n\\begin{itemize}\n\\item NO DATA\n\\end{itemize}\n        \n";
    EXPECT_EQ(expected, entry.to_latex());
}
