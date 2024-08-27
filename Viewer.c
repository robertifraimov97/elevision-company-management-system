//
// Created by Robert Ifraimov on 25/08/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "Viewer.h"

int initViewer(Viewer* pViewer)
{
    initPerson(&pViewer->person);
    if (pViewer->person.age < VIEWER_MIN_AGE)
    {
        printf("Hello, unfortunately you are still young, you can join us in %d years.\n", VIEWER_MIN_AGE - pViewer->person.age);
        return 0;
    }
    printf("Dear customer, your profile is saved in the system, this is your account number: %d Please remember it for future contact with us.\n", pViewer->person.id);
    initContract(&pViewer->contract);

    pViewer->channelArr = NULL;
    pViewer->numOfChannelArr = 0;
    return 1;
}

void printViewer(const Viewer* pViewer)
{
    PRINT_SEPARATOR_LINE();//MACRO
    printPerson(&pViewer->person);
    printContract(&pViewer->contract);
    PRINT_SEPARATOR_LINE();//MACRO
}



void freeViewer(Viewer* viewer)
{
    if (viewer->channelArr != NULL)
        free(viewer->channelArr);
}

