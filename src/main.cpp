#include "io/tub_mediawiki.h"
#include "io/file_writer.h"
#include "TubJson.h"
#include "./managers/entry_manager.h"
#include "./formatters/latex_formatter.h"

int main() {

    tub_mediawiki tub;
    file_writer fileWriter;
    auto result =  tub.getQuery("[[Category:Title]]|?Category|?Book%20type|?Has%20number%20of%20commentaries|?Title%20(Arabic)|?Title%20(transliterated)|?Has%20author(s)|?Has%20author(s).Full%20name%20(transliterated)|?Has%20author(s).Death%20(Hijri)|?Has%20author(s).Death%20(Gregorian)|?Has%20author(s).Death%20(Hijri)%20text|?Has%20author(s).Death%20(Gregorian)%20text|?Has%20a%20catalogue%20description|limit=1000");
    TubJson tubJson;
    tubJson.parse(result);
    BOOST_LOG_TRIVIAL(info) << "The offset: " << tubJson.get_int("query-continue-offset");
    auto results = tubJson.at("query").at("results");
    EntryManager entryManager;
    entryManager.add_entries(results);
    auto result2 =  tub.getQuery("[[Category:Title]]|?Category|?Book%20type|?Has%20number%20of%20commentaries|?Title%20(Arabic)|?Title%20(transliterated)|?Has%20author(s)|?Has%20author(s).Full%20name%20(transliterated)|?Has%20author(s).Death%20(Hijri)|?Has%20author(s).Death%20(Gregorian)|?Has%20author(s).Death%20(Hijri)%20text|?Has%20author(s).Death%20(Gregorian)%20text|?Has%20a%20catalogue%20description|limit=1000|offset=1000");
    TubJson tubJson1;
    tubJson1.parse(result2);
    BOOST_LOG_TRIVIAL(info) << "The offset: " << tubJson1.get_int("query-continue-offset");
    auto results2 = tubJson1.at("query").at("results");
    entryManager.add_entries(results2);
    fileWriter.save_to_file("response.json", result2);
    auto latex = latex_formatter::to_latex(entryManager.getEntryMap());
    fileWriter.save_to_file("output.latex",latex);
    return 0;


}
