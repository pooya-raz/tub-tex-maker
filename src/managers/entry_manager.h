//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_MANAGER_H
#define TUB_PDF_MAKER_ENTRY_MANAGER_H
#include "../models/entry.h"
#include <nlohmann/json.hpp>
#include "../TubJson.h"
#include <vector>

typedef std::vector<std::shared_ptr<Entry>> EntryVec;
typedef std::map<TitleType, EntryVec > EntryMap;

class EntryManager {
private:
    EntryVec entries;
    EntryMap entryMap;
    std::shared_ptr<Entry> add_entry(TubJson& json);

public:
    void add_entries(TubJson& json);
    EntryVec& getEntries();
    EntryMap& getEntryMap();

};


#endif //TUB_PDF_MAKER_ENTRY_MANAGER_H
