#include "io/tub_mediawiki.h"
#include "io/file_writer.h"
#include "tub_json.h"
#include "./builders/entry_builder.h"

int main() {

    tub_mediawiki tub;
    file_writer fileWriter;
    auto result =  tub.getQuery("[[Category:Title]]|?Category|?Title%20(Arabic)|?Title%20(transliterated)|?Has%20author(s)|?Has%20author(s).Full%20name%20(transliterated)|?Has%20author(s).Death%20(Hijri)|?Has%20author(s).Death%20(Gregorian)|?Has%20author(s).Death%20(Hijri)%20text|?Has%20author(s).Death%20(Gregorian)%20text|?Has%20a%20catalogue%20description|limit=1000");
    fileWriter.save_to_file(result);
    tub_json tubJson;
    auto json = tubJson.parse(result);
    auto results = json["query"]["results"];
    entry_builder entryBuilder;
    auto entries = entryBuilder.build_entries(results);
    for (auto entry: entries)
    {
        std::cout<<entry.to_string()<<std::endl;
    }

    return 0;

}
