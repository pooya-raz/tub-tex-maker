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

std::string entry_builder::safe_get_value(const std::string& key, nlohmann::json json, int index)
{
    if(json.contains(key)){
        nlohmann::json array = json[key];
        return safe_get_element(index, array);
    }
    return "";
}

std::vector<Entry> entry_builder::make_entry(const nlohmann::json& json) {
    std::vector<Entry> entries;
    for(nlohmann::json entry: json)
    {
        nlohmann::json printouts = entry["printouts"];
        Entry new_entry;
        new_entry.title_arabic = safe_get_value("Title (Arabic)", printouts,0);
        new_entry.title_transliteration = safe_get_value("Title (transliterated)",printouts,0);
        new_entry.author.name_transliterated = printouts["Has author(s)"][0]["fulltext"];
        entries.push_back(new_entry);
    }
    return entries;
}
