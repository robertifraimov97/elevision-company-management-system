//
// Created by Robert Ifraimov on 25/08/2024.
//

//#ifndef FINAL_PROJECT_IN_C_VIEWER_H
//#define FINAL_PROJECT_IN_C_VIEWER_H

//#endif //FINAL_PROJECT_IN_C_VIEWER_H
#ifndef VIEWER
#define VIEWER
#include "Person.h"
#include "Contract.h"
#include "Channel.h"
#include "General.h"
#define VIEWER_MIN_AGE 18



typedef struct
{
    Person person;
    Contract contract;
    Channel* channelArr;
    int numOfChannelArr;
}Viewer;


int initViewer(Viewer* pViewer);
void printViewer(const Viewer* pViewer);
void freeViewer(Viewer* viewer);


#endif //
