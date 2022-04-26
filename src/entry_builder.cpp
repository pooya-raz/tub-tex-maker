//
// Created by pooya on 4/26/22.
//

#include "entry_builder.h"
std::string entry_builder::safe_get_element(int index, nlohmann::json json){
    if(!json.empty()){
        return json[index];
    }
    return "NO DATA";
}

std::string entry_builder::safe_get_value(const std::string& key, nlohmann::json json){
    if(json.contains(key)) {
        return json[key];
    }
    return "NO DATA";
}
std::string entry_builder::safe_get_value_with_index(const std::string& key, nlohmann::json json, int index)
{
    if(json.contains(key)){
        nlohmann::json array = json[key];
        return safe_get_element(index, array);
    }
    return "NO DATA";
}
int entry_builder::safe_get_hijri(const std::string& key, nlohmann::json json){
    if(json.contains(key)) {
        if(!json[key].empty()){
            return json[key][0];
        }
        return 0;
    }
    return 0;
}

int entry_builder::safe_get_gregorian(const std::string& key, nlohmann::json json){
    if(json.contains(key)) {
        if(!json[key].empty()){
            std::string raw = json[key][0]["raw"];
            auto year = raw.substr(raw.find('/') + 1);
            return std::stoi( year );
        }
        return 0;
    }
    return 0;
}


Entry entry_builder::build_entry(const nlohmann::json & json) {
    nlohmann::json printouts = json["printouts"];
    auto id = safe_get_value("fulltext", json);
    auto title_arabic = safe_get_value_with_index("Title (Arabic)", printouts,0);
    auto title_transliterated = safe_get_value_with_index("Title (transliterated)",printouts,0);
    std::string author_name_transliterated = printouts["Has author(s)"][0]["fulltext"];
    auto description = safe_get_value_with_index("Has a catalogue description", printouts,0);

    auto death_hijri = safe_get_hijri("Death (Hijri)", printouts);
    auto death_gregorian = safe_get_gregorian("Death (Gregorian)", printouts);
    auto death_hijri_text = safe_get_value_with_index("Death (Hijri) text",printouts, 0);
    auto death_gregorian_text = safe_get_value_with_index("Death (Gregorian) text",printouts, 0);

    Author author {author_name_transliterated,
                   death_hijri,
                   death_gregorian,
                   death_hijri_text,
                   death_gregorian_text};
    Entry new_entry {id, title_transliterated, title_arabic, description, author};
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
