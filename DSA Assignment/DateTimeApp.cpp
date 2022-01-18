// DateTimeApp.cpp : Converts a string to a time structure (tm) using sscanf_s() function
//

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

int main()
{   // https://www.cplusplus.com/reference/ctime/tm/ for info about time structure (tm)
    tm result;
    char aString[] = "03/04/2020  06:09:02";
    sscanf_s(aString, "%d/%d/%4d  %d:%d:%d",
        &result.tm_mday, &result.tm_mon, &result.tm_year, &result.tm_hour, &result.tm_min, &result.tm_sec);
    printf("tm_hour:  %d\n", result.tm_hour);
    printf("tm_min:  %d\n", result.tm_min);
    printf("tm_sec:  %d\n", result.tm_sec);
    printf("tm_mday:  %d\n", result.tm_mday);
    printf("tm_mon:  %d\n", result.tm_mon);
    printf("tm_year:  %d\n", result.tm_year);
}