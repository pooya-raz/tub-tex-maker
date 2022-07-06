#include "io/tub_mediawiki.h"
#include "io/file_writer.h"
#include "TubJson.h"
#include "./managers/entry_manager.h"
#include "./formatters/latex_formatter.h"

int main() {

    tub_mediawiki tub;
    file_writer fileWriter;



    auto result =  tub.getQuery(
            "[[Category:Title]]"
            "|?Category"
            "|?Book%20type"
            "|?Has%20number%20of%20commentaries"
            "|?Title%20(Arabic)"
            "|?Title%20(transliterated)"
            "|?Has%20author(s)"
            "|?Has%20a%20catalogue%20description"
            "|?Has%20base%20text"
            "|limit=1000");
    TubJson tubJson;
    tubJson.parse(result);
    fileWriter.save_to_file("entries1.json", result);
    BOOST_LOG_TRIVIAL(info) << "The offset: " << tubJson.get_int("query-continue-offset");
    auto results = tubJson.at("query").at("results");
    EntryManager entryManager;
    entryManager.add_entries(results);

    auto result2 =  tub.getQuery(
            "[[Category:Title]]"
            "|?Category"
            "|?Book%20type"
            "|?Has%20number%20of%20commentaries"
            "|?Title%20(Arabic)"
            "|?Title%20(transliterated)"
            "|?Has%20author(s)"
            "|?Has%20author(s).Full%20name%20(transliterated)"
            "|?Has%20a%20catalogue%20description"
            "|?Has%20base%20text"
            "|limit=1000"
            "|offset=1000");
    fileWriter.save_to_file("entries2.json", result2);
    TubJson tubJson1;
    tubJson1.parse(result2);
    BOOST_LOG_TRIVIAL(info) << "The offset: " << tubJson1.get_int("query-continue-offset");
    auto results2 = tubJson1.at("query").at("results");
    entryManager.add_entries(results2);



    auto manuscripts = tub.getQuery(
            "[[Category:Manuscript]]"
            "|?Has%20a%20location"
            "|?Has%20references"
            "|?Has%20year(Gregorian)"
            "|?Has%20year(Gregorian)%20text"
            "|?Has%20year(Hijri)"
            "|?Has%20year(Hijri)%20text"
            "|?Located%20in%20a%20city"
            "|?Manuscript%20number"
            "|?Manuscript%20of%20title"
            "|limit=1000"
            "|offset=0"
            );
    fileWriter.save_to_file("response-manuscript.json", manuscripts);
    TubJson manuJson;
    manuJson.parse(manuscripts);
    entryManager.add_manuscripts(manuJson);
    BOOST_LOG_TRIVIAL(info) << "The manuscript2 offset: " << manuJson.get_int("query-continue-offset");

    auto manuscripts2 = tub.getQuery(
            "[[Category:Manuscript]]"
            "|?Has%20a%20location"
            "|?Has%20references"
            "|?Has%20year(Gregorian)"
            "|?Has%20year(Gregorian)%20text"
            "|?Has%20year(Hijri)"
            "|?Has%20year(Hijri)%20text"
            "|?Located%20in%20a%20city"
            "|?Manuscript%20number"
            "|?Manuscript%20of%20title"
            "|limit=1000"
            "|offset=1000"
    );
    fileWriter.save_to_file("response-manuscript2.json", manuscripts2);
    TubJson manuJson2;
    manuJson2.parse(manuscripts2);
    entryManager.add_manuscripts(manuJson2);
    BOOST_LOG_TRIVIAL(info) << "The manuscript2 offset: " << manuJson2.get_int("query-continue-offset");

    auto manuscripts3 = tub.getQuery(
            "[[Category:Manuscript]]"
            "|?Has%20a%20location"
            "|?Has%20references"
            "|?Has%20year(Gregorian)"
            "|?Has%20year(Gregorian)%20text"
            "|?Has%20year(Hijri)"
            "|?Has%20year(Hijri)%20text"
            "|?Located%20in%20a%20city"
            "|?Manuscript%20number"
            "|?Manuscript%20of%20title"
            "|limit=1000"
            "|offset=2000"
    );
    fileWriter.save_to_file("response-manuscript3.json", manuscripts3);
    TubJson manuJson3;
    manuJson3.parse(manuscripts3);
    entryManager.add_manuscripts(manuJson3);
    BOOST_LOG_TRIVIAL(info) << "The manuscript3 offset: " << manuJson3.get_int("query-continue-offset");

    auto editions = tub.getQuery(
            "[[Category:Edition]]"
            "|?Title%20(transliterated)"
            "|?Title%20(Arabic)"
            "|?Has%20year(Gregorian)"
            "|?Has%20year(Gregorian)%20text"
            "|?Has%20year(Hijri)"
            "|?Has%20year(Hijri)%20text"
            "|?Published%20edition%20of%20title"
            "|?Has%20editor(s)"
            "|?Has%20a%20publisher"
            "|?Has%20a%20description"
            "|?Edition%20type"
            "|?City"
            "|limit=1000"
    );
    fileWriter.save_to_file("response-editions.json", editions);
    TubJson editionJson;
    editionJson.parse(editions);
    entryManager.add_editions(editionJson);
    BOOST_LOG_TRIVIAL(info) << "The offset: " << editionJson.get_int("query-continue-offset");


    /*
     * Add commentaries
     */
    entryManager.add_commentaries();
    for(const auto& entry: entryManager.getEntries()){
        if(entry->getId() == "Ḥāshiyat ʿUddat al-uṣūl - al-Ḥāshiyat al-ūlā"){
            BOOST_LOG_TRIVIAL(info) << "Entry found " << entry->getId() << "\n title type: " << entry->getTitleType();
        }
    }

    BOOST_LOG_TRIVIAL(info) << "Total number of entries: " << entryManager.getEntries().size();

    /*
   * Get all authors
   */
    auto author_result = tub.getQuery(
            "[[Category:Author]]"
            "|?Full%20name%20(transliterated)"
            "|?Death%20(Hijri)"
            "|?Death%20(Gregorian)"
            "|?Death%20(Hijri)%20text"
            "|?Death%20(Gregorian)%20text"
            "|limit=1000"
    );
    fileWriter.save_to_file("authors.json", author_result);
    TubJson tubAuthors;
    tubAuthors.parse(author_result);
    auto authors = tubAuthors.at("query").at("results");
    entryManager.add_authors(authors);

    /*
     * Sort entries, manuscripts, editions, and commentaries
     */

    entryManager.sort_all();
    /*
     * Save to latex
     */
    auto latex = latex_formatter::to_latex(entryManager.getEntryMap());
    fileWriter.save_to_file("output.latex",latex);
    return 0;


}
