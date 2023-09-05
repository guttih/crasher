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
    // Crasher::PARAM_OPTION parse( std::string argument, bool throwExceptionOnError = true );
    crasher::OPTION parse( std::string argument, bool throwExceptionOnError );
    ~Options();

private:

};
}

#endif