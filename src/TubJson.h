//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_TUBJSON_H
#define TUB_PDF_MAKER_TUBJSON_H
#include <string>
#include <nlohmann/json.hpp>


class TubJson {
private:
    nlohmann::json m_json_tmp;
public:
    nlohmann::json m_json;
    TubJson& at(const std::string& string);
    TubJson& at(int index);
    [[nodiscard]] std::string get(const std::string& string);
    [[nodiscard]] std::string get(int index);
    [[nodiscard]] int get_int(int index);
    [[nodiscard]] int get_int(const std::string& key);
    std::vector<TubJson> get_results();

    void parse(const std::string& string);

    TubJson();
    explicit TubJson(const nlohmann::json& json);
};

#endif //TUB_PDF_MAKER_TUBJSON_H
