//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_AUTHOR_H
#define TUB_PDF_MAKER_AUTHOR_H
#include <string>

class Author
{
private:
    std::string m_name_transliterated {};
public:
    Author();
    Author(std::string name_transliterated);

    const std::string &getName() const;
};


#endif //TUB_PDF_MAKER_AUTHOR_H
