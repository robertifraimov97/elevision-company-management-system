//
// Created by Robert Ifraimov on 25/08/2024.
//

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

//void writeCompanyToFile(const TvCompany* company, const char* filename)
//{
//    FILE* file = fopen(filename, "w");
//    if (file == NULL) {
//        printf("Error opening file for writing.\n");
//        return;
//    }
//
//    int nameLength = strlen(company->companyName) + 1;
//    fprintf(file, "%d\n", nameLength);// Write the length of the name
//    fprintf(file, "%s\n", company->companyName);// Write the name
//
//    // Write viewers
//    fprintf(file, "%d\n", company->numOfViewers); // print num of viewers
//    for (int i = 0; i < company->numOfViewers; i++)
//    {
//        printViewerToFile(company->viewerArr[i], file);
//    }
//
//    // Write employees
//    fprintf(file, "%d\n", company->numOfEmployees);// print num of employees
//    for (int i = 0; i < company->numOfEmployees; i++)
//    {
//        printEmployeeToFile(company->employeeArr[i], file);
//    }
//
//    // Write channels
//    fprintf(file, "%d\n", company->numOfChannels);
//    for (int i = 0; i < company->numOfChannels; i++)
//    {
//        printChannelToFile(&company->channelArr[i], file);
//    }
//
//    // Write complaints
//    fprintf(file, "%d\n", company->numOfCompliants);
//    for (int i = 0; i < company->numOfCompliants; i++)
//    {
//        printComplaintToFile(&company->complaintsArr[i], file);
//    }
//
//    fclose(file);
//}

