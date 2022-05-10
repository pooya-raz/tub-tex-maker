//
// Created by pooya on 5/1/22.
//
#include <gtest/gtest.h>
#include "latex_formatter.h"
#include <fstream>

TEST(LatexFormatterTest,BasicTest){
    EntryManager entryManager;
    TubJson tubJson;
    // Read from the text file
    std::ifstream file("/Users/pooya/Developer/sandbox/cpp/tub-tex-maker/tests/samples.json");
    std::string json_string( (std::istreambuf_iterator<char>(file) ),
                             (std::istreambuf_iterator<char>()    ) );
    tubJson.parse(json_string);
    entryManager.add_entries(tubJson);
    std::string expected= "\"\\item \\\\textbf{(Bahth fī) uṣūl al-fiqh}\n"
                          "        \\\\newline\n"
                          "        \\\\textarabic{بحث في) أصول الفقه)}\n"
                          "        \\\\newline\n"
                          "        Murtaḍā al-Ḥusaynī\n"
                          "        \\\\newline\n"
                          "        (d. NO DATA/NO DATA)\n"
                          "        \\\\newline\n"
                          "        \\\\newline\n"
                          "        \\\\textbf{Description}\n"
                          "        \\\\newline\t\n"
                          "        NO DATA\n"
                          "        \\\\newline\n"
                          "        \\\\newline\\item \\\\textbf{Abwāb al-jinān al-mushtamil ʿalā rasāʾil thamān}\n"
                          "        \\\\newline\n"
                          "        \\\\textarabic{أبواب الجنان المشتمل على رسائل ثمان}\n"
                          "        \\\\newline\n"
                          "        Muḥammad b. Faraj al-Ḥimyarī al-Najafī\n"
                          "        \\\\newline\n"
                          "        (d. c. 1059/c. 1649)\n"
                          "        \\\\newline\n"
                          "        \\\\newline\n"
                          "        \\\\textbf{Description}\n"
                          "        \\\\newline\t\n"
                          "        NO DATA\n"
                          "        \\\\newline\n"
                          "        \\\\newline";
    EXPECT_EQ(expected, latex_formatter::to_latex(entryManager.getEntryMap()));
}