//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_MEDIAWIKISERVICE_H
#define TUB_PDF_MAKER_MEDIAWIKISERVICE_H


#include <string>

class MediaWikiService {
public:
    virtual std::string getQuery(std::string query) = 0;
};


#endif //TUB_PDF_MAKER_MEDIAWIKISERVICE_H