//void printViewerToFile(const Viewer* pViewer, FILE* file)
//{
//    fprintf(file, "%s\n", pViewer->person.name);//print name
//    fprintf(file, "%d\n", pViewer->person.age);//print age
//    fprintf(file, "%d\n", pViewer->person.id);//print id
//    fprintf(file, "%d\n", pViewer->contract.contractNumber);//print contract number
//    fprintf(file, "%d/%d/%d\n", pViewer->contract.contStartDate.day,
//            pViewer->contract.contStartDate.month, pViewer->contract.contStartDate.year);//print contract start date
//    fprintf(file, "%d/%d/%d\n", pViewer->contract.contEndDate.day,
//            pViewer->contract.contEndDate.month, pViewer->contract.contEndDate.year);//print contract end date
//    fprintf(file, "%d\n", pViewer->contract.type);//print contract type
//}
//
//void printEmployeeToFile(const Employee* pEmployee, FILE* file)
//{
//    fprintf(file, "%s\n", pEmployee->person.name);//print name
//    fprintf(file, "%d\n", pEmployee->person.age);//print age
//    fprintf(file, "%d\n", pEmployee->person.id);//print id
//    fprintf(file, "%d\n", pEmployee->contract.contractNumber);//print contract number
//    fprintf(file, "%d/%d/%d\n", pEmployee->contract.contStartDate.day,
//            pEmployee->contract.contStartDate.month, pEmployee->contract.contStartDate.year);//print contract start date
//    fprintf(file, "%d/%d/%d\n", pEmployee->contract.contEndDate.day,
//            pEmployee->contract.contEndDate.month, pEmployee->contract.contEndDate.year);//print contract end date
//    fprintf(file, "%d\n", pEmployee->contract.type);//print contract type
//}
//
//void printChannelToFile(const Channel* pChannel, FILE* file)
//{
//    fprintf(file, "%d\n", pChannel->ChannelNum);//print channel number
//    fprintf(file, "%d\n", pChannel->type);//print channel type
//    int numOfShows = pChannel->showsList.head.next ? L_print(&(pChannel->showsList), printShow) : 0;
//    fprintf(file, "%d\n", numOfShows);
//
//    L_printToFile(&(pChannel->showsList), printShowToFile, file);
//
//    fprintf(file, "%d\n", pChannel->numOfCommercial);//print number of commercials
//    for (int i = 0; i < pChannel->numOfCommercial; i++)
//    {
//        int nameLength = strlen(pChannel->CommercialArr[i].commercialName) + 1;
//        fprintf(file, "%d\n", nameLength);// Write the length of the name of the commercial
//        fprintf(file, "%s\n", pChannel->CommercialArr[i].commercialName);//print commercial name
//        fprintf(file, "%d\n", pChannel->CommercialArr[i].commercialLengthInSeconds);//print commercial length
//        fprintf(file, "%d\n", pChannel->CommercialArr[i].type);//print commercial type
//    }
//}
//
//void printComplaintToFile(const Complaints* pComplaint, FILE* file) {
//    fprintf(file, "%d\n", pComplaint->type);//print complaint type
//    fprintf(file, "%d/%d/%d\n", pComplaint->date.day, pComplaint->date.month, pComplaint->date.year);//print complaint date
//
//    fprintf(file, "%s\n", pComplaint->viewer.person.name);//print name
//    fprintf(file, "%d\n", pComplaint->viewer.person.id);//print id
//    fprintf(file, "%d\n", pComplaint->viewer.person.age);//print age
//}
//
//TvCompany readCompanyFromFile(const char* filename)
//{
//    FILE* file = fopen(filename, "r");
//    if (file == NULL) {
//        printf("Error opening file for reading.\n");
//        TvCompany emptyCompany;
//        memset(&emptyCompany, 0, sizeof(TvCompany)); // Initialize empty company
//        return emptyCompany; // Return an empty TvCompany struct
//    }
//
//    // Read company name
//    int nameLength;
//    fscanf(file, "%d", &nameLength);
//    char* companyName = (char*)malloc(nameLength * sizeof(char));
//    fscanf(file, "%s", companyName);
//
//    // Read viewers
//    int numOfViewers;
//    fscanf(file, "%d", &numOfViewers);
//    Viewer** viewerArr = (Viewer**)malloc(numOfViewers * sizeof(Viewer*));
//    if (viewerArr == NULL)
//    {
//        printf("Memory allocation failed\n");
//        exit(1);
//    }
//    for (int i = 0; i < numOfViewers; i++)
//        viewerArr[i] = readViewerFromFile(file);
//
//    // Read employees
//    int numOfEmployees;
//    fscanf(file, "%d", &numOfEmployees);
//    Employee** employeeArr = (Employee**)malloc(numOfEmployees * sizeof(Employee*));
//    if (employeeArr == NULL)
//    {
//        printf("Memory allocation failed\n");
//        exit(1);
//    }
//    for (int i = 0; i < numOfEmployees; i++)
//        employeeArr[i] = readEmployeeFromFile(file);
//
//    // Read channels
//    int numOfChannels;
//    fscanf(file, "%d", &numOfChannels);
//    Channel* channelArr = (Channel*)malloc(numOfChannels * sizeof(Channel));
//    for (int i = 0; i < numOfChannels; i++) {
//        channelArr[i] = readChannelFromFile(file);
//    }
//
//    // Read complaints
//    int numOfComplaints;
//    fscanf(file, "%d", &numOfComplaints);
//    Complaints* complaintsArr = (Complaints*)malloc(numOfComplaints * sizeof(Complaints));
//    for (int i = 0; i < numOfComplaints; i++) {
//        complaintsArr[i] = readComplaintFromFile(file);
//    }
//
//    fclose(file);
//
//    // Construct and return the TvCompany structure
//    TvCompany company;
//    company.companyName = companyName;
//    company.numOfViewers = numOfViewers;
//    company.viewerArr = viewerArr;
//    company.numOfEmployees = numOfEmployees;
//    company.employeeArr = employeeArr;
//    company.numOfChannels = numOfChannels;
//    company.channelArr = channelArr;
//    company.numOfCompliants = numOfComplaints;
//    company.complaintsArr = complaintsArr;
//
//    return company;
//}
//
//Viewer* readViewerFromFile(FILE* file)
//{
//    Viewer* viewer = (Viewer*)malloc(sizeof(Viewer)); // Allocate memory for viewer
//    if (viewer == NULL)
//    {
//        printf("Memory allocation error.\n");
//        return NULL; // Return NULL to indicate failure
//    }
//
//    increaseId(&viewer->person);
//    increaseContractNumber(&viewer->contract);
//
//    fscanf(file, "%s", viewer->person.name); //read name
//    fscanf(file, "%d", &viewer->person.age); // Read age
//    fscanf(file, "%d", &viewer->person.id); // Read ID
//    fscanf(file, "%d", &viewer->contract.contractNumber); // Read contract number
//    fscanf(file, "%d/%d/%d", &viewer->contract.contStartDate.day,
//           &viewer->contract.contStartDate.month, &viewer->contract.contStartDate.year); // Read contract start date
//    fscanf(file, "%d/%d/%d", &viewer->contract.contEndDate.day,
//           &viewer->contract.contEndDate.month, &viewer->contract.contEndDate.year); // Read contract end date
//    fscanf(file, "%d", &viewer->contract.type); // Read contract type
//
//
//    viewer->channelArr = NULL;
//    viewer->numOfChannelArr = 0;
//
//    return viewer;
//}
//
//Employee* readEmployeeFromFile(FILE* file)
//{
//    Employee* employee = (Employee*)malloc(sizeof(Employee));
//    if (employee == NULL)
//    {
//        printf("Memory allocation error.\n");
//        return NULL; // Return NULL to indicate failure
//    }
//
//    increaseId(&employee->person);
//    increaseContractNumber(&employee->contract);
//
//    fscanf(file, "%s", employee->person.name); // Read name
//    fscanf(file, "%d", &employee->person.age); // Read age
//    fscanf(file, "%d", &employee->person.id); // Read ID
//    fscanf(file, "%d", &employee->contract.contractNumber); // Read contract number
//    fscanf(file, "%d/%d/%d", &employee->contract.contStartDate.day,
//           &employee->contract.contStartDate.month, &employee->contract.contStartDate.year); // Read contract start date
//    fscanf(file, "%d/%d/%d", &employee->contract.contEndDate.day,
//           &employee->contract.contEndDate.month, &employee->contract.contEndDate.year); // Read contract end date
//    fscanf(file, "%d", &employee->contract.type); // Read contract type
//
//    return employee;
//}
//
//Channel readChannelFromFile(FILE* file)
//{
//    Channel channel;
//
//    // Read channel number and type
//    fscanf(file, "%d", &channel.ChannelNum);
//    fscanf(file, "%d", &channel.type);
//
//    // Read number of shows
//    int numOfShows;
//    fscanf(file, "%d", &numOfShows);
//
//    // Initialize shows list
//    L_init(&(channel.showsList));
//
//    // Read shows
//    for (int i = 0; i < numOfShows; i++)
//    {
//        Show* show = readShowFromFile(file);
//        L_insert(&(channel.showsList.head), show);
//    }
//
//    // Read number of commercials
//    fscanf(file, "%d", &channel.numOfCommercial);
//    if (channel.numOfCommercial == 0)
//        channel.CommercialArr = NULL;
//    else
//    {
//        // Allocate memory for CommercialArr
//        channel.CommercialArr = (Commercial*)malloc(channel.numOfCommercial * sizeof(Commercial));
//
//        // Read each commercial
//        for (int i = 0; i < channel.numOfCommercial; i++)
//        {
//            channel.CommercialArr[i] = readCommercialFromFile(file);
//        }
//    }
//
//    return channel;
//}
//
//
//
//
//
//Complaints readComplaintFromFile(FILE* file)
//{
//    Complaints complaint;
//
//    fscanf(file, "%d", &complaint.type);
//    fscanf(file, "%d/%d/%d", &complaint.date.day, &complaint.date.month, &complaint.date.year);
//    fscanf(file, "%s", complaint.viewer.person.name);
//    fscanf(file, "%d", &complaint.viewer.person.id);
//    fscanf(file, "%d", &complaint.viewer.person.age);
//
//    complaint.viewer.channelArr = NULL;
//    complaint.viewer.numOfChannelArr = 0;
//
//    return complaint;
//}
//
//Show* readShowFromFile(FILE* file)
//{
//    Show* show = (Show*)malloc(sizeof(Show));
//    if (show == NULL)
//    {
//        printf("Memory allocation failed\n");
//        return NULL;
//    }
//    // Read the show name
//    fscanf(file, "%s", show->showName);
//    fscanf(file, "%s", show->broadcastDay);
//    show->startTime = readTimeFromFile(file);
//    show->endTime = readTimeFromFile(file);
//    fscanf(file, "%d", &show->showLengthInMinutes);
//    fscanf(file, "%d", &show->subtitles);
//
//    return show;
//}
//
//
//
//
//
//
//
//
//Commercial readCommercialFromFile(FILE* file)
//{
//    Commercial commercial;
//
//    int nameLength;
//    fscanf(file, "%d", &nameLength);
//
//    // Allocate memory for the commercial name
//    commercial.commercialName = (char*)malloc(nameLength * sizeof(char));
//
//    // Read the commercial name
//    fscanf(file, "%s", commercial.commercialName);
//
//    // Read the commercial length in seconds
//    fscanf(file, "%d", &commercial.commercialLengthInSeconds);
//
//    // Read the commercial type
//    fscanf(file, "%d", &commercial.type);
//
//    return commercial;
//}
//
//Time readTimeFromFile(FILE* file)
//{
//    Time time;
//    fscanf(file, "%d:%d:%d", &time.hours, &time.minutes, &time.seconds);
//    return time;
//}
//
//void writeCompanyToBinaryFile(const TvCompany* company, const char* filename)
//{
//    FILE* file = fopen(filename, "wb"); // Open file in binary write mode
//    if (file == NULL) {
//        printf("Error opening file for writing.\n");
//        return;
//    }
//
//    // Write company name length and name
//    int nameLength = strlen(company->companyName) + 1;
//    fwrite(&nameLength, sizeof(int), 1, file);
//    fwrite(company->companyName, sizeof(char), nameLength, file);
//
//    // Write number of viewers and viewers
//    fwrite(&company->numOfViewers, sizeof(int), 1, file);
//    for (int i = 0; i < company->numOfViewers; i++) {
//        writeViewerToBinaryFile(company->viewerArr[i], file);
//    }
//
//    // Write number of employees and employees
//    fwrite(&company->numOfEmployees, sizeof(int), 1, file);
//    for (int i = 0; i < company->numOfEmployees; i++) {
//        writeEmployeeToBinaryFile(company->employeeArr[i], file);
//    }
//
//    // Write number of channels and channels
//    fwrite(&company->numOfChannels, sizeof(int), 1, file);
//    for (int i = 0; i < company->numOfChannels; i++) {
//        writeChannelToBinaryFile(&company->channelArr[i], file);
//    }
//
//    // Write number of complaints and complaints
//    fwrite(&company->numOfCompliants, sizeof(int), 1, file);
//    fwrite(company->complaintsArr, sizeof(Complaints), company->numOfCompliants, file);
//
//    fclose(file);
//}
//
//void writeViewerToBinaryFile(const Viewer* pViewer, FILE* file)
//{
//    int lengthOfViewerName = strlen(pViewer->person.name);
//    fwrite(&lengthOfViewerName, sizeof(int), 1, file);
//    fwrite(pViewer->person.name, sizeof(char), lengthOfViewerName, file); // Write name
//
//    fwrite(&pViewer->person.age, sizeof(int), 1, file); // Write age
//    fwrite(&pViewer->person.id, sizeof(int), 1, file); // Write ID
//    fwrite(&pViewer->contract.contractNumber, sizeof(int), 1, file); // Write contract number
//    fwrite(&pViewer->contract.contStartDate, sizeof(Date), 1, file); // Write contract start date
//    fwrite(&pViewer->contract.contEndDate, sizeof(Date), 1, file); // Write contract end date
//    fwrite(&pViewer->contract.type, sizeof(int), 1, file); // Write contract type
//}

