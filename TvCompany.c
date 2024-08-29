
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TvCompany.h"
static int next_id = 1;

void initTvCompany(TvCompany* pCompany)
{
    pCompany->companyName = getStrExactName("Enter a name for your TV COMPANY:\n");

    pCompany->channelArr = NULL;
    pCompany->complaintsArr = NULL;
    pCompany->employeeArr = NULL;
    pCompany->viewerArr = NULL;

    pCompany->numOfChannels = 0;
    pCompany->numOfCompliants = 0;
    pCompany->numOfEmployees = 0;
    pCompany->numOfViewers = 0;
    pCompany->sortType = 0;
}

int addChannelsToViewerByContractType(TvCompany* pCompany, Viewer* pViewer)
{
    if (pViewer->contract.type == 1)
    {
        if (pCompany->numOfChannels < 2)
            return 0;

        pViewer->channelArr = malloc(sizeof(Channel) * BASIC_CHANNELS);
        if (!pViewer->channelArr)
            return 0;

        for (int i = 0; i < BASIC_CHANNELS; i++)
        {
            pViewer->channelArr[i] = pCompany->channelArr[i];
        }
        pViewer->numOfChannelArr = BASIC_CHANNELS;

    }
    else if (pViewer->contract.type == 2)
    {
        if (pCompany->numOfChannels < 3)
            return 0;
        pViewer->channelArr = malloc(sizeof(Channel) * PREMIUM_CHANNELS);
        if (!pViewer->channelArr)
            return 0;

        for (int i = 0; i < PREMIUM_CHANNELS; i++)
        {
            pViewer->channelArr[i] = pCompany->channelArr[i];
        }
        pViewer->numOfChannelArr = PREMIUM_CHANNELS;
    }
    else
    {
        if (pCompany->numOfChannels < 5)
            return 0;

        pViewer->channelArr = malloc(sizeof(Channel) * VIP_CHANNELS);
        if (!pViewer->channelArr)
            return 0;

        for (int i = 0; i < VIP_CHANNELS; i++)
        {
            pViewer->channelArr[i] = pCompany->channelArr[i];
        }
        pViewer->numOfChannelArr = VIP_CHANNELS;

    }
    return 1;
}

int addEmployee(TvCompany* pCompany)
{
    Employee* pEmployee = (Employee*)calloc(1, sizeof(Employee));
    if (!pEmployee)
        return 0;

    if (!initEmployee(pEmployee))
    {
        free(pEmployee);
        return 0;
    }
    pCompany->employeeArr = (Employee**)realloc(pCompany->employeeArr, (pCompany->numOfEmployees + 1) * sizeof(Employee*));
    if (!pCompany->employeeArr)
    {
        free(pCompany);
        return 0;
    }
    pCompany->employeeArr[pCompany->numOfEmployees++] = pEmployee;
    return 1;
}

int addViewer(TvCompany* pCompany)
{
    if (pCompany->numOfChannels < 2)
    {
        printf("There are not enough channels in Tvcompany.(in order to add a viewer you must first create at least 2 channels)\n");
        return 0;
    }
    Viewer* pViewer = (Viewer*)malloc(sizeof(Viewer));
    if (!pViewer)
        return 0;

    if (!initViewer(pViewer))
    {
        free(pViewer);
        return 0;
    }

    if (addChannelsToViewerByContractType(pCompany, pViewer) == 0)
    {
        printf("Dear customer, after checking we found that there are not enough channels to create a viewer with this subscription, therefore we cannot create a contract.\n");
        free(pViewer);
        return 0;
    }


    pCompany->viewerArr = (Viewer**)realloc(pCompany->viewerArr, (pCompany->numOfViewers + 1) * sizeof(Viewer*));
    if (!pCompany->viewerArr)
    {
        free(pCompany);
        return 0;
    }
    pCompany->viewerArr[pCompany->numOfViewers++] = pViewer;
    return 1;
}

