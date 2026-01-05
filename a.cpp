#define P_OK 0
#define P_ERR -5

#define STR_SIZE 100

#include <stdio.h>
#include <time.h>

char str01[STR_SIZE];

int time_meter()
{

    char buff[STR_SIZE];

    time_t tm01;
    time_t tm02;

    struct tm *ctm01;
    struct tm ctm02;

    tm01=time(NULL);
    ctm01=localtime(&tm01);

    printf("%i/%i/%i - %i:%i:%i\n", (ctm01->tm_mon)+1, ctm01->tm_mday, (ctm01->tm_year)+1900, ctm01->tm_hour, ctm01->tm_min, ctm01->tm_sec);

    printf("UNIX Time: %ld\n", tm01);



    return P_OK;

};



int main(int argc, char* argv[])
{

    time_meter();



    return 0;

}