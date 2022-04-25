//
// Created by pooya on 4/25/22.
//

#include "TubMediaWikiService.h"

std::string TubMediaWikiService::getQuery(std::string query) {
    BOOST_LOG_TRIVIAL(info) << "HTTP call to TUB";
    try
    {
        cpr::AsyncResponse asyncResponse = cpr::GetAsync(cpr::Url{"http://144.173.140.108:8080/tub/api.php?action=ask&format=json&query=[[Category:Title]]"});
        cpr::Response response = asyncResponse.get();
        return response.text;
    }
    catch(const std::exception& e){
        BOOST_LOG_TRIVIAL(error) << "Error response: " << e.what();
    }
}
