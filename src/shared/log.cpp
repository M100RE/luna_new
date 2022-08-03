#include <luna/shared/log.h>
#include <iostream>
#include <ctime>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace luna
{
    std::string logger::format_time_number(uint8_t number)
    {
        if(number / 10 == 0)
        {
            std::string formatted = "0";
            formatted += std::to_string(number);
            return formatted;
        }
        else
        {
            return std::to_string(number);
        }
    }

    logger::logger(LN_LOG_TYPE log_type, const char* file, const char* function, int line)
    #ifdef _WIN32
        : log_type(log_type)
    #endif
    {
        std::string format = "";

    #ifndef _WIN32
        switch (log_type)
        {
            case LN_LOG_TYPE_INFO: format = "\e[38;5;4mINFO"; break;
            case LN_LOG_TYPE_FATAL: format = "\e[48;5;196;1mFATAL"; break;
            case LN_LOG_TYPE_WARNING: format = "\e[38;5;220mWARNING"; break;
            case LN_LOG_TYPE_TRACE: format = "\e[38;5;240mTRACE"; break;
            case LN_LOG_TYPE_ERROR: format = "\e[38;5;196;1mERROR"; break;
        }
    #endif

        std::time_t current_time = std::time(0);
        std::tm* now = std::localtime(&current_time);

    #ifdef _WIN32
        switch (log_type)
        {
            case LN_LOG_TYPE_INFO: format = "INFO"; color = 2; break;
            case LN_LOG_TYPE_FATAL: format = "FATAL"; color = 79; break;
            case LN_LOG_TYPE_WARNING: format = "WARNING"; color = 6; break;
            case LN_LOG_TYPE_TRACE: format = "TRACE"; color = 8; break;
            case LN_LOG_TYPE_ERROR: format = "ERROR"; color = 12; break;
        }
    #else
        message_stream << "[" << format_time_number(now->tm_mday) << "." << format_time_number(now->tm_mon + 1) << "." << now->tm_year + 1900 << "|" << format_time_number(now->tm_hour) << ":" << format_time_number(now->tm_min) << ":" << format_time_number(now->tm_sec) << "]-";
        message_stream << format << ": " << file << ":" << line << " (" << function << "): ";
    #endif
    }

    logger::~logger()
    {
    #ifdef _WIN32
        message_stream << "\n";
        std::cout << date.str();

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, color);

        std::cout << message_stream.str();

        SetConsoleTextAttribute(hConsole, 7);
    #else
        message_stream << "\e[0m\n";
        std::cout << message_stream.str();
    #endif
    } 
}
