#ifndef APPLICATION_BASE_H
#define APPLICATION_BASE_H


namespace crasher
{


enum PROGRAM_EXIT_TYPE
{
    SUCCESS,
    ERROR,
    DIVISION_BY_ZERO,
    SEGMENT_FAULT,
    THROW_EXCEPTION
};


enum OPTION {
    OPTION_HELP,
    OPTION_VERSION,
    OPTION_CRASH_TYPE,
    OPTION_AFTER,
    OPTION_AT,
    OPTION_COUNT
};

struct OPTION_TEXT
{
    const char Name[ 20 ];
};

extern OPTION_TEXT options[ OPTION::OPTION_COUNT ];


} // namespace crasher

#endif