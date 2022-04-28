//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_TITLE_TYPE_H
#define TUB_PDF_MAKER_TITLE_TYPE_H
enum TitleType {
    MonographsWithCommentaries,
    MonographsWithoutCommentaries,
    Commentary,
    Gloss,
    MarginalNotes,
    Treatise,
    Summary,
    Poem,
    Refutation,
    Taqrirat,
    Translation
};
enum Category {
    Edited,
    ManuscriptOnly,
    NonExtant,
    kCorrectionsRequired
};

enum CorrectionsRequired {
    CheckDates,
    CheckCategory,
};
#endif //TUB_PDF_MAKER_TITLE_TYPE_H
