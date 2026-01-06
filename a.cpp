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

struct caldate compute_elapsed(time_t time1, time_t time2)
{
    struct caldate elapsed;
    elapsed.month = 0;
    elapsed.day = 0;
    elapsed.year = 0;
    elapsed.status = P_OK;
    
    if (time2 < time1) {
        elapsed.status = P_ERR_VAL;
        return elapsed;
    }
    
    double diff = difftime(time2, time1);
    int days = (int)(diff / 86400);
    
    elapsed.year = days / 365;
    days %= 365;
    elapsed.month = days / 30;
    elapsed.day = days % 30;
    
    return elapsed;
};

int validate_day_range(int month, int day, int year)
{
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month < 1 || month > 12) return P_ERR_RANGE;
    
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        days_in_month[1] = 29;
    
    return (day >= 1 && day <= days_in_month[month - 1]) ? P_OK : P_ERR_RANGE;
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
            (calprocess.year>=1500 && calprocess.year<=5000) &&
            (validate_day_range(calprocess.month, calprocess.day, calprocess.year) == P_OK)
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


struct caldate time_meter(struct caldate calinquire)
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

    ctm02->tm_mon=calinquire.month-1;
    ctm02->tm_mday=calinquire.day;
    ctm02->tm_year=calinquire.year-1900;

    tm02=mktime(ctm02);

    return compute_elapsed(tm02, tm01);


};



int main(int argc, char* argv[])
{
    struct caldate caldate;
    struct caldate calresult;

    char str01[STR_SIZE];

    printf("Enter Cal: MMDDYYYY\n");
    scanf("%s", &str01);

    caldate=calinit(str01);

    if( caldate.status == P_OK )
    {
        calresult=time_meter(caldate);

        printf("Elapsed: %d Years, %d Months, %d Days\n", calresult.year, calresult.month, calresult.day);  
           

        
    }else
    if(caldate.status == P_ERR_RANGE)
    {
        printf("Program Error: Value Out of Range...\n");
        printf("Input in MMDDYYYY. MM<01-12> DD<01-31> YYYY<1500-5000>\n");
    }else
    {
        printf("Program Error: Input not in Integer\n");
    };


    return 0;

}