//void writeEmployeeToBinaryFile(const Employee* pEmployee, FILE* file)
//{
//    int lengthOfEmployeeName = strlen(pEmployee->person.name);
//    fwrite(&lengthOfEmployeeName, sizeof(int), 1, file);
//    fwrite(pEmployee->person.name, sizeof(char), lengthOfEmployeeName, file); // Write name
//
//    fwrite(&pEmployee->person.age, sizeof(int), 1, file); // Write age
//    fwrite(&pEmployee->person.id, sizeof(int), 1, file); // Write ID
//    fwrite(&pEmployee->contract.contractNumber, sizeof(int), 1, file); // Write contract number
//    fwrite(&pEmployee->contract.contStartDate, sizeof(Date), 1, file); // Write contract start date
//    fwrite(&pEmployee->contract.contEndDate, sizeof(Date), 1, file); // Write contract end date
//    fwrite(&pEmployee->contract.type, sizeof(int), 1, file); // Write contract type
//
//}


//void writeChannelToBinaryFile(const Channel* channel, FILE* file)
//{
//    // Write channel number
//    fwrite(&channel->ChannelNum, sizeof(int), 1, file);
//
//    // Write channel type
//    fwrite(&channel->type, sizeof(eGenreType), 1, file);
//
//    // Write number of shows
//    int numOfShows = channel->showsList.head.next ? L_print(&(channel->showsList), printShow) : 0;
//    fwrite(&numOfShows, sizeof(int), 1, file);
//
//    // Write shows
//    L_printToFile(&(channel->showsList), writeShowToBinaryFile, file);
//
//    // Write number of commercials
//    fwrite(&channel->numOfCommercial, sizeof(int), 1, file);
//    for (int i = 0; i < channel->numOfCommercial; i++)
//    {
//        // Write length of commercial name and commercial name
//        int nameLength = strlen(channel->CommercialArr[i].commercialName) + 1;
//        fwrite(&nameLength, sizeof(int), 1, file);
//        fwrite(channel->CommercialArr[i].commercialName, sizeof(char), nameLength, file);
//
//        // Write commercial length in seconds and commercial type
//        fwrite(&channel->CommercialArr[i].commercialLengthInSeconds, sizeof(int), 1, file);
//        fwrite(&channel->CommercialArr[i].type, sizeof(eCommercialType), 1, file);
//    }
//}

