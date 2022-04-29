//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_TITLE_TYPE_H
#define TUB_PDF_MAKER_TITLE_TYPE_H
enum TitleType {
    Monograph,
    Commentary,
    Gloss,
    MarginalNotes,
    Treatise,
    Summary,
    Poem,
    Refutation,
    Taqrirat,
    Translation,
    tCorrectionsRequired,
};
enum Category {
    Edited,
    ManuscriptOnly,
    NonExtant,
    cCorrectionsRequired
};

enum CorrectionsRequired {
    CheckDates,
    CheckCategory,
    CheckTitleType
};
#endif //TUB_PDF_MAKER_TITLE_TYPE_H
