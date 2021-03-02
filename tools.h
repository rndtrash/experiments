#ifndef TOOLS_H
#define TOOLS_H

#define DEBUG(x) {printf("%s %s\n", "DEBUG:", x);}

#if defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#define PR_SIZET "z"
#elif defined(_WIN32)
#define PR_SIZET ""
#elif defined(_WIN64)
#define PR_SIZET "I"
#else
#error "Unknown platform!"
#endif

#endif
