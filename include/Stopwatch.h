#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <string>

class Stopwatch
{
private:
    std::chrono::time_point< std::chrono::system_clock > _start_time;
    std::chrono::time_point< std::chrono::system_clock > _stop_time;

// std::chrono::_V2::system_clock::time_point _start_time;

public:
    Stopwatch();
    ~Stopwatch();

    /**
     * @brief Start the stopwatch
     *
     * @param msStopAfter - set the time to stop the stopwatch in milliseconds
     */
    void start( unsigned long msStopAfter );

    /**
     * @brief Start the stopwatch
     *
     * @param stopTime - set the time to stop the stopwatch
     */
    void start( std::tm stopTime );

    /**
     * @brief Start the stopwatch
     *
     */
    void start();
    long elapsedMillis();
    std::string elapsedString();
    std::string infoString();
    void setStopTime( std::tm timeInfo );

    /**
     * @brief   Check if the stopwatch is active (not stopped)
     * @details This function compares if the current time is
     *          less than the stop time.
     * @return bool
     */
    bool isActive();

    /**
     * @brief Add milliseconds to a time structure and returns a new time structure
     *
     * @param timeInfo
     * @param millisecondsToAdd
     * @return std::tm
     */
    std::tm now();
    std::tm addMilliseconds( std::tm timeInfo, unsigned long millisecondsToAdd );

    /**
     * @brief Get the current time as a string
     *
     * @param format
     * @return std::string
     */
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
     * @example std::tm timeInfo = stopwatch.now();
     *          std::cout << stopwatch.formatTime( timeInfo, "%Y-%m-%d %H:%M:%S" ) << std::endl;
     * @return std::string
     */
    std::string formatTime( const std::tm& timeInfo, const std::string& format="%T" );

    /**
     * @brief Get start time as immutable variable
     *
     */
    std::chrono::time_point< std::chrono::system_clock > getStartTime() const;

    // std::tm stringToTime( std::string argument );
    std::tm stringToTime( const std::string& str );

    /**
     * @brief Overwrite a time structure with another time structure
     *
     * @param timeBase
     * @param timeOverwrite
     * @return std::tm
     */
    std::tm overwrite( std::tm timeBase, const std::tm timeOverwrite );

};

#endif