//TvCompany readCompanyFromBinaryFile(const char* filename)
//{
//    FILE* file = fopen(filename, "rb"); // Open file in binary read mode
//    if (file == NULL) {
//        printf("Error opening file for reading.\n");
//        TvCompany emptyCompany;
//        memset(&emptyCompany, 0, sizeof(TvCompany)); // Initialize empty company
//        return emptyCompany; // Return an empty TvCompany struct
//    }
//
//    // Read company name
//    int nameLength;
//    fread(&nameLength, sizeof(int), 1, file);
//    char* companyName = (char*)malloc(nameLength * sizeof(char));
//    fread(companyName, sizeof(char), nameLength, file);
//
//    // Read number of viewers and viewers
//    int numOfViewers;
//    fread(&numOfViewers, sizeof(int), 1, file);
//    Viewer** viewerArr = (Viewer**)malloc(numOfViewers * sizeof(Viewer*));
//    for (int i = 0; i < numOfViewers; i++) {
//        viewerArr[i] = readViewerFromBinaryFile(file);
//    }
//
//    // Read number of employees and employees
//    int numOfEmployees;
//    fread(&numOfEmployees, sizeof(int), 1, file);
//    Employee** employeeArr = (Employee**)malloc(numOfEmployees * sizeof(Employee*));
//    for (int i = 0; i < numOfEmployees; i++) {
//        employeeArr[i] = readEmployeeFromBinaryFile(file);
//    }
//
//    // Read number of channels and channels
//    int numOfChannels;
//    fread(&numOfChannels, sizeof(int), 1, file);
//    Channel* channelArr = (Channel*)malloc(numOfChannels * sizeof(Channel));
//    for (int i = 0; i < numOfChannels; i++) {
//        channelArr[i] = readChannelFromBinaryFile(file);
//    }
//
//    // Read number of complaints and complaints
//    int numOfComplaints;
//    fread(&numOfComplaints, sizeof(int), 1, file);
//    Complaints* complaintsArr = (Complaints*)malloc(numOfComplaints * sizeof(Complaints));
//    fread(complaintsArr, sizeof(Complaints), numOfComplaints, file);
//
//    complaintsArr->viewer.channelArr = NULL;
//    complaintsArr->viewer.numOfChannelArr = 0;
//
//    fclose(file);
//
//    // Construct and return the TvCompany structure
//    TvCompany company;
//    company.companyName = companyName;
//    company.numOfViewers = numOfViewers;
//    company.viewerArr = viewerArr;
//    company.numOfEmployees = numOfEmployees;
//    company.employeeArr = employeeArr;
//    company.numOfChannels = numOfChannels;
//    company.channelArr = channelArr;
//    company.numOfCompliants = numOfComplaints;
//    company.complaintsArr = complaintsArr;
//
//    return company;
//}

