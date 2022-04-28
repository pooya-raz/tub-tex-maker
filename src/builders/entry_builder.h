//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_BUILDER_H
#define TUB_PDF_MAKER_ENTRY_BUILDER_H
#include "../models/entry.h"
#include <nlohmann/json.hpp>
#include "../TubJson.h"



class entry_builder {
private:
    Entry build_entry(TubJson& json);

public:
    std::vector<Entry> build_entries(TubJson& json);

};


#endif //TUB_PDF_MAKER_ENTRY_BUILDER_H
