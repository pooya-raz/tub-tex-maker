//
// Created by pooya on 4/26/22.
//

#ifndef TUB_PDF_MAKER_TITLE_TYPE_H
#define TUB_PDF_MAKER_TITLE_TYPE_H
enum TitleType {
    kMonographsWithCommentaries,
    kMonographsWithoutCommentaries,
    kCommentary,
    kGloss,
    kMarginalNotes,
    kTreatise,
    kSummary,
    kPoem,
    kRefutation,
    kTaqrirat,
    kTranslation
    };
enum TitleStatus { kEdited, kManuscriptOnly, kNonExtant };
#endif //TUB_PDF_MAKER_TITLE_TYPE_H
