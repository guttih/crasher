#include "Options.h"
#include <stdexcept>
namespace crasher
{

Options::Options()
{

}

Options::~Options()
{

}

OPTION Options::stringToEnum( std::string argument, bool throwExceptionOnError )
{
    if( argument == "-h" || argument == "-H" || argument == "--help" || argument == "-help" )
    {
        return OPTION::OPTION_HELP;
    }
    else if( argument == "-v" )
        return OPTION::OPTION_VERSION;
    else
    {
        while( argument.length() > 0 && argument[ 0 ] == '-' )
            argument.erase( 0, 1 );

        for( int i = 0; i < OPTION::OPTION_COUNT; i++ )
        {
            if( argument == options[ i ].Name )
                return static_cast< OPTION >( i );
        }

        //No match found
        if( throwExceptionOnError )
            throw std::runtime_error( std::string( "Unknown program argument: " ) + argument );
        else
            return OPTION::OPTION_UNKNOWN;
    }
}


bool Options::findOption( OPTION findMe, char *argv[], int argc )
{
    for( int i = 1; i < argc; i++ )
    {
        std::string argument = argv[ i ];
        OPTION currentOption = stringToEnum( argument, false );
        if( currentOption == findMe )
            return true;
    }
    return false;
}


std::string Options::getName( OPTION option, bool throwExceptionOnError )
{
    if( option == OPTION::OPTION_UNKNOWN || option == OPTION::OPTION_COUNT )
    {
        if( throwExceptionOnError )
            throw std::runtime_error( std::string( "Option::getName Unknown Option. " ) );
        else
            return std::string( "Unknown" );
    }

    return options[ static_cast< int >( option ) ].Name;
}

bool Options::isNumber( const std::string& s )
{
    for( char const &ch : s )
    {
        if( std::isdigit( ch ) == 0 )
            return false;
    }
    return true;
}


unsigned long Options::stringToUlong( std::string argument, bool throwExceptionOnError )
{
    if( !isNumber( argument ) )
    {
        if( throwExceptionOnError )
            throw std::runtime_error( std::string( argument ) + std::string( " is not a number. " ) );
        else
            return -1;
    }

    return std::stoul( argument, nullptr, 0 );

}

} // namespace crasher