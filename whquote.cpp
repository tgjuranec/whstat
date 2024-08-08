#include <iostream>
#include <string>
#include <chrono>

#include "holydays.h"


// TEST IF YEAR IS LEAP YEAR
bool isLeapYear(unsigned long year){
    if(year%4 == 0){
        if((year % 100) == 0){
            if(year % 400 == 0){
                // e.g. 2000, 2400, 1600
                return true;
            }
            else{
                // e.g. 2100, 2200, 1900
                return false;
            }
        }
        // e. g. 2016
        return true;
    }
    //e.g. 2017
    return false;
}

int main(int argc, char **argv){

    if(argc < 3){
        std::cerr << "Arguments not provided!" << std::endl;
        std::cerr << "Usage: whquote 2023 5" << std::endl;
        return 1;
    }
    //convert arguments to strings
    std::string strYear = argv[1];
    std::string strMonth = argv[2];
    if(!isdigit(strYear.at(0)) || !isdigit(strMonth.at(0))){
        std::cerr << "Wrong arguments provided!" << std::endl;
        std::cerr << "Usage: whquote 2023 5" << std::endl;
        return 1;
    }

    unsigned long ulYear = strtoul(strYear.c_str(),nullptr,10);
    unsigned long ulMonth = strtoul(strMonth.c_str(),nullptr,10);
    //check arguments limits
    if(ulYear < 2020l|| ulYear > 2050  || ulMonth < 1l || ulMonth > 12l){
        std::cerr << "Year must be between 2020 and 2050" << std::endl;
        std::cerr << "Month must be between 1 and 12" << std::endl;
        return 1;
    }

    // CHECK SUNDAYS AND SATHURDAYS
    //INITIALIZATION OF THE tm OBJECT FROM int
    std::tm timeinfo = {0, 0, 0, 1, (int)(ulMonth - 1l), (int)(ulYear - 1900ul)}; // Note: month is 0-based
    std::time_t timeinit = std::mktime(&timeinfo);
    timeinfo = *std::localtime(&timeinit);
    std::cout << timeinfo.tm_gmtoff << timeinfo.tm_zone << timeinfo.tm_wday << std::endl;

    unsigned int nSunSat = 0, nHolydays = 0;
    unsigned long nonWorkingDays = 0;                         // sum of hours of nonworking days (8*nonworking days)
    unsigned int monthDays;
    if(isLeapYear(ulYear)){
        monthDays = daysInMonth_leapyear[ulMonth-1u];
    }
    else{
        monthDays = daysInMonth[ulMonth-1u];
    } 
    for (unsigned int i = 0; i < monthDays; i++){
        //CHECK WEEKDAY
        if(timeinfo.tm_wday == 0 || timeinfo.tm_wday == 6){
            nonWorkingDays += 1;
            nSunSat++;
        }
        else{
        //CHECK HOLLYDAY
            unsigned int loopsize = sizeof(holydays_list) / sizeof(holyday);
            for (unsigned int j = 0; j < loopsize; j++){
                if(holydays_list[j].year == 0){
                    if(holydays_list[j].month == ulMonth && holydays_list[j].day == (i+1)){
                        nonWorkingDays += 1;
                        nHolydays++;
                    }

                }
                else if(holydays_list[j].year < ulYear ){
                    continue;
                }
                else if(holydays_list[j].year == ulYear){
                    if(holydays_list[j].month == ulMonth && holydays_list[j].day == (i+1)){
                        nonWorkingDays += 1;
                        nHolydays++;
                    }
                }
                else{
                    break;  
                    //CURRENT YEAR IS SMALLER THAN YEAR IN THE TABLE
                    //SO WE COULDN'T EXPECT MATCH ANYMORE
                }
            }
        }
        //INCREASE std::tm structure
        std::time_t time = std::mktime(&timeinfo);
        time += (24*3600);
        timeinfo = *std::localtime(&time);
    }  
    
    
    std::cout << 8*(monthDays - nonWorkingDays) << ", Sundays&Sathurdays: " << nSunSat 
            << ", Holydays: " << nHolydays << ", Diff: " << 8*nonWorkingDays - 2*monthDays<< std::endl;

    return 0;
}

