//
// Created by pooya on 5/1/22.
//

#include "latex_formatter.h"

std::string latex_formatter::to_latex(const EntryMap& entryMap) {
    auto build_section {
        [](TitleType title_type, const std::string& label, const EntryMap& map){
            if(map.contains(title_type))
            {
                std::string output = fmt::format("\\section{{{}}}\n\\begin{{enumerate}}\n",label);
                auto treatises = map.at(title_type);
                auto latex_fold = [](
                        std::string a,
                        const std::shared_ptr<Entry>& b) {
                    return std::move(a) + b->to_latex();
                };
                auto entries = std::accumulate(
                        std::next(treatises.begin()),
                        treatises.end(),
                        treatises[0]->to_latex(),
                        latex_fold);
                output += entries + "\\end{enumerate}";
                return output;
            }
            else{
                std::string empty;
                return empty;
            }
        }
    };

    std::string final;
    std::map<TitleType,std::string> section_map {
        {Monograph,"Monograph"},
        {Treatise,"Treatise (risāla)"},
        {Commentary,"Commentary (sharḥ)"},
        {Gloss,"Gloss (ḥāshīyah)"},
        {MarginalNotes,"Marginal notes (taʿlīqa)"},
        {Summary,"Summary (khulāṣa/mukhtaṣar)"},
        {Poem,"Poem (manẓūma)"},
        {Refutation,"Refutation (radd)"},
        {Taqrirat,"Taqrīrāt"},
        {Translation," Translation"},
    };
    for (const auto& section: section_map){
            final += build_section(section.first, section.second,entryMap);
    }
    return final;
}