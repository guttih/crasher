#include "Output.h"
#include <iostream>


Output::Output( const char* applicationName ) : _applicationName( applicationName )
{
}

Output::~Output()
{

}
void Output::help()
{
    std::cout << "Usage  " << std::endl << std::endl;
    std::cout << "  " << _applicationName << "Usage: [options]"  << std::endl << std::endl;
    std::cout << "This application will exit on a given time"  << std::endl;
    std::cout << "The app can also crash on a given time"  << std::endl << std::endl;
    std::cout << "OPTIONS                   Option description" << std::endl;
    std::cout << "  --help,-h,-H            Print usage information and exit." << std::endl;
    std::cout << "  --debug                 Print Debug information." << std::endl;
    std::cout << "  --after,-a <msSeconds>  Crashes after specified number of milliseconds."  << std::endl;
    std::cout << "  --at <time>             Stops at a specified time. Time can be given in the following format." << std::endl << std::endl;
    std::cout << "  --crash <crashType>     On exit make the application crash" << std::endl << std::endl;

    std::cout << "ARGUMENTS    Option argument description" << std::endl;
    std::cout << "  crashType  The available exit errors are:" << std::endl;
    std::cout << "               divZero    Division by zero" << std::endl;
    std::cout << "               segFault   Segment fault" << std::endl;
    std::cout << "               throw      Throw an error" << std::endl << std::endl;

    std::cout << "  time       FORMAT               Example                Example result " << std::endl;
    std::cout << "             yyyy-mm-d HH:MM:SS   \"2024-01-7 13:06:00\"  Stops 1. january 2024, at 13:06:00." << std::endl;
    std::cout << "             d HH:MM:SS           \"9 13:06:00\"          Stops on the ninth day this at 13:06." << std::endl;
    std::cout << "               HH:MM:SS           \"13:02:11\"            Stops today 2 minutes and 11 seconds past 13 hundred hours." << std::endl;
    std::cout << "               HH:MM              \"13:02:00\"            Stops today, 2 minutes past 13 hundred hours." << std::endl;
    std::cout << std::endl << std::endl;




}