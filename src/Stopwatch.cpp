#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include "Stopwatch.h"
#include <iomanip>
#include <sstream>
#include <ctime>
// #include <chrono>

Stopwatch::Stopwatch()
{

}

Stopwatch::~Stopwatch()
{

}

void Stopwatch::start( std::tm stopTime )
{
    _start_time = std::chrono::system_clock::now();
    _stop_time = this->convert( stopTime );
}


void Stopwatch::start( unsigned long msStopAfter )
{
    start( addMilliseconds( now(), msStopAfter ) );
}

void Stopwatch::start()
{
    _start_time = std::chrono::system_clock::now();
}

void Stopwatch::setStopTime( std::tm timeInfo )
{
    _stop_time = this->convert( timeInfo );
}

bool Stopwatch::isActive()
{
    std::chrono::time_point< std::chrono::system_clock > nuna = std::chrono::system_clock::now();
    return nuna < _stop_time;
}


long Stopwatch::elapsedMillis()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now() - _start_time ).count();
}
std::string Stopwatch::elapsedString()
{
    return "Elapsed " + std::to_string( this->elapsedMillis() );

}
std::string Stopwatch::infoString()
{
    return "Started :" + this->formatTime( this->convert( _start_time ), "%Y-%m-%d %H:%M:%S" ) + "\n" +
           "Stopping:" + this->formatTime( this->convert( _stop_time ), "%Y-%m-%d %H:%M:%S" );

}
std::tm Stopwatch::now()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t( now );
    std::tm now_tm = *std::localtime( &now_c );
    return now_tm;
}

std::string Stopwatch::formatTime( const std::tm& timeInfo, const std::string& format )
{
    char buffer[ 80 ]; // Adjust the buffer size as needed
    std::strftime( buffer, sizeof( buffer ), format.c_str(), &timeInfo );
    return buffer;
}

std::string Stopwatch::nowString( const std::string& format )
{

    return this->formatTime( this->now(), format );
}
std::tm Stopwatch::addMilliseconds( std::tm timeInfo, unsigned long millisecondsToAdd )
{
    std::tm timeCopy = timeInfo;
    std::time_t time_t_copy = std::mktime( &timeCopy );
    auto timePoint = std::chrono::system_clock::from_time_t( time_t_copy );

    timePoint += std::chrono::milliseconds( millisecondsToAdd );

    // Convert back to std::tm
    std::time_t new_time_t = std::chrono::system_clock::to_time_t( timePoint );
    return *std::localtime( &new_time_t );
}
std::tm Stopwatch::convert( std::chrono::time_point< std::chrono::system_clock > timePoint )
{
    // Convert time_point to seconds since the epoch
    std::time_t timeT = std::chrono::system_clock::to_time_t( timePoint );

    // Convert time_t to std::tm (local time)
    std::tm timeInfoLocal = *std::localtime( &timeT );

    // Convert time_t to std::tm (UTC time)
    std::tm timeInfoUTC = *std::gmtime( &timeT );

    return timeInfoUTC;
}

std::chrono::time_point< std::chrono::system_clock > Stopwatch::convert( const std::tm& timeInfo )
{
    // Define the epoch time (January 1, 1970)
    std::tm epochTime;
    epochTime.tm_year = 70; // Year since 1900
    epochTime.tm_mon = 0;   // January
    epochTime.tm_mday = 1;  // Day
    epochTime.tm_hour = 0;  // Hour
    epochTime.tm_min = 0;   // Minutes
    epochTime.tm_sec = 0;   // Seconds

    // Calculate the duration in seconds
    std::chrono::seconds durationSeconds =
        std::chrono::seconds( std::mktime( const_cast< std::tm* >( &timeInfo ) ) - std::mktime( const_cast< std::tm* >( &epochTime ) ) );

    // Create a time_point using the calculated duration
    return std::chrono::system_clock::time_point( durationSeconds );
}
std::chrono::time_point< std::chrono::system_clock > Stopwatch::getStartTime() const
{
    return _start_time;
}

std::tm Stopwatch::overwrite( std::tm timeBase, const std::tm timeOverwrite )
{
    std::tm retTime = timeBase;


    if( timeOverwrite.tm_year > 0 )
        return timeOverwrite;
    else if( timeOverwrite.tm_mon > 0 )
    {
        retTime = timeOverwrite;
        retTime.tm_year = timeBase.tm_year;
        return retTime;
    }
    else if( timeOverwrite.tm_mday > 0 )
    {
        retTime = timeOverwrite;
        retTime.tm_year = timeBase.tm_year;
        retTime.tm_mon = timeBase.tm_mon;
        return retTime;
    }
    else if( timeOverwrite.tm_hour > 0 )
    {
        retTime = timeOverwrite;
        retTime.tm_year = timeBase.tm_year;
        retTime.tm_mon = timeBase.tm_mon;
        retTime.tm_mday = timeBase.tm_mday;

        return retTime;
    }
    else if( timeOverwrite.tm_min > 0 )
    {
        retTime = timeOverwrite;
        retTime.tm_year = timeBase.tm_year;
        retTime.tm_mon = timeBase.tm_mon;
        retTime.tm_mday = timeBase.tm_mday;
        retTime.tm_hour = timeBase.tm_hour;
        return retTime;
    }
    else if( timeOverwrite.tm_sec > 0 )
    {
        retTime = timeOverwrite;
        retTime.tm_year = timeBase.tm_year;
        retTime.tm_mon = timeBase.tm_mon;
        retTime.tm_mday = timeBase.tm_mday;
        retTime.tm_hour = timeBase.tm_hour;
        retTime.tm_min = timeBase.tm_min;
        return retTime;
    }

    throw std::runtime_error( "Cannot overwrite tm" );
}

std::tm Stopwatch::stringToTime( const std::string& str )
{
    std::tm timeNow = this->now();
    std::tm timeInput = {};

    std::istringstream ss( str );
    ss >> std::get_time( &timeInput, "%Y-%m-%d %H:%M:%S" );
    if( !ss.fail() )
        return overwrite( timeNow, timeInput );

    ss = std::istringstream( str ); timeInput = {};
    ss >> std::get_time( &timeInput, "%m-%d %H:%M:%S" );
    if( !ss.fail() )
        return overwrite( timeNow, timeInput );

    ss = std::istringstream( str ); timeInput = {};
    ss >> std::get_time( &timeInput, "%d %H:%M:%S" );
    if( !ss.fail() )
        return overwrite( timeNow, timeInput );

    ss = std::istringstream( str ); timeInput = {};
    ss >> std::get_time( &timeInput, "%H:%M:%S" );
    if( !ss.fail() )
        return overwrite( timeNow, timeInput );

    ss = std::istringstream( str ); timeInput = {};
    ss >> std::get_time( &timeInput, "%H:%M" );
    if( !ss.fail() )
        return overwrite( timeNow, timeInput );

    throw std::runtime_error( "Failed to parse time string: " + str );
}
#endif // __STOPWATCH_H__