int addChannel(TvCompany* pCompany)
{
    Channel* newChannel = (Channel*)realloc(pCompany->channelArr, (pCompany->numOfChannels + 1) * sizeof(Channel));
    if (!newChannel)
    {
        printf("Memory allocation failed. Unable to add channel.\n");
        return 0;
    }

    initChannel(&newChannel[pCompany->numOfChannels]);

    if (channelNumberExist(newChannel[pCompany->numOfChannels].ChannelNum, newChannel, pCompany->numOfChannels))
    {
        printf("This channel number already exists.\n");
        pCompany->channelArr = newChannel;
        //free(newChannel);
        return 0;
    }

    pCompany->channelArr = newChannel;
    pCompany->numOfChannels++;
    return 1;
}

int addComplaint(TvCompany* pCompany)
{
    if (!(pCompany->viewerArr))
    {
        printf("NO viewers in Tvcompany.(In order to create a complaint you must first add a viewer)\n");
        return 0;
    }
    Complaints* newComplaint = (Complaints*)realloc(pCompany->complaintsArr, (pCompany->numOfCompliants + 1) * sizeof(Complaints));
    if (!newComplaint)
    {
        printf("Memory allocation failed. Unable to add complaint.\n");
        return 0;
    }

    printf("Dear customer, in order to create a new complaint in the system, please enter your account number.\n");
    int numOfAccount;
    do
    {
        if (scanf("%d", &(numOfAccount)) != 1) {
            printf("Please enter a valid account number:\n");
            while (getchar() != '\n');
        }
        else if (numOfAccount < 0) {
            printf("Please enter a positive account number:\n");

            while (getchar() != '\n');
        }
    } while (numOfAccount < 0);

    Viewer* viewer = viewerNumberExist(numOfAccount, pCompany->viewerArr, pCompany->numOfViewers);
    if (!viewer)
    {
        printf("This account number does not exist in our system.\n");
        return 0;
    }

    int channelUserChoice = 0;
    for (int i = 0; i < pCompany->numOfChannels; i++)
    {
        PRINT_SEPARATOR_LINE(); // MACRO
        printChannel(&pCompany->channelArr[i]);
        printf("\n");
        printf("\n");
    }
    PRINT_SEPARATOR_LINE(); // MACRO

    printf("Pick a channel number\n");
    scanf("%d", &channelUserChoice);
    Channel* userChannel = channelNumberExist(channelUserChoice, pCompany->channelArr, pCompany->numOfChannels);

    initComplaint(&(newComplaint[pCompany->numOfCompliants]), viewer);
    if (!isComplaintAccepted(pCompany, newComplaint, userChannel))
    {
        pCompany->complaintsArr = newComplaint;
        return 0;
    }

    pCompany->complaintsArr = newComplaint;
    RespondingToCustomerComplaints(pCompany,&pCompany->complaintsArr[pCompany->numOfCompliants], userChannel);
    pCompany->numOfCompliants++;
    return 1;
}

Channel* channelNumberExist(int channelNum, Channel* channelArr, int numOfChannels)
{
    for (int i = 0; i < numOfChannels; i++)
    {
        if (channelArr[i].ChannelNum == channelNum)
            return &channelArr[i];
    }
    return NULL;
}

Viewer* viewerNumberExist(int numOfAccount, Viewer** viewerArr, int numOfViewers)
{
    for (int i = 0; i < numOfViewers; i++)
    {
        if (viewerArr[i]->person.id == numOfAccount)
            return viewerArr[i];
    }
    return NULL;
}

int isComplaintAccepted(TvCompany* pCompany, Complaints* cpmplaintArr, Channel* userChannel)
{
    if (userChannel == NULL)
    {
        printf("No such channel.\n");
        return 0;
    }
    int numOfComplaintType = cpmplaintArr[pCompany->numOfCompliants].type;
    if (!(userChannel->CommercialArr) && numOfComplaintType == 0)
    {
        printf("No commercials have been added to the system yet.");
        return 0;
    }
    else if (!(userChannel->showsList.head.next) && (numOfComplaintType == 1 || numOfComplaintType == 2))
    {
        printf("No shows have been added to the system yet.");
        return 0;
    }
    else if (!(pCompany->channelArr))
    {
        printf("No channels have been added to the system yet.");
        return 0;
    }
    return 1;
}

