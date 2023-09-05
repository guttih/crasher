#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>


class Output
{
public:
    Output( const char* applicationName );
    ~Output();
    void help();

private:
    std::string _applicationName;
};

#endif