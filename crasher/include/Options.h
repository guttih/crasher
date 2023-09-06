#ifndef OPTIONS_H
#define OPTIONS_H

#include "base.h"
#include <string>

namespace crasher
{

class Options
{
public:
    Options();
    ~Options();
    OPTION stringToEnum( std::string argument, bool throwExceptionOnError = true );
    std::string getName( OPTION option,  bool throwExceptionOnError = true );
    unsigned long stringToUlong( std::string argument, bool throwExceptionOnError = true );
    bool findOption( OPTION findMe, char *argv[], int argc );


private:
    bool isNumber( const std::string& s );
};
}

#endif