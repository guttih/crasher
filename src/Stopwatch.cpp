#include "Stopwatch.h"
// #include <chrono>

Stopwatch::Stopwatch()
{

}

Stopwatch::~Stopwatch()
{

}
void Stopwatch::start()
{

    _start_time = std::chrono::system_clock::now();
}
long Stopwatch::elapsed_time()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now() - _start_time ).count();
}
std::string Stopwatch::elapsedString()
{
    return "Elapsed " + std::to_string( this->elapsed_time() );

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
std::tm Stopwatch::addMilliseconds( std::tm timeInfo, int millisecondsToAdd )
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