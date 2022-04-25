//
// Created by pooya on 4/25/22.
//

#ifndef TUB_PDF_MAKER_FILE_WRITER_SERVICE_H
#define TUB_PDF_MAKER_FILE_WRITER_SERVICE_H
#include <string>
#include <fstream>

class file_writer_service {
public:
    void save_to_file(const std::string& text);
};


#endif //TUB_PDF_MAKER_FILE_WRITER_SERVICE_H
