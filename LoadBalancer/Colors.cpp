/**
 * @file Colors.cpp
 * @brief Implementation of cross-platform colored console output
 * @date February 2026
 */

#include "Colors.h"

#ifdef _WIN32
void ConsoleColor::setColor(Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(color) {
        case GREEN:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case RED:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        case CYAN:
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case YELLOW:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case MAGENTA:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case RESET:
        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
    }
}

void ConsoleColor::reset() {
    setColor(RESET);
}

std::string ConsoleColor::colorize(const std::string& text, Color color) {
    setColor(color);
    std::cout << text;
    reset();
    return "";
}
#else
// ANSI color codes for Linux/Mac
void ConsoleColor::setColor(Color color) {
    switch(color) {
        case GREEN:
            std::cout << "\033[1;32m";
            break;
        case RED:
            std::cout << "\033[1;31m";
            break;
        case CYAN:
            std::cout << "\033[1;36m";
            break;
        case YELLOW:
            std::cout << "\033[1;33m";
            break;
        case MAGENTA:
            std::cout << "\033[1;35m";
            break;
        case RESET:
        default:
            std::cout << "\033[0m";
            break;
    }
}

void ConsoleColor::reset() {
    std::cout << "\033[0m";
}

std::string ConsoleColor::colorize(const std::string& text, Color color) {
    setColor(color);
    std::cout << text;
    reset();
    return "";
}
#endif
