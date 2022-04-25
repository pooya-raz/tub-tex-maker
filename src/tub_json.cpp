//
// Created by pooya on 4/25/22.
//

#include "tub_json.h"

nlohmann::json tub_json::parse(const std::string& string) {
    return nlohmann::json::parse(string);
}
