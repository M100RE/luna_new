#pragma once

#ifdef _WIN32
    #define LUNA_OS_WINDOWS
    #define LUNA_OS_WIN32
#elifdef _WIN64
    #define LUNA_OS_WINDOWS
    #define LUNA_OS_WIN64
#elifdef __linux__
    #define LUNA_OS_LINUX
#elifdef __APPLE__
    #define LUNA_OS_MAC
#endif

#ifdef unix
    #define LUNA_OS_UNIX
#endif