/**
 * @file Colors.h
 * @brief Cross-platform colored console output
 * @date February 2026
 */

#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @class ConsoleColor
 * @brief Provides colored text output for Windows and Unix systems
 * 
 * Uses Windows Console API on Windows and ANSI escape codes on Linux/Mac.
 */
class ConsoleColor {
public:
    /**
     * @enum Color
     * @brief Color codes for semantic event coloring
     */
    enum Color {
        RESET = 0,    /**< Default terminal color */
        GREEN = 1,    /**< Scaling up events */
        RED = 2,      /**< Scaling down events */
        CYAN = 3,     /**< Informational messages */
        YELLOW = 4,   /**< Status updates */
        MAGENTA = 5   /**< Summary/completion messages */
    };
    
    /**
     * @brief Set console color for subsequent output
     * @param color Color to apply
     */
    static void setColor(Color color);
    
    /**
     * @brief Reset console to default color
     */
    static void reset();
    
    /**
     * @brief Wrap text with color codes (doesn't require reset)
     * @param text Text to colorize
     * @param color Color to apply
     * @return Colored string (platform-specific codes)
     */
    static std::string colorize(const std::string& text, Color color);
};

#endif // COLORS_H
