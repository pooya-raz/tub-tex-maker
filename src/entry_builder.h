//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_ENTRY_BUILDER_H
#define TUB_PDF_MAKER_ENTRY_BUILDER_H
#include "../src/models/entry.h"
#include <nlohmann/json.hpp>



class entry_builder {
private:
    std::string safe_get_element(int index, nlohmann::json json);
    std::string safe_get_value(const std::string& key, nlohmann::json json, int index);
public:
    std::vector<Entry> make_entry(const nlohmann::json& json);

};


#endif //TUB_PDF_MAKER_ENTRY_BUILDER_H
