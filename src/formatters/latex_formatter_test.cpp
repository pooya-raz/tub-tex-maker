//
// Created by pooya on 5/1/22.
//
#include <gtest/gtest.h>
#include "latex_formatter.h"
#include <fstream>

TEST(LatexFormatterTest, BasicTest) {
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

    std::shared_ptr<Entry> entry = std::make_shared<Entry>(
            "1",
            "Title Transliterated",
            "Title Arabic",
            "Description",
            Edited,
            corrections_required,
            Monograph,
            "Base Text",
            "Author Title Page");
    entry->setAuthor(author);
    entry->manuscripts = manuscripts;

    std::vector<std::shared_ptr<Entry>> monographs = {entry};


    EntryMap entryMap = {{Monograph, monographs}};

    std::string expected = " \\documentclass{article}\n    \\usepackage{fontspec,lipsum}\n    \\defaultfontfeatures{Ligatures=TeX}\n    \\usepackage[small,sf,bf]{titlesec}\n    \\setmainfont[BoldFont={Gentium Basic Bold}]{Gentium Plus}    \\newfontfamily\\arabicfont[Script=Arabic]{Amiri}\n    \\usepackage{polyglossia}\n    \\setmainlanguage{english}\n    \\setotherlanguage{arabic}\n    \\title{Twelver Usul Bibliography}\n    \\author{The TUB Team}\n    \\date{\\today} \n    \\begin{document}\n    \\maketitle\n    \\tableofcontents\n    \\pagebreak\n\\section{Monograph}\n\\begin{enumerate}\n\\item Title Transliterated\n        \\newline\n        \\textarabic{Title Arabic}\n        \\newline\n        Name Transliterated\n        \\newline\n        (d. 8th century/14th century)\n        \\newline\n        \\newline\n        \\textbf{Principal Manuscripts}\n\\begin{itemize}\n\\item Location, City (\\#Manuscript Number), dated 700/1300\n\\end{itemize}\n        \\textbf{Editions}\n\\begin{itemize}\n\\item NO DATA\n\\end{itemize}\n        \n\\end{enumerate}\n\\end{document}";
    EXPECT_EQ(expected, latex_formatter::to_latex(entryMap));
}