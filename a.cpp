#define P_OK 0
#define P_ERR_RANGE -5
#define P_ERR_VAL -10

#define STR_SIZE 100

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct caldate
{
    int month;
    int day;
    int year;

    int status;
};


struct caldate calinit(char str01[STR_SIZE])
{

    struct caldate calprocess;

    int res;
    int x;
    int count;

    char str_month[10];
    char str_day[10];
    char str_year[10];

    calprocess.month=0;
    calprocess.day=0;
    calprocess.year=0;
    calprocess.status=0;

    count=0;
    x=0;

    while(str01[x]!='\n' && str01[x]!='\0' && x<8)
    {
        if( !(isdigit(str01[x]) ) )
        {
            count ++;
        };

        x++;
    };

    if(count == 0)
    {
        snprintf(str_month, sizeof(str_month), "%c%c", str01[0], str01[1]);
        snprintf(str_day, sizeof(str_day), "%c%c", str01[2], str01[3]);
        snprintf(str_year, sizeof(str_year), "%c%c%c%c", str01[4], str01[5], str01[6], str01[7]);

        calprocess.month=atoi(str_month);
        calprocess.day=atoi(str_day);
        calprocess.year=atoi(str_year);

        if( 
            (calprocess.month>=1 && calprocess.month<=12) && 
            (calprocess.day>=1 && calprocess.day<=31) && 
            (calprocess.year>=1500 && calprocess.year<=5000)
        )
        {
            res=P_OK;
        }else
        {
            res=P_ERR_RANGE;
        };


    }else
    {
        res=P_ERR_VAL;

    };

    calprocess.status=res;


    return calprocess;

};

int time_meter()
{

    char buff[STR_SIZE];

    time_t tm01;
    time_t tm02;

    struct tm *ctm01;
    struct tm *ctm02;

    tm01=time(NULL);
    ctm01=localtime(&tm01);

    tm02=time(NULL);
    ctm02=localtime(&tm02);

    printf("%i/%i/%i - %i:%i:%i\n", (ctm01->tm_mon)+1, ctm01->tm_mday, (ctm01->tm_year)+1900, ctm01->tm_hour, ctm01->tm_min, ctm01->tm_sec);

    printf("UNIX Time: %ld\n", tm01);



    return P_OK;

};



int main(int argc, char* argv[])
{
    struct caldate caldate;

    char str01[STR_SIZE];

    printf("Enter Cal: MMDDYYYY\n");
    scanf("%s", &str01);

    caldate=calinit(str01);

    if( caldate.status == P_OK )
    {
        printf("Input OK...\n");
        printf("%i - %i - %i\n", caldate.month, caldate.day, caldate.year);
        
    }else
    {
        printf("Program Error...\n");
        printf("%i - %i - %i\n", caldate.month, caldate.day, caldate.year);

    };


    

    return 0;

}