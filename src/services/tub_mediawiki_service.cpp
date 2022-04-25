//
// Created by pooya on 4/25/22.
//

#include "tub_mediawiki_service.h"

std::string tub_mediawiki_service::getQuery(std::string query) {
    BOOST_LOG_TRIVIAL(info) << "HTTP call to TUB";
    auto url = "http://144.173.140.108:8080/tub/api.php?action=ask&format=json&query=" + query;
    cpr::Response response = cpr::Get(cpr::Url{url});
    if(response.status_code != 200)
    {
        BOOST_LOG_TRIVIAL(error) << "There was an error retrieving the data. HTTP error code: " << response.status_code;
    }
    BOOST_LOG_TRIVIAL(info) << "Successful. Status code: " << response.status_code;

    return response.text;
}
