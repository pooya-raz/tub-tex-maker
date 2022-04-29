#include "io/tub_mediawiki.h"
#include "io/file_writer.h"
#include "TubJson.h"
#include "./builders/entry_builder.h"

int main() {

    tub_mediawiki tub;
    file_writer fileWriter;
    auto result =  tub.getQuery("[[Category:Title]]|?Category|?Has%20number%20of%20commentaries|?Title%20(Arabic)|?Title%20(transliterated)|?Has%20author(s)|?Has%20author(s).Full%20name%20(transliterated)|?Has%20author(s).Death%20(Hijri)|?Has%20author(s).Death%20(Gregorian)|?Has%20author(s).Death%20(Hijri)%20text|?Has%20author(s).Death%20(Gregorian)%20text|?Has%20a%20catalogue%20description|limit=1000");
    fileWriter.save_to_file(result);

    return 0;

}
