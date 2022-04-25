//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_TUBMEDIAWIKISERVICE_H
#define TUB_PDF_MAKER_TUBMEDIAWIKISERVICE_H
#include <string>
#include "MediaWikiService.h"
#include <cpr/cpr.h>
#include <boost/log/trivial.hpp>

class TubMediaWikiService: public MediaWikiService{
private:
public:
    std::string getQuery(std::string query) override;
};


#endif //TUB_PDF_MAKER_TUBMEDIAWIKISERVICE_H
