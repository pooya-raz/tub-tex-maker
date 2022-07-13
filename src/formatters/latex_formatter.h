//
// Created by pooya on 5/1/22.
//

#ifndef TUB_PDF_MAKER_LATEX_FORMATTER_H
#define TUB_PDF_MAKER_LATEX_FORMATTER_H

#include <string>
#include "../managers/entry_manager.h"

namespace latex_formatter {
    std::string to_latex(const EntryMap &entryMap);
}
#endif //TUB_PDF_MAKER_LATEX_FORMATTER_H