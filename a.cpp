/*
 * Time Meter Program
 * Measures elapsed time from a given date to the current date
 * Input: Date in MMDDYYYY format
 * Output: Elapsed time in years, months, and days
 */


// ------------------------------------
// ************************************
// preprocessor declaration
// ************************************
// ------------------------------------

#define P_OK 0
#define P_ERR_RANGE -5
#define P_ERR_VAL -10

#define STR_SIZE 100

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// ----------------------------------------
// ****************************************
// Functions & Object Declaration
// ****************************************
// ----------------------------------------


// ---------------------------------
// caldate structure
// ----------------------------------
struct caldate
{
    int month;
    int day;
    int year;

    int status;
};


// ----------------------------------
// function caldate
// ----------------------------------
struct caldate compute_elapsed(time_t time1, time_t time2)
{
    //  -----------------------------------
    // variables and object declaration
    struct caldate elapsed;
    elapsed.month = 0;
    elapsed.day = 0;
    elapsed.year = 0;
    elapsed.status = P_OK;
    
    // ----------------------------------
    // function body


    if (time1 < 0 || time2 < 0) {
        elapsed.status = P_ERR_VAL;
        return elapsed;
    }
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
    
    // return the result
    return elapsed;
};


// ---------------------------------------------------
// function validate_day_range
// ---------------------------------------------------
int validate_day_range(int month, int day, int year)
{
    // ---------------------------------
    // variable and data declaration
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // ---------------------------------
    // function body

    if (year < 1500 || year > 5000) return P_ERR_RANGE;
    if (month < 1 || month > 12) return P_ERR_RANGE;
    
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        days_in_month[1] = 29;
    
    return (day >= 1 && day <= days_in_month[month - 1]) ? P_OK : P_ERR_RANGE;
};


// ---------------------------------------------------
// function calinit
// --------------------------------------------------
struct caldate calinit(char str01[STR_SIZE])
{

    // ----------------------------------------------
    // variable declaration
    struct caldate calprocess;

    int res;
    int x;
    int count;

    char str_month[10];
    char str_day[10];
    char str_year[10];

    
    // ----------------------------------------------
    // function body

    memset(str_month, 0, sizeof(str_month));
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

// ---------------------------------------------------------
// funcction time_meter
// ---------------------------------------------------------
struct caldate time_meter(struct caldate calinquire)
{

    // ----------------------------------
    // variable declaration
    char buff[STR_SIZE];

    time_t tm01;
    time_t tm02;

    struct tm *ctm01;
    struct tm *ctm02;

    // ----------------------------------
    // function body

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


// ---------------------------------------------
// *********************************************
// Program Entry Point
// *********************************************
// ---------------------------------------------
int main(int argc, char* argv[])
{
    
    // ----------------------------------------
    // variable and object declaration
    int res;
    struct caldate caldate;
    struct caldate calresult;

    char str01[STR_SIZE];

    
    // ------------------------------------------
    // Actual program function


    printf("\n");
    printf("-------------------------------\n");
    printf("Elapsed Date Calculator Program\n");
    printf("-------------------------------\n\n");
    printf("Enter the Date values: MMDDYYYY\n");
    scanf("%s", &str01);

    printf("\n");

    caldate=calinit(str01);

    if( caldate.status == P_OK )
    {
        calresult=time_meter(caldate);

        if(calresult.status == P_OK)
        {
            printf("Elapsed Time: %d Years, %d Months, %d Days\n", calresult.year, calresult.month, calresult.day);
        }else
        {
            printf("Program Error: Inputed date not solvable...\n");
        };
           
        
    }else
    if(caldate.status == P_ERR_RANGE)
    {
        printf("Program Error: Value Out of Range...\n");
        printf("Input in MMDDYYYY. MM<01-12> DD<01-31> YYYY<1500-5000>\n");
    }else
    {
        printf("Program Error: Input not in Integer\n");
    };

    printf("\n");

    return 0;

};
