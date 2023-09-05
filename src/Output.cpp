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
    std::cout << "This application will crash on demand "  << std::endl << std::endl;
    std::cout << "Options  " << std::endl;
    std::cout << "  --help,-h,-H            = Print usage information and exit." << std::endl;
    std::cout << "  --after,-a <msSeconds>  = Crashes after specified number of milliseconds." << std::endl;

}