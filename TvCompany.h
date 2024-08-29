
#ifndef TVCOMPANY
#define TVCOMPANY
#include "Employee.h"
#include "Channel.h"
#include "Complaints.h"
#include "General.h"
#define ADULT_VIEWER 40
#define DIVIDING(x) ((x) / (2))

typedef enum {
    eNotSorted, eViewerName, eStartDate, eEndDate, eNofSortTypes
} eSortType;

static const char* sortTypeStr[eNofSortTypes]
        = { "Viewer name", "Start date", "End date" };


typedef struct
{
    char* companyName;

    Employee** employeeArr;
    int numOfEmployees;

    Viewer** viewerArr;
    int numOfViewers;

    Channel* channelArr;
    int numOfChannels;

    Complaints* complaintsArr;
    int numOfCompliants;

    eSortType   sortType;
}TvCompany;

void initTvCompany(TvCompany* pCompany);
int addChannelsToViewerByContractType(TvCompany* pCompany, Viewer* pViewer);
int addEmployee(TvCompany* pCompany);
int addViewer(TvCompany* pCompany);
int addChannel(TvCompany* pCompany);
Channel* channelNumberExist(int channelNum, Channel* channelArr, int numOfChannels);
Viewer* viewerNumberExist(int numOfAccount, Viewer** viewerArr, int numOfViewers);
int addComplaint(TvCompany* pCompany);
int isComplaintAccepted(TvCompany* pCompany, Complaints* cpmplaintArr, Channel* userChannel);
int RespondingToCustomerComplaints(TvCompany* pCompany, Complaints* pComp, Channel* userChannel);
void sortViewer(TvCompany* pCompany);
void findViewer(const TvCompany* pCompany);
int compareContractByContractNum(const void* viewer1, const void* viewer2);
int compareContractByStartDate(const void* viewer1, const void* viewer2);
int compareContractByEndDate(const void* viewer1, const void* viewer2);
void printAllAdultViewers(const TvCompany* pCompany);
void printAllCommercialsSameType(const TvCompany* pCompany);
void printTvCompany(const TvCompany* pCompany);

void freeCompany(TvCompany* company);


////////////////////////////const and free
#endif
