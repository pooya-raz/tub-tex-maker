//
// Created by pooya on 5/1/22.
//

#include "latex_formatter.h"

std::string latex_formatter::to_latex(const EntryMap& entryMap) {
    TitleType title_type {Treatise};
    auto treatises = entryMap.at(title_type);
    auto latex_fold = [](
            std::string a,
            const std::shared_ptr<Entry>& b) {
        return std::move(a) + b->to_latex();
    };
    auto output = std::accumulate(
            std::next(treatises.begin()),
            treatises.end(),
            treatises[0]->to_latex(),
            latex_fold);

    return output;
}