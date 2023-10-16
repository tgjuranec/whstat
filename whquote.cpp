#include <iostream>
#include <string>
#include <chrono>

#include "holydays.h"

int main(int argc, char **argv){

    if(argc < 3){
        std::cout << "Arguments not provided!" << std::endl;
        std::cout << "Usage: whquote 2023 5" << std::endl;
        return 1;
    }
    //convert arguments to strings
    std::string strYear = argv[1];
    std::string strMonth = argv[2];

    int iYear = strtol(strYear.c_str(),nullptr,10);
    int iMonth = strtol(strMonth.c_str(),nullptr,10);
    //check arguments correctness
    if(iYear > 2100 || iYear < 2000){
        return 1;
    }
    if(iMonth < 1 || iMonth > 12){
        return 1;
    }
    // CHECK SUNDAYS AND SATHURDAYS
    //INITIALIZATION OF THE tm OBJECT FROM int
    std::tm timeinfo = {0, 0, 0, 1, (iMonth - 1), iYear - 1900}; // Note: month is 0-based
    

    unsigned long subtractionHours = 0;                         // sum of hours of nonworking days (8*nonworking days)
    int monthDays = daysInMonth[iMonth-1];
    for (int i = 0; i < monthDays; i++){
        if(timeinfo.tm_wday == 0 || timeinfo.tm_wday == 6){
            subtractionHours += 8;
        }
        //INCREASE std::tm structure
        std::time_t time = std::mktime(&timeinfo);
        time += (24*3600);
        timeinfo = *std::localtime(&time);
    }
    
    
    unsigned int loopsize = sizeof(holydays_list) / sizeof(holyday);
    for (unsigned int i = 0; i < loopsize; i++){
        std::cout << i << std::endl;
        
    }
    std::cout << 8*daysInMonth[iMonth-1] - subtractionHours << std::endl;

    return 0;
}

