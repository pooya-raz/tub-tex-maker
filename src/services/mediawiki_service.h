//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_MEDIAWIKI_SERVICE_H
#define TUB_PDF_MAKER_MEDIAWIKI_SERVICE_H


#include <string>

class mediawiki_service {
public:
    virtual std::string getQuery(std::string query) = 0;
};


#endif //TUB_PDF_MAKER_MEDIAWIKI_SERVICE_H
