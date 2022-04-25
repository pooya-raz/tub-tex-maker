#include <iostream>
#include "services/tub_mediawiki_service.h"
#include "services/file_writer_service.h"

int main() {

    tub_mediawiki_service tub;
    file_writer_service fileWriter;
    auto result =  tub.getQuery("[[Category:Title]]|?Title%20(Arabic)|?Title%20(transliterated)|?Has%20author(s)|?Has%20author(s).Death%20(Hijri)|?Has%20author(s).Death%20(Gregorian)|?Has%20author(s).Death%20(Hijri)%20text|?Has%20author(s).Death%20(Gregorian)%20text|?Has%20a%20catalogue%20description|limit=5");
    fileWriter.save_to_file(result);

    std::cout << "Hello, ф or \u0444!\n";
    return 0;

}
