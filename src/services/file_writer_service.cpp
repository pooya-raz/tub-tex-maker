//
// Created by pooya on 4/25/22.
//

#include "file_writer_service.h"

void file_writer_service::save_to_file(const std::string& text)
{
    std::ofstream file;
    file.open("output.latex");
    file << text;
    file.close();
}