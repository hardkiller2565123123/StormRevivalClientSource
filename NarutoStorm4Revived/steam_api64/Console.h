#ifndef CONSOLE_H 
#define CONSOLE_H
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

class ConsoleLogger : public std::streambuf {
    std::streambuf* consoleBuf;
    std::ofstream logFile;
public:
    ConsoleLogger(const std::string& path) {
        consoleBuf = std::cout.rdbuf();
        logFile.open(path, std::ios::out | std::ios::trunc);
        std::cout.rdbuf(this);
    }

    ~ConsoleLogger() {
        std::cout.rdbuf(consoleBuf);
        logFile.close();
    }

protected:
    virtual int overflow(int c) override {
        if (c == EOF) return !EOF;
        if (consoleBuf) consoleBuf->sputc(c);
        if (logFile.is_open()) logFile.put((char)c);
        return c;
    }

    virtual int sync() override {
        if (consoleBuf) consoleBuf->pubsync();
        if (logFile.is_open()) logFile.flush();
        return 0;
    }
};

class Console
{
public:
    static HANDLE hOut;
    static void InitializeConsole(const std::string& log_path);
    static void PrintOut(const char* format, ...);
    static void PrintOutW(const char* format, ...);
    static void PrintOutY(const char* format, ...);
    static void PrintErr(const char* format, ...);

private:
};

#endif