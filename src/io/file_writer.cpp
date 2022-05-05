//
// Created by pooya on 4/25/22.
//

#include "file_writer.h"

void file_writer::save_to_file(const std::string& filename, const std::string& text)
{
    std::ofstream file;
    file.open(filename);
    file << text;
    file.close();
}