//Viewer* readViewerFromBinaryFile(FILE* file)
//{
//    Viewer* viewer = (Viewer*)malloc(sizeof(Viewer)); // Allocate memory for viewer
//    if (viewer == NULL)
//    {
//        printf("Memory allocation error.\n");
//        return NULL; // Return NULL to indicate failure
//    }
//
//    increaseId(&viewer->person);
//    increaseContractNumber(&viewer->contract);
//
//    int nameLength;
//    fread(&nameLength, sizeof(int), 1, file);
//    fread(viewer->person.name, sizeof(char), nameLength, file);
//    viewer->person.name[nameLength] = '\0';
//
//    fread(&(viewer->person.age), sizeof(int), 1, file);
//    fread(&viewer->person.id, sizeof(int), 1, file);
//    fread(&viewer->contract.contractNumber, sizeof(int), 1, file);
//    fread(&viewer->contract.contStartDate, sizeof(Date), 1, file);
//    fread(&viewer->contract.contEndDate, sizeof(Date), 1, file);
//    fread(&viewer->contract.type, sizeof(eContType), 1, file);
//
//
//    viewer->channelArr = NULL;
//    viewer->numOfChannelArr = 0;
//
//    return viewer;
//}
//
//Employee* readEmployeeFromBinaryFile(FILE* file)
//{
//    Employee* employee = (Employee*)malloc(sizeof(Employee)); // Allocate memory for employee
//    if (employee == NULL)
//    {
//        printf("Memory allocation error.\n");
//        return NULL; // Return NULL to indicate failure
//    }
//
//    increaseId(&employee->person);
//    increaseContractNumber(&employee->contract);
//
//    int nameLength;
//    fread(&nameLength, sizeof(int), 1, file);
//    fread(employee->person.name, sizeof(char), nameLength, file); // Read name
//    employee->person.name[nameLength] = '\0';
//
//    fread(&employee->person.age, sizeof(int), 1, file);
//    fread(&employee->person.id, sizeof(int), 1, file);
//    fread(&employee->contract.contractNumber, sizeof(int), 1, file);
//    fread(&employee->contract.contStartDate, sizeof(Date), 1, file);
//    fread(&employee->contract.contEndDate, sizeof(Date), 1, file);
//    fread(&employee->contract.type, sizeof(eContType), 1, file);
//
//    return employee;
//}

//Channel readChannelFromBinaryFile(FILE* file)
//{
//    Channel channel;
//
//    // Read channel number and type
//    fread(&channel.ChannelNum, sizeof(int), 1, file);
//    fread(&channel.type, sizeof(eGenreType), 1, file);
//
//    // Read number of shows
//    int numOfShows;
//    fread(&numOfShows, sizeof(int), 1, file);
//
//    // Initialize shows list
//    L_init(&(channel.showsList));
//
//    // Read shows
//    for (int i = 0; i < numOfShows; i++)
//    {
//        Show* show = readShowFromBinaryFile(file);
//        L_insert(&(channel.showsList.head), show);
//    }
//
//    // Read number of commercials
//    fread(&channel.numOfCommercial, sizeof(int), 1, file);
//    if (channel.numOfCommercial == 0)
//        channel.CommercialArr = NULL;
//    else
//    {
//        // Allocate memory for CommercialArr
//        channel.CommercialArr = (Commercial*)malloc(channel.numOfCommercial * sizeof(Commercial));
//
//        // Read each commercial
//        for (int i = 0; i < channel.numOfCommercial; i++)
//        {
//            int nameLength;
//            fread(&nameLength, sizeof(int), 1, file);
//            channel.CommercialArr[i].commercialName = malloc(nameLength * sizeof(char));
//            fread(channel.CommercialArr[i].commercialName, sizeof(char), nameLength, file);
//
//            fread(&channel.CommercialArr[i].commercialLengthInSeconds, sizeof(int), 1, file);
//            fread(&channel.CommercialArr[i].type, sizeof(eCommercialType), 1, file);
//        }
//    }
//
//    return channel;
//}

