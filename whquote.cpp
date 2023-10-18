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
    if(!isdigit(strYear.at(0)) || !isdigit(strMonth.at(0))){
        std::cout << "Wrong arguments provided!" << std::endl;
        std::cout << "Usage: whquote 2023 5" << std::endl;
        return 1;
    }

    long iYear = strtol(strYear.c_str(),nullptr,10);
    long iMonth = strtol(strMonth.c_str(),nullptr,10);
    //check arguments correctness
    if(iYear > 2100l || iYear < 2000l){
        return 1;
    }
    if(iMonth < 1l || iMonth > 12l){
        return 1;
    }
    // CHECK SUNDAYS AND SATHURDAYS
    //INITIALIZATION OF THE tm OBJECT FROM int
    std::tm timeinfo = {0, 0, 0, 1, (int)(iMonth - 1l), (int)(iYear - 1900l)}; // Note: month is 0-based
    std::time_t timeinit = std::mktime(&timeinfo);
    timeinfo = *std::localtime(&timeinit);

    unsigned int nSunSat = 0, nHolydays = 0;
    unsigned long nonWorkingDays = 0;                         // sum of hours of nonworking days (8*nonworking days)
    int monthDays = daysInMonth[iMonth-1];
    for (int i = 0; i < monthDays; i++){
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
                    if(holydays_list[j].month == iMonth && holydays_list[j].day == (i+1)){
                        nonWorkingDays += 1;
                        nHolydays++;
                    }

                }
                else if(holydays_list[j].year < iYear ){
                    continue;
                }
                else if(holydays_list[j].year == iYear){
                    if(holydays_list[j].month == iMonth && holydays_list[j].day == (i+1)){
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
    
    
    std::cout << 8*(daysInMonth[iMonth-1] - (int)nonWorkingDays) << ", Sundays&Sathurdays: " << nSunSat 
            << ", Holydays: " << nHolydays << ", Diff: " << 8*nonWorkingDays - 2*daysInMonth[iMonth-1]<< std::endl;

    return 0;
}

