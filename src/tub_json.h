//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_TUB_JSON_H
#define TUB_PDF_MAKER_TUB_JSON_H
#include <string>
#include <nlohmann/json.hpp>


class tub_json {
public:
    nlohmann::json parse(const std::string& string);
};

#endif //TUB_PDF_MAKER_TUB_JSON_H
