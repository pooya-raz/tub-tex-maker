//
// Created by pooya on 4/25/22.
//

#include "TubJson.h"

TubJson::TubJson() = default;

TubJson::TubJson(const nlohmann::json& json){
    m_json = json;
    m_json_tmp = json;
}

void TubJson::parse(const std::string& string) {
    m_json = nlohmann::json::parse(string);
    m_json_tmp = m_json;
}

TubJson& TubJson::at(int index) {
    m_json_tmp = m_json_tmp[index];
    return *this;
}

TubJson& TubJson::at(const std::string& key)  {
   m_json_tmp = m_json_tmp[key];
   return *this;
}

std::string TubJson::get(const std::string& key) {
    if (m_json_tmp.contains(key)) {
        auto result =  m_json_tmp[key];
        m_json_tmp = m_json;
        return result;
    }
    m_json_tmp = m_json;
    return "NO DATA";
}

std::string TubJson::get(int index) {
    if (m_json_tmp.size() >= (index + 1)) {
       auto result =  m_json_tmp[index];
       m_json_tmp = m_json;
       return result;
    }
    m_json_tmp = m_json;
    return "NO DATA";
}

int TubJson::get_int(int index) {
    if (m_json_tmp.size() >= (index + 1)) {
        auto result =  m_json_tmp[index];
        m_json_tmp = m_json;
        return result;
    }
    m_json_tmp = m_json;
    return 0;
}

std::vector<TubJson> TubJson::get_entries() {
    std::vector<TubJson> entries;
    for(const nlohmann::json& entry: m_json["query"]["results"])
    {
        TubJson tubJson_entry(entry);
        entries.push_back(tubJson_entry);
    }
    return entries;
}
