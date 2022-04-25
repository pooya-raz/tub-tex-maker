//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_TUB_MEDIAWIKI_SERVICE_H
#define TUB_PDF_MAKER_TUB_MEDIAWIKI_SERVICE_H
#include <string>
#include "mediawiki_service.h"
#include <cpr/cpr.h>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

class tub_mediawiki_service: public mediawiki_service{
public:
    std::string getQuery(std::string query) override;
};


#endif //TUB_PDF_MAKER_TUB_MEDIAWIKI_SERVICE_H
