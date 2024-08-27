//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_COMPLAINTS_H
//#define FINAL_PROJECT_IN_C_COMPLAINTS_H

//#endif //FINAL_PROJECT_IN_C_COMPLAINTS_H

#ifndef COMPLAINTS
#define COMPLAINTS
#include "Date.h"
#include "Viewer.h"

typedef enum {
    eCommercialDuration, eSubtitles, eShowWithOffensiveContent, eNofComplaintsType
} eComplaintsType;

static const char* ComplaintsTypeStr[eNofComplaintsType]
        = { "Commercial duration is too long.",
            "No subtitles in the show.",
            "Commercial with offensive content."};

typedef struct
{
    eComplaintsType type;
    Date date;
    Viewer viewer;

}Complaints;

void initComplaint(Complaints* pComp,Viewer* viewer);
Viewer* checkViewer(int viewerId, Viewer* viewerArr, int arrLength);
int getComplaintType(Complaints* pComp);
void freeComplaints(Complaints* pComp);

#endif
