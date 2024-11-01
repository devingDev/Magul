#ifndef _HELPER_H
#define _HELPER_H

#include <filesystem>
#include <limits.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


std::filesystem::path GetExeDirectory();





#endif