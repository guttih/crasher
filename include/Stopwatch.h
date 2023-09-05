#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <string>

class Stopwatch
{
private:
    std::chrono::time_point< std::chrono::system_clock > _start_time;
// std::chrono::_V2::system_clock::time_point _start_time;

public:
    Stopwatch();
    ~Stopwatch();
    void start();
    long elapsed_time();
    std::string elapsedString();

    /**
     * @brief Add milliseconds to a time structure and returns a new time structure
     *
     * @param timeInfo
     * @param millisecondsToAdd
     * @return std::tm
     */
    std::tm now();
    std::tm addMilliseconds( std::tm timeInfo, int millisecondsToAdd );
    std::string nowString( const std::string& format="%Y-%m-%d %H:%M:%S" );
    std::tm convert( std::chrono::time_point< std::chrono::system_clock > timePoint );
    std::chrono::time_point< std::chrono::system_clock > convert( const std::tm& timeInfo );

    /**
     * @brief Format a time structure into a string
     *
     * See https://en.cppreference.com/w/cpp/chrono/c/strftime for format options
     *
     * @param timeInfo
     * @param format
     * @return std::string
     */
    std::string formatTime( const std::tm& timeInfo, const std::string& format="%T" );

    /**
     * @brief Get start time as immutable variable
     *
     */
    std::chrono::time_point< std::chrono::system_clock > getStartTime() const;
};

#endif