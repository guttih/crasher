#include <iostream>
#include "Version.h"
#include "Output.h"
#include "Options.h"
#include "Stopwatch.h"


int main( int argc, char* argv[] )
{
    // Argument argHelp( Argument::ARGUMENT::HELP,         Argument::PARAM_TYPE::NONE,   0, { "help", "h" } );

    // Arguments aa;
    // aa.init();
    crasher::Options options;
    Output o( argv[ 0 ] );
    Version v( 1, 0 );
    std::cout << "Crasher x- version " << v.c_str() << std::endl;
    auto t_start = std::chrono::high_resolution_clock::now();
    if( argc < 2 )
    {
        std::cerr << "Usage: " << argv[ 0 ] << " <argument1>[ argument2 ... ] \
    " << std::endl;
        return 1;  // Exit with an error code
    }

    int a=0;

    int b = 3 / a;

    for( int i = 1; i < argc; i++ )
    {
        std::string argument = argv[ i ];
        // if( argument == " - h " || argument == " - H "  || argument == " --help "  || argument == " - help " )
        // {
        //     o.help();
        //     return PROGRAM_EXIT_TYPE::SUCCESS;
        // }
        // else
        // {
        //     if( argument == " - v " || argument == " --version " )
        //     {
        //         std::cout << "Crasher - version " << v.c_str() << std::endl;
        //         return PROGRAM_EXIT_TYPE::SUCCESS;
        //     }
        // }

        options.parse( argument, true );

        std::cout << "Argument " << i << " : " << argument << std::endl;


    }

    Stopwatch stopwatch;
    stopwatch.start();
    auto now = stopwatch.now();
    std::cout << "     Now: " << stopwatch.formatTime( now ) << std::endl;
    std::cout << " +10 sec: " << stopwatch.formatTime( stopwatch.addMilliseconds( now, 10000 ) ) << std::endl;
    // std::cout << "Starting " << stopwatch.nowString() << std::endl;
    std::cout << "Starting stopwatch" << stopwatch.elapsedString() << std::endl;


    while( true )
    {
        if( stopwatch.elapsed_time() > 10000 )
        {
            std::cout << "Crashing now!" << std::endl;
            std::cout << "stopwatch" << stopwatch.elapsedString() << std::endl;
            std::cout << "started at " << stopwatch.formatTime( stopwatch.convert( stopwatch.getStartTime() ) ) << std::endl;
            std::cout << "Stopping: " << stopwatch.nowString() << std::endl;

            return 0;
        }

    }
}