//Show* readShowFromBinaryFile(FILE* file)
//{
//    Show* show = (Show*)malloc(sizeof(Show)); // Allocate memory for show
//    if (show == NULL)
//    {
//        printf("Memory allocation failed\n");
//        return NULL;
//    }


    // Read the show name
//    int showLength;
//    fread(&showLength, sizeof(int), 1, file);
//    fread(show->showName, sizeof(char), showLength, file); // Read name
//    show->showName[showLength] = '\0';
//
//    // Read the broadcast day
//    int broadcastDayLength;
//    fread(&broadcastDayLength, sizeof(int), 1, file);
//    fread(show->broadcastDay, sizeof(char), broadcastDayLength, file); // Read broadcast day
//    show->broadcastDay[broadcastDayLength] = '\0';
//
//    // Read start and end time
//    fread(&show->startTime, sizeof(Time), 1, file);
//    fread(&show->endTime, sizeof(Time), 1, file);
//
//    // Read show length in minutes and subtitles
//    fread(&show->showLengthInMinutes, sizeof(int), 1, file);
//    fread(&show->subtitles, sizeof(int), 1, file);
//
//    return show;
//}

//void freeCompany(TvCompany* company)
//{
//    //free viewer
//    for (int i = 0; i < company->numOfViewers; i++)
//    {
//        freeViewer(company->viewerArr[i]);
//        free(company->viewerArr[i]);
//    }
//    free(company->viewerArr);
//
//    //free employee
//    for (int i = 0; i < company->numOfEmployees; i++)
//        free(company->employeeArr[i]);
//    free(company->employeeArr);
//
//    //free channel
//    for (int i = 0; i < company->numOfChannels; i++)
//        freeChannel(&company->channelArr[i]);
//    free(company->channelArr);
//
//    //free cpmplaint
//    for (int i = 0; i < company->numOfCompliants; i++)
//        freeComplaints(&company->complaintsArr[i]);
//    free(company->complaintsArr);
//
//}




int compareContractByStartDate(const void* viewer1, const void* viewer2)
{
    const Viewer* v1 = *(const Viewer**)viewer1;
    const Viewer* v2 = *(const Viewer**)viewer2;

    return (v1->contract.contStartDate.year != v2->contract.contStartDate.year) ? v1->contract.contStartDate.year - v2->contract.contStartDate.year :
           (v1->contract.contStartDate.month != v2->contract.contStartDate.month) ? v1->contract.contStartDate.month - v2->contract.contStartDate.month :
           v1->contract.contStartDate.day - v2->contract.contStartDate.day;
}



