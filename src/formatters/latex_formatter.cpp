//
// Created by pooya on 5/1/22.
//

#include "latex_formatter.h"


std::string latex_formatter::to_latex(const EntryMap &entryMap) {
    auto build_section{
            [](TitleType title_type, const std::string &label, const EntryMap &map) {
                if (map.contains(title_type)) {
                    auto entriesv = map.at(title_type);

                    std::string output = fmt::format("\\section{{{}}}\n\\begin{{enumerate}}\n", label);
                    auto latex_fold = [](
                            std::string a,
                            const std::shared_ptr<Entry> &b) {
                        return std::move(a) + b->to_latex();
                    };
                    auto entries = std::accumulate(
                            std::next(entriesv.begin()),
                            entriesv.end(),
                            entriesv[0]->to_latex(),
                            latex_fold);
                    output += entries + "\\end{enumerate}\n";
                    return output;
                } else {
                    std::string empty;
                    return empty;
                }
            }
    };

    std::string final;
    final += " \\documentclass{article}\n"
             "    \\usepackage{fontspec,lipsum}\n"
             "    \\defaultfontfeatures{Ligatures=TeX}\n"
             "    \\usepackage[small,sf,bf]{titlesec}\n"
             "    \\setmainfont[BoldFont={Gentium Basic Bold}]{Gentium Plus}"
             "    \\newfontfamily\\arabicfont[Script=Arabic]{Amiri}\n"
             "    \\usepackage{polyglossia}\n"
             "    \\setmainlanguage{english}\n"
             "    \\setotherlanguage{arabic}\n"
             "    \\title{Twelver Usul Bibliography}\n"
             "    \\author{The TUB Team}\n"
             "    \\date{\\today} \n"
             "    \\begin{document}\n"
             "    \\maketitle\n"
             "    \\tableofcontents\n"
             "    \\pagebreak\n";

    std::map<TitleType, std::string> section_map{
            {Monograph,            "Monograph"},
            {Treatise,             "Treatise (risāla)"},
            {Commentary,           "Commentary (sharḥ)"},
            {Gloss,                "Gloss (ḥāshīyah)"},
            {MarginalNotes,        "Marginal notes (taʿlīqa)"},
            {Summary,              "Summary (khulāṣa/mukhtaṣar)"},
            {Poem,                 "Poem (manẓūma)"},
            {Refutation,           "Refutation (radd)"},
            {Taqrirat,             "Taqrīrāt"},
            {tCorrectionsRequired, "Corrections required in title type"},
    };

    for (const auto &section: section_map) {
        final += build_section(section.first, section.second, entryMap);
    }
    final += "\\end{document}";
    return final;
}