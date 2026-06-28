#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include <iostream>
#include <fstream>
#include <streambuf>
#include <WinSock2.h>
#include <Windows.h>

#include "Common.h"
#include "Console.h"

#include <io.h>      // _open_osfhandle
#include <fcntl.h>   // _O_TEXT

using namespace std;
// 
ConsoleLogger* g_logger = nullptr;

void InitConsoleLogger(const std::string& logPath) {
    if (!g_logger) {
        g_logger = new ConsoleLogger(logPath);
    }
}

void ShutdownConsoleLogger() {
    delete g_logger;
    g_logger = nullptr;
}



HANDLE Console::hOut = nullptr;

void Console::InitializeConsole(const std::string& log_path)
{
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Console::PrintOut("====== STORM MODDING API CONSOLE ======\n");
}

#include <windows.h>
#include <cstdarg>
#include <cstdio>
#include <iostream>

static const WORD COLOR_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
static const WORD COLOR_RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
void Console::PrintOutY(const char* format, ...)
{
    if (!format) return;
    va_list args;
    va_start(args, format);

    const char* p = format;
    const char* segStart = p;

    while (*p)
    {
        if (*p == '%')
        {
            // print literal before '%'
            if (p > segStart)
            {
                SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // main color
                std::cout.write(segStart, (std::streamsize)(p - segStart));
            }

            p++; // skip '%'
            if (*p == '%') { std::cout.put('%'); p++; segStart = p; continue; }

            // detect length modifiers
            bool is_h = false, is_l = false, is_ll = false;
            const char* q = p;
            while (*q && !strchr("diuoxXpcsfeEgG", *q)) q++;
            if (!*q) break;
            const char spec = *q;

            // scan between p and q for l/h
            for (const char* t = p; t < q; ++t) {
                if (*t == 'l') { if (is_l) is_ll = true; else is_l = true; }
                else if (*t == 'h') is_h = true;
            }

            // format arg to buffer
            char argBuf[1024] = { 0 };
            switch (spec)
            {
            case 'd': case 'i':
                if (is_ll) { long long v = va_arg(args, long long); snprintf(argBuf, sizeof(argBuf), "%lld", v); }
                else if (is_l) { long v = va_arg(args, long); snprintf(argBuf, sizeof(argBuf), "%ld", v); }
                else { int v = va_arg(args, int); snprintf(argBuf, sizeof(argBuf), "%d", v); }
                break;
            case 'u': case 'o': case 'x': case 'X':
                if (is_ll) { unsigned long long v = va_arg(args, unsigned long long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%llu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%llo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%llx", v); else snprintf(argBuf, sizeof(argBuf), "%llX", v); }
                else if (is_l) { unsigned long v = va_arg(args, unsigned long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%lu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%lo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%lx", v); else snprintf(argBuf, sizeof(argBuf), "%lX", v); }
                else { unsigned int v = va_arg(args, unsigned int); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%u", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%o", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%x", v); else snprintf(argBuf, sizeof(argBuf), "%X", v); }
                break;
            case 'p':
            {
                void* ptr = va_arg(args, void*);
                snprintf(argBuf, sizeof(argBuf), "%p", ptr);
                break;
            }
            case 's':
            {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                snprintf(argBuf, sizeof(argBuf), "%s", s);
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                snprintf(argBuf, sizeof(argBuf), "%c", ch);
                break;
            }
            case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':
            {
                double d = va_arg(args, double);
                snprintf(argBuf, sizeof(argBuf), "%f", d);
                break;
            }
            default:
                // unknown: consume as char and print literal
                // try to consume one arg if needed
                argBuf[0] = spec;
                argBuf[1] = 0;
                break;
            }

            // print argument in cyan
            SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            std::cout << argBuf;
            // restore main color
            SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

            p = q + 1;
            segStart = p;
        }
        else
        {
            p++;
        }
    }

    // trailing literal
    if (*segStart)
    {
        SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << segStart;
    }

    // reset
    SetConsoleTextAttribute(Console::hOut, COLOR_RESET);
    va_end(args);
}
void Console::PrintOut(const char* format, ...)
{
    if (!format) return;
    va_list args;
    va_start(args, format);

    const char* p = format;
    const char* segStart = p;

    while (*p)
    {
        if (*p == '%')
        {
            // print literal before '%'
            if (p > segStart)
            {
                SetConsoleTextAttribute(Console::hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // main color
                std::cout.write(segStart, (std::streamsize)(p - segStart));
            }

            p++; // skip '%'
            if (*p == '%') { std::cout.put('%'); p++; segStart = p; continue; }

            // detect length modifiers
            bool is_h = false, is_l = false, is_ll = false;
            const char* q = p;
            while (*q && !strchr("diuoxXpcsfeEgG", *q)) q++;
            if (!*q) break;
            const char spec = *q;

            // scan between p and q for l/h
            for (const char* t = p; t < q; ++t) {
                if (*t == 'l') { if (is_l) is_ll = true; else is_l = true; }
                else if (*t == 'h') is_h = true;
            }

            // format arg to buffer
            char argBuf[1024] = { 0 };
            switch (spec)
            {
            case 'd': case 'i':
                if (is_ll) { long long v = va_arg(args, long long); snprintf(argBuf, sizeof(argBuf), "%lld", v); }
                else if (is_l) { long v = va_arg(args, long); snprintf(argBuf, sizeof(argBuf), "%ld", v); }
                else { int v = va_arg(args, int); snprintf(argBuf, sizeof(argBuf), "%d", v); }
                break;
            case 'u': case 'o': case 'x': case 'X':
                if (is_ll) { unsigned long long v = va_arg(args, unsigned long long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%llu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%llo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%llx", v); else snprintf(argBuf, sizeof(argBuf), "%llX", v); }
                else if (is_l) { unsigned long v = va_arg(args, unsigned long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%lu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%lo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%lx", v); else snprintf(argBuf, sizeof(argBuf), "%lX", v); }
                else { unsigned int v = va_arg(args, unsigned int); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%u", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%o", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%x", v); else snprintf(argBuf, sizeof(argBuf), "%X", v); }
                break;
            case 'p':
            {
                void* ptr = va_arg(args, void*);
                snprintf(argBuf, sizeof(argBuf), "%p", ptr);
                break;
            }
            case 's':
            {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                snprintf(argBuf, sizeof(argBuf), "%s", s);
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                snprintf(argBuf, sizeof(argBuf), "%c", ch);
                break;
            }
            case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':
            {
                double d = va_arg(args, double);
                snprintf(argBuf, sizeof(argBuf), "%f", d);
                break;
            }
            default:
                // unknown: consume as char and print literal
                // try to consume one arg if needed
                argBuf[0] = spec;
                argBuf[1] = 0;
                break;
            }

            // print argument in cyan
            SetConsoleTextAttribute(Console::hOut, COLOR_CYAN);
            std::cout << argBuf;
            // restore main color
            SetConsoleTextAttribute(Console::hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            p = q + 1;
            segStart = p;
        }
        else
        {
            p++;
        }
    }

    // trailing literal
    if (*segStart)
    {
        SetConsoleTextAttribute(Console::hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << segStart;
    }

    // reset
    SetConsoleTextAttribute(Console::hOut, COLOR_RESET);
    va_end(args);
}

void Console::PrintOutW(const char* format, ...)
{
    if (!format) return;
    va_list args;
    va_start(args, format);

    const char* p = format;
    const char* segStart = p;

    while (*p)
    {
        if (*p == '%')
        {
            if (p > segStart)
            {
                SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // main color (white)
                std::cout.write(segStart, (std::streamsize)(p - segStart));
            }

            p++;
            if (*p == '%') { std::cout.put('%'); p++; segStart = p; continue; }

            bool is_h = false, is_l = false, is_ll = false;
            const char* q = p;
            while (*q && !strchr("diuoxXpcsfeEgG", *q)) q++;
            if (!*q) break;
            char spec = *q;
            for (const char* t = p; t < q; ++t) {
                if (*t == 'l') { if (is_l) is_ll = true; else is_l = true; }
                else if (*t == 'h') is_h = true;
            }

            char argBuf[1024] = { 0 };
            switch (spec)
            {
            case 'd': case 'i':
                if (is_ll) { long long v = va_arg(args, long long); snprintf(argBuf, sizeof(argBuf), "%lld", v); }
                else if (is_l) { long v = va_arg(args, long); snprintf(argBuf, sizeof(argBuf), "%ld", v); }
                else { int v = va_arg(args, int); snprintf(argBuf, sizeof(argBuf), "%d", v); }
                break;
            case 'u': case 'o': case 'x': case 'X':
                if (is_ll) { unsigned long long v = va_arg(args, unsigned long long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%llu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%llo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%llx", v); else snprintf(argBuf, sizeof(argBuf), "%llX", v); }
                else if (is_l) { unsigned long v = va_arg(args, unsigned long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%lu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%lo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%lx", v); else snprintf(argBuf, sizeof(argBuf), "%lX", v); }
                else { unsigned int v = va_arg(args, unsigned int); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%u", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%o", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%x", v); else snprintf(argBuf, sizeof(argBuf), "%X", v); }
                break;
            case 'p':
            {
                void* ptr = va_arg(args, void*);
                snprintf(argBuf, sizeof(argBuf), "%p", ptr);
                break;
            }
            case 's':
            {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                snprintf(argBuf, sizeof(argBuf), "%s", s);
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                snprintf(argBuf, sizeof(argBuf), "%c", ch);
                break;
            }
            case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':
            {
                double d = va_arg(args, double);
                snprintf(argBuf, sizeof(argBuf), "%f", d);
                break;
            }
            default:
                argBuf[0] = spec; argBuf[1] = 0;
                break;
            }

            SetConsoleTextAttribute(Console::hOut, COLOR_CYAN);
            std::cout << argBuf;
            SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            p = q + 1;
            segStart = p;
        }
        else p++;
    }

    if (*segStart)
    {
        SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << segStart;
    }

    SetConsoleTextAttribute(Console::hOut, COLOR_RESET);
    va_end(args);
}

void Console::PrintErr(const char* format, ...)
{
    if (!format) return;
    va_list args;
    va_start(args, format);

    const char* p = format;
    const char* segStart = p;

    while (*p)
    {
        if (*p == '%')
        {
            if (p > segStart)
            {
                SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_INTENSITY); // main color (err red)
                std::cerr.write(segStart, (std::streamsize)(p - segStart));
            }

            p++;
            if (*p == '%') { std::cerr.put('%'); p++; segStart = p; continue; }

            bool is_h = false, is_l = false, is_ll = false;
            const char* q = p;
            while (*q && !strchr("diuoxXpcsfeEgG", *q)) q++;
            if (!*q) break;
            char spec = *q;
            for (const char* t = p; t < q; ++t) {
                if (*t == 'l') { if (is_l) is_ll = true; else is_l = true; }
                else if (*t == 'h') is_h = true;
            }

            char argBuf[1024] = { 0 };
            switch (spec)
            {
            case 'd': case 'i':
                if (is_ll) { long long v = va_arg(args, long long); snprintf(argBuf, sizeof(argBuf), "%lld", v); }
                else if (is_l) { long v = va_arg(args, long); snprintf(argBuf, sizeof(argBuf), "%ld", v); }
                else { int v = va_arg(args, int); snprintf(argBuf, sizeof(argBuf), "%d", v); }
                break;
            case 'u': case 'o': case 'x': case 'X':
                if (is_ll) { unsigned long long v = va_arg(args, unsigned long long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%llu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%llo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%llx", v); else snprintf(argBuf, sizeof(argBuf), "%llX", v); }
                else if (is_l) { unsigned long v = va_arg(args, unsigned long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%lu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%lo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%lx", v); else snprintf(argBuf, sizeof(argBuf), "%lX", v); }
                else { unsigned int v = va_arg(args, unsigned int); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%u", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%o", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%x", v); else snprintf(argBuf, sizeof(argBuf), "%X", v); }
                break;
            case 'p':
            {
                void* ptr = va_arg(args, void*);
                snprintf(argBuf, sizeof(argBuf), "%p", ptr);
                break;
            }
            case 's':
            {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                snprintf(argBuf, sizeof(argBuf), "%s", s);
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                snprintf(argBuf, sizeof(argBuf), "%c", ch);
                break;
            }
            case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':
            {
                double d = va_arg(args, double);
                snprintf(argBuf, sizeof(argBuf), "%f", d);
                break;
            }
            default:
                argBuf[0] = spec; argBuf[1] = 0;
                break;
            }

            SetConsoleTextAttribute(Console::hOut, COLOR_CYAN);
            std::cerr << argBuf;
            SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);

            p = q + 1;
            segStart = p;
        }
        else p++;
    }

    if (*segStart)
    {
        SetConsoleTextAttribute(Console::hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << segStart;
    }

    SetConsoleTextAttribute(Console::hOut, COLOR_RESET);
    va_end(args);
}
