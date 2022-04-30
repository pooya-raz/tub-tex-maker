//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_BUILDER_H
#define TUB_PDF_MAKER_ENTRY_BUILDER_H
#include "../models/entry.h"
#include <nlohmann/json.hpp>
#include "../TubJson.h"
#include <vector>

typedef std::vector<std::shared_ptr<Entry>> EntryVec;


class entry_builder {
private:
    EntryVec m_entries;
    std::shared_ptr<Entry> add_entry(TubJson& json);

public:
    void add_entries(TubJson& json);
    EntryVec& getEntries();

};


#endif //TUB_PDF_MAKER_ENTRY_BUILDER_H
