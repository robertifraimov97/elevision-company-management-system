#include <stdio.h>
#include "TvCompany.h"

int addShowTochannelIfExist(TvCompany* company);
int addCommercialToChannelIfExist(TvCompany* company);
void printAllViewers(const TvCompany* company);
void printAllEmployees(const TvCompany* company);

typedef enum
{
    eLoadTvCompanyFromTextFile , eLoadTvCompanyFromBinaryFile, eAddEmployee, eAddViewer, eCreateAChannel, eAddShowToChannel, eAddCommercialToChannel,
    eAddComplaint, eSortViewer, eSearchViewer, ePrintTvCompany, ePrintAllViewers,ePrintAllEmployees,
    ePrintAllAdultsViewers, ePrintAllCommercialsSameType, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = {"Load TvCompany From Text File", "Load TvCompany From Binary File", "Add Employee","Add Viewer","Create a Channel",
                                "Add show to channel", "Add commercial to channel", "Add complaint", "Sort viewer",
                                "Find viewer", "Print Tv company", "Print all viewers","Print all employees",
                                "Print all adults viewers", "Print all commercial with the same type"};

#define EXIT -1
int menu();


int main()
{
    TvCompany company;
    company.companyName = NULL;

    int option;
    int stop = 0;

    do
    {
        option = menu();

        if (option > 1 && option <= 14 && !(company.companyName))
            initTvCompany(&company);

        switch (option)
        {
//            case eLoadTvCompanyFromTextFile:
//                company = readCompanyFromFile("TvCompany.txt");
//                break;
//
//            case eLoadTvCompanyFromBinaryFile:
//                company = readCompanyFromBinaryFile("TvCompany.bin");
//                break;

            case eAddEmployee:
                if (!addEmployee(&company))
                    printf("Error adding employee\n");
                break;

            case eAddViewer:
                if (!addViewer(&company))
                    break;
                break;

            case eCreateAChannel:
                if (!addChannel(&company))
                    printf("Error creating channel\n");
                break;

            case eAddShowToChannel:
                if(!addShowTochannelIfExist(&company))
                    break;
                break;

            case eAddCommercialToChannel:
                if (!addCommercialToChannelIfExist(&company))
                    break;
                break;

            case eAddComplaint:
                if (!addComplaint(&company))
                    break;
                break;

            case eSortViewer:
                sortViewer(&company);
                break;

            case eSearchViewer:
                findViewer(&company);
                break;

            case ePrintTvCompany:
                printTvCompany(&company);
                break;

            case ePrintAllViewers:
                printAllViewers(&company);
                break;

            case ePrintAllEmployees:
                printAllEmployees(&company);
                break;

            case ePrintAllAdultsViewers:
                printAllAdultViewers(&company);
                break;

            case ePrintAllCommercialsSameType:
                printAllCommercialsSameType(&company);
                break;

            case EXIT:
                printf("Bye bye\n");
                stop = 1;
                break;

            default:
                printf("Wrong option\n");
                break;
        }
    } while (!stop);

//    writeCompanyToFile(&company, "TvCompany.txt");
//    writeCompanyToBinaryFile(&company, "TvCompany.bin");

    //freeCompany(&company);
}

int menu()
{
    int option;
    printf("\n\n");
    printf("Please choose one of the following options\n");
    for (int i = 0; i < eNofOptions; i++)
        printf("%2d - %s\n", i, str[i]);
    printf("%d - Quit\n", EXIT);
    scanf("%d", &option);
    //clean buffer
    char tav;
    scanf("%c", &tav);
    return option;
}

int addShowTochannelIfExist(TvCompany* company)
{
    if (!(company->channelArr))
    {
        printf("NO channels in Tvcompany.\n");
        return 0;
    }
    int channelNum1;
    printf("pick a channel number for adding a show:\n");
    if (scanf("%d", &channelNum1) != 1)
    {
        printf("Your answer is not a number.\n");
        while (getchar() != '\n');
        return 0;
    }
    Channel* channel = channelNumberExist(channelNum1, company->channelArr, company->numOfChannels);
    if (channel)
    {
        addShow(channel);
    }
    else {
        printf("Channel not found!.\n");
        return 0;
    }
    return 1;

}

int addCommercialToChannelIfExist(TvCompany* company)
{
    if (!(company->channelArr))
    {
        printf("NO channels in Tvcompany.\n");
        return 0;
    }
    int channelNum2;
    printf("pick a channel number for adding a commercial:\n");
    if (scanf("%d", &channelNum2) != 1)
    {
        printf("Your answer is not a number.\n");
        while (getchar() != '\n');
        return 0;
    }

    Channel* channel2 = channelNumberExist(channelNum2, company->channelArr, company->numOfChannels);
    if (channel2)
    {
        addCommercial(channel2);
    }
    else {
        printf("Channel not found!.\n");
        return 0;
    }
    return 1;
}

void printAllViewers(const TvCompany* company)
{
    for (int i = 0; i < company->numOfViewers; i++)
    {
        printViewer(company->viewerArr[i]);
    }
}

void printAllEmployees(const TvCompany* company)
{
    for (int i = 0; i < company->numOfEmployees; i++)
    {
        printEmployee(company->employeeArr[i]);
    }
}