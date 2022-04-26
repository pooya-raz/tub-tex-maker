//
// Created by pooya on 4/26/22.
//

#include "entry_builder.h"
std::string entry_builder::safe_get_element(int index, nlohmann::json json){
    if(!json.empty()){
        return json[index];
    }
    return "";
}

std::string entry_builder::safe_get_value(const std::string& key, nlohmann::json json){
    if(json.contains(key)) {
        return json[key];
    }
    return "";
}
std::string entry_builder::safe_get_value_with_index(const std::string& key, nlohmann::json json, int index)
{
    if(json.contains(key)){
        nlohmann::json array = json[key];
        return safe_get_element(index, array);
    }
    return "";
}

Entry entry_builder::build_entry(const nlohmann::json & json) {
    nlohmann::json printouts = json["printouts"];
    auto id = safe_get_value("fulltext", json);
    auto title_arabic = safe_get_value_with_index("Title (Arabic)", printouts,0);
    auto title_transliterated = safe_get_value_with_index("Title (transliterated)",printouts,0);
    std::string author_name_transliterated = printouts["Has author(s)"][0]["fulltext"];

    Author author {author_name_transliterated};
    Entry new_entry {id, title_transliterated, title_arabic, author};
    return new_entry;
}

std::vector<Entry> entry_builder::build_entries(const nlohmann::json& json) {
    std::vector<Entry> entries;
    for(const nlohmann::json& entry: json)
    {
        auto new_entry = build_entry(entry);
        entries.push_back(new_entry);
    }
    return entries;
}