int RespondingToCustomerComplaints(TvCompany* pCompany, Complaints* pComp, Channel* userChannel)
{
    switch (pComp->type)
    {
        case 0:
        {
            for (int i = 0; i < userChannel->numOfCommercial; i++)
            {
                printCommercial(&userChannel->CommercialArr[i]);
                printf("\n");
            }
            char* commercialUserChoice = getStrExactName("Please enter the name of the commercial\n");
            Commercial* commercial = commercialNameExist(commercialUserChoice, userChannel->CommercialArr, userChannel->numOfCommercial);
            if (!commercial)
            {
                printf("No such commercial in this channel.\n");
                return 0;
            }
            if (commercial->commercialLengthInSeconds >= 10)
            {
                commercial->commercialLengthInSeconds = DIVIDING(commercial->commercialLengthInSeconds);// MACRO
                printf("The length of the commercial is shortened at your request. Enjoy watching!\n");
            }
            else
                printf("The length of the selected commercial cannot be shortened!(Because the length of the advertisement is short already)\n");
        }
            break;

        case 1:
        {
            int numShows = L_print(&(userChannel->showsList), printShow);
            char* showUserChoice = getStrExactName("Please enter the name of the show\n");
            Show* show = findShowByName(userChannel, showUserChoice);
            if (!show)
            {
                printf("No such show in this channel.\n");
                return 0;
            }
            if (show->subtitles == 0)
            {
                show->subtitles = 1;
                printf("At your request we have added subtitles in the selected show.\n");
            }
            else
                printf("The selected show already has subtitles.\n");
        }
            break;

        case 2:
        {
            for (int i = 0; i < userChannel->numOfCommercial; i++)
            {
                printCommercial(&userChannel->CommercialArr[i]);
                printf("\n");
            }
            char* commercialUserChoice = getStrExactName("Please enter the name of the commercial\n");
            Commercial* commercial = commercialNameExist(commercialUserChoice, userChannel->CommercialArr, userChannel->numOfCommercial);
            if (!commercial)
            {
                printf("No such commercial in this channel.\n");
                return 0;
            }
            if (deleteCommercial(userChannel->CommercialArr, &userChannel->numOfCommercial, commercialUserChoice))
            {
                printf("The show has been deleted at your request.\n");

            }

            for (int i = 0; i < userChannel->numOfCommercial; i++)
            {
                printCommercial(&userChannel->CommercialArr[i]);
                printf("\n");
            }
        }
            break;

        default:
            printf("Error!");
            break;
    }
}

void sortViewer(TvCompany* pCompany)
{
    if (pCompany->numOfViewers > 1)
    {
        int option;
        printf("Base on what field do you want to sort?\n");
        printf("Enter %d for viewer name\n", eViewerName);
        printf("Enter %d for start date\n", eStartDate);
        printf("Enter %d for end date \n", eEndDate);
        scanf("%d", &option);

        pCompany->sortType = (eSortType)option;

        switch (pCompany->sortType)
        {
            case eViewerName:
                qsort(pCompany->viewerArr, pCompany->numOfViewers, sizeof(Viewer*), compareContractByContractNum);
                break;
            case eStartDate:
                qsort(pCompany->viewerArr, pCompany->numOfViewers, sizeof(Viewer*), compareContractByStartDate);
                break;
            case eEndDate:
                qsort(pCompany->viewerArr, pCompany->numOfViewers, sizeof(Viewer*), compareContractByEndDate);
                break;
            default:
                return;
        }
    }
    else
    {
        printf("There are no viewers in the company that can be sorted.\n");
    }
}

void findViewer(const TvCompany* pCompany)
{
    Viewer* searchKey;
    Viewer** result;
    searchKey = malloc(sizeof(Viewer));

    if (pCompany->sortType == 0)
    {
        printf("The search cannot be performed, array not sorted.\n");
        return;
    }
    if (pCompany->sortType == 1)
    {
        printf("Viewer name: ");
        personName(&searchKey->person);
        result = bsearch(&searchKey, pCompany->viewerArr, pCompany->numOfViewers, sizeof(Viewer*), compareContractByContractNum);
    }
    else if (pCompany->sortType == 2)
    {
        printf("Start date: ");
        getCorrectDate(&searchKey->contract.contStartDate);
        result = bsearch(&searchKey, pCompany->viewerArr, pCompany->numOfViewers, sizeof(Viewer*), compareContractByStartDate);
    }
    else
    {
        printf("End date: ");
        getCorrectDate(&searchKey->contract.contEndDate);
        result = bsearch(&searchKey, pCompany->viewerArr, pCompany->numOfViewers, sizeof(Viewer*), compareContractByEndDate);
    }

    if (result != NULL)
    {
        printf("Viewer found!\n");
        printViewer(*result);
    }
    else
        printf("Viewer was not found\n");

    free(searchKey);
}

