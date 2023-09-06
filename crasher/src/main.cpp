#include <iostream>
#include "Version.h"
#include "Output.h"
#include "Options.h"
#include "Stopwatch.h"
#include <thread>

using namespace crasher;

bool debugging = false;
PROGRAM_EXIT_TYPE exitType = PROGRAM_EXIT_TYPE::SUCCESS;
void debugPrint( std::string message )
{
    if( !debugging )
        return;
    std::cout << message;
}

void debugPrint( std::string msg1, std::string msg2 )
{
    debugPrint( msg1 + msg2 );
}
void debugPrintLn( std::string message )
{
    debugPrint( message + "\n" );
}
void debugPrintLn( std::string msg1, std::string msg2 )
{
    debugPrint( msg1 + msg2 + "\n" );
}

int crashWithDivisionByZero()
{
    debugPrintLn( "with error division by zero." );
    int a = 1;
    int b=2;
    a--;
    b = 21 / a;
    return b;
}
int crashWithSegmentFault()
{
    debugPrintLn( "with error segment fault." );
    int *intPtr = nullptr;
    *intPtr = 42;
    return PROGRAM_EXIT_TYPE::SEGMENT_FAULT;
}

int crashWithThrowException()
{
    debugPrintLn( "by throwing an error." );
    throw std::runtime_error( "Exception thrown" );
}


int main( int argc, char *argv[] )
{
    int *intPtr = nullptr;
    Stopwatch stopwatch;
    Options options;
    debugging = options.findOption( OPTION::OPTION_DEBUG, argv, argc );
    Output o( argv[ 0 ] );
    Version v( 1, 0 );

    debugPrintLn( "Crasher ", v.c_str() );
    auto t_start = std::chrono::high_resolution_clock::now();
    if( argc < 2 )
    {
        o.help();
        return PROGRAM_EXIT_TYPE::SUCCESS;
    }


    OPTION currentOption = OPTION::OPTION_UNKNOWN;
    OPTION selectedTimer = OPTION::OPTION_UNKNOWN;
    unsigned long ulValue;
    unsigned long msStopAfter = 0;
    for( int i = 1; i < argc; i++ )
    {
        std::string optArg = argv[ i ];
        std::string argument;
        currentOption = options.stringToEnum( optArg, true );
        debugPrint( "Option " + std::to_string( i ) + " : " + optArg );
        switch( currentOption )
        {
            case OPTION::OPTION_HELP:
                o.help();
                return PROGRAM_EXIT_TYPE::SUCCESS;
                break;

            case OPTION::OPTION_VERSION:
                std::cout << "version " << v.c_str() << std::endl;
                return PROGRAM_EXIT_TYPE::SUCCESS;
                break;
            case OPTION::OPTION_CRASH_TYPE:
                if( i + 1 >= argc )
                    throw std::runtime_error( std::string( "Option argument missing for : " ) + options.getName( OPTION_CRASH_TYPE ) );
                i++;
                argument = argv[ i ];
                debugPrint( " " + std::string( argument ) );
                if( argument == "divZero" )
                    exitType = PROGRAM_EXIT_TYPE::DIVISION_BY_ZERO;
                else if( argument == "segFault" )
                    exitType = PROGRAM_EXIT_TYPE::SEGMENT_FAULT;
                else if( argument == "throw" )
                    exitType = PROGRAM_EXIT_TYPE::THROW_EXCEPTION;
                else
                    throw std::runtime_error( std::string( "Unknown crash type: " ) + argument + " or missing argument." );
                break;

            case OPTION::OPTION_AFTER:
                if( i + 1 >= argc )
                    throw std::runtime_error( std::string( "Option argument missing for : " ) + options.getName( OPTION_AFTER ) );
                i++;
                debugPrint( " " + std::string( argv[ i ] ) );
                msStopAfter = options.stringToUlong( argv[ i ], true );
                if( msStopAfter > 0 )
                {
                    selectedTimer = currentOption;
                    stopwatch.start( msStopAfter );
                }
                break;
            case OPTION::OPTION_AT:

                if( i + 1 >= argc )
                    throw std::runtime_error( std::string( "Option argument missing for : " ) + options.getName( OPTION_AT ) );
                i++;
                argument = argv[ i ];
                debugPrint( " " + std::string( argument ) );
                std::tm timeInfo = stopwatch.stringToTime( argument );
                if( timeInfo.tm_year > 0 )
                {
                    selectedTimer = currentOption;
                    stopwatch.start( timeInfo );
                }
                break;
        }
        debugPrintLn( "" );

    }

    debugPrintLn( stopwatch.infoString() );
    while( stopwatch.isActive() )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    }

    debugPrint( "Exiting " );
    switch( exitType )
    {
        case PROGRAM_EXIT_TYPE::SUCCESS:
            debugPrintLn( "normally with success" );
            return PROGRAM_EXIT_TYPE::SUCCESS;
            break;
        case PROGRAM_EXIT_TYPE::ERROR:
            debugPrintLn( "normally with error." );
            return PROGRAM_EXIT_TYPE::ERROR;
            break;


        case PROGRAM_EXIT_TYPE::THROW_EXCEPTION:
            return crashWithThrowException();
            break;

        case PROGRAM_EXIT_TYPE::SEGMENT_FAULT:
            return crashWithSegmentFault();
            break;
        case PROGRAM_EXIT_TYPE::DIVISION_BY_ZERO:
            return crashWithDivisionByZero();
            break;
    }

    debugPrintLn( "Exiting: " + stopwatch.nowString() );
}




