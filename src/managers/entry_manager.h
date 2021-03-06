//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_MANAGER_H
#define TUB_PDF_MAKER_ENTRY_MANAGER_H

#include "../models/entry.h"
#include "../models/manuscript.h"
#include <nlohmann/json.hpp>
#include "../TubJson.h"
#include <vector>

typedef std::vector<std::shared_ptr<Entry>> EntryVec;
typedef std::map<TitleType, EntryVec> EntryMap;

class EntryManager {
private:
    EntryVec entries;
    EntryMap entryMap;

    std::shared_ptr<Entry> add_entry(TubJson &json);

    Manuscript add_manuscript(TubJson &json);

    Edition add_edition(TubJson &json);

    static Author add_author(TubJson &json);

public:
    void add_entries(TubJson &json);

    void add_manuscripts(TubJson &json);

    void add_editions(TubJson &json);

    void add_commentaries();

    void add_authors(TubJson &json);

    EntryVec &getEntries();

    EntryMap &getEntryMap();

    void sort_all();

    static double createSort(int hijri, int gregorian, int shamsi);

    void add_translators(TubJson &json);
};


#endif //TUB_PDF_MAKER_ENTRY_MANAGER_H