int compareContractByContractNum(const void* viewer1, const void* viewer2)
{
    const Viewer* v1 = *(const Viewer**)viewer1;
    const Viewer* v2 = *(const Viewer**)viewer2;

    return strcmp(v1->person.name, v2->person.name);
}

int compareContractByEndDate(const void* viewer1, const void* viewer2)
{
    const Viewer* v1 = *(const Viewer**)viewer1;
    const Viewer* v2 = *(const Viewer**)viewer2;

    if (v1->contract.contEndDate.year < v2->contract.contEndDate.year)
        return -1;
    else if (v1->contract.contEndDate.year > v2->contract.contEndDate.year)
        return 1;
    else
        return 0;
}

void printAllAdultViewers(const TvCompany* pCompany)
{

    for (int i = 0; i < pCompany->numOfViewers; i++)
    {
        if (pCompany->viewerArr[i]->person.age >= ADULT_VIEWER)
            printViewer(pCompany->viewerArr[i]);
    }
}

void printAllCommercialsSameType(const TvCompany* pCompany)
{
    int counterOfCommercialsArr = 0;
    if (!pCompany->channelArr)
    {
        printf("There are currently no channels in the company.\n");
        return;
    }

    for (int i = 0; i < pCompany->numOfChannels; i++)
    {
        if (pCompany->channelArr[i].CommercialArr)
        {
            counterOfCommercialsArr++;
        }
    }


    if (counterOfCommercialsArr > 0)
    {
        int counter = 0;
        Commercial commercial;
        int commercialType = getCommercialType(&commercial);

        for (int i = 0; i < pCompany->numOfChannels; i++)
        {
            for (int j = 0; j < pCompany->channelArr[i].numOfCommercial; j++)
            {
                if (commercialType == pCompany->channelArr[i].CommercialArr[j].type)
                {
                    printCommercial(&pCompany->channelArr[i].CommercialArr[j]);
                    counter++;
                }
            }
        }
        if (counter == 0)
            printf("No commercials with the chosen type.\n");
    }
    else {
        printf("There are currently no commercials in the company.\n");
    }
}

void printTvCompany(const TvCompany* pCompany)
{
    if (pCompany->channelArr)
    {
        printf("\nTv company name: %s\n", pCompany->companyName);
        printf("These are all the channels in the company.\n");
        for (int i = 0; i < pCompany->numOfChannels; i++)
        {
            PRINT_SEPARATOR_LINE();
            printChannel(&pCompany->channelArr[i]);
        }
        PRINT_SEPARATOR_LINE();

    }
    else {
        printf("There are currently no channels to show.\n");
    }
}


void freeCompany(TvCompany* company)
{
    //free viewer
    for (int i = 0; i < company->numOfViewers; i++)
    {
        freeViewer(company->viewerArr[i]);
        free(company->viewerArr[i]);
    }
    free(company->viewerArr);

    //free employee
    for (int i = 0; i < company->numOfEmployees; i++)
        free(company->employeeArr[i]);
    free(company->employeeArr);

    //free channel
    for (int i = 0; i < company->numOfChannels; i++)
        freeChannel(&company->channelArr[i]);
    free(company->channelArr);

    //free cpmplaint
    for (int i = 0; i < company->numOfCompliants; i++)
        freeComplaints(&company->complaintsArr[i]);
    free(company->complaintsArr);

}

int compareContractByStartDate(const void* viewer1, const void* viewer2)
{
    const Viewer* v1 = *(const Viewer**)viewer1;
    const Viewer* v2 = *(const Viewer**)viewer2;

    return (v1->contract.contStartDate.year != v2->contract.contStartDate.year) ? v1->contract.contStartDate.year - v2->contract.contStartDate.year :
           (v1->contract.contStartDate.month != v2->contract.contStartDate.month) ? v1->contract.contStartDate.month - v2->contract.contStartDate.month :
           v1->contract.contStartDate.day - v2->contract.contStartDate.day;
}
