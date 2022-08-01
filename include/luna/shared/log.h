#ifndef _MSTL_LOG_H
#define _MSTL_LOG_H

#include <sstream>

enum LN_LOG_TYPE
{
    LN_LOG_TYPE_INFO = 0,
    LN_LOG_TYPE_WARNING = 1,
    LN_LOG_TYPE_ERROR = 2,
    LN_LOG_TYPE_FATAL = 3,
    LN_LOG_TYPE_TRACE = 4
};

namespace luna
{
    class logger
    {
    private:
        std::stringstream message_stream;

        std::string format_number(int number);

    public:
        logger(LN_LOG_TYPE log_type, const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());
        ~logger();

        template <typename T>
        logger& operator << (T argument)
        {
            message_stream << argument;
            return *this;
        }
    };
}

#define LN_ERROR luna::logger(LN_LOG_TYPE_ERROR)
#define LN_FATAL luna::logger(LN_LOG_TYPE_FATAL)
#define LN_INFO luna::logger(LN_LOG_TYPE_INFO)
#define LN_WARNING luna::logger(LN_LOG_TYPE_WARNING)
#define LN_TRACE luna::logger(LN_LOG_TYPE_TRACE)

#endif