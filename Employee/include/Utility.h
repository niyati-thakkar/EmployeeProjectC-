#ifndef _UTILITY_H
#define _UTILITY_H

#define PIN int
#define EID int
#define DID int
#define MID int
#define TID int
#define AID int
#define HID int

#include <string>
#include <regex>
#include "DatabaseWrapper.h"
#include <type_traits>
#include <iostream>
#include <windows.h>
#include "Validation.h"

#define RED_COLOR "\033[1;31m"
#define YELLOW_COLOR "\033[1;33m"
#define DEFAULT_COLOR "\033[0m"

template<typename T>
struct PropertyMap {
    std::string name;
    bool(T::* setter)(std::string);
    std::string(T::* getter)() const;
    bool isOptional;
};

namespace Utility {

    static inline std::string backMessage = "0. Go back to previous menu!";
    static inline std::string exitMessage = "100. To exit!";

    template<class T, class U>
    struct are_same_template : std::is_same<T, U>
    {};

    template<template<class...> class T, class T1, class T2>
    struct are_same_template<T<T1>, T<T2>> : std::true_type
    {};

    template<typename T1>
    [[nodiscard]] bool setInput(T1& res) {
        std::cout << YELLOW_COLOR;
        std::string arg;
        std::getline(std::cin, arg);
        std::cout << DEFAULT_COLOR;
        if constexpr (std::is_same_v<T1, std::string>) {
            res = arg;
        }
        else if constexpr (std::is_arithmetic_v<T1>) {
            try {
                res = stoi(arg);
            }
            catch (...) {
                return false;
            }
        }
        else {
            res = arg[0];
        }
        return true;
    }

    inline bool tryAgain() {
        std::cout << RED_COLOR << "The entered value is not valid. Do you wish to try again?\n" << DEFAULT_COLOR
            << "1. YES\n2. NO, Go Back to previous Menu!\n";
        int opt;
        if (setInput(opt))
            return opt == 1;
        return false;
    }

    template<typename T1, typename T2 = T1>
    [[nodiscard]] bool getUserInput(T1& e, const PropertyMap<T2>& map) {
        int cnt = 0;
        do {
            std::cout << "Enter " << map.name << "\n";
            std::string temp;
            if (setInput(temp)) {
                if ((e.*(map.setter))(temp)) {
                    return true;
                }
            }
            cnt++;
        } while (cnt < 3 && tryAgain());
        if (cnt == 3) {
            std::cout << RED_COLOR << "Sorry Maximum Limits for invalid input exhausted!" << DEFAULT_COLOR << "\n";
        }
        return false;
    }

    template<typename... Args>
    [[nodiscard]] int takeOption(bool extra, Args... args) {
        if (extra) std::cout << Utility::backMessage << "\n";
        int i = 1;
        ((std::cout << i++ << ". " << std::forward<Args>(args) << " \n"), ...);
        if (extra) std::cout << Utility::exitMessage << "\n";
        int option = 0;
        if (setInput(option)) {
            if (extra && option == 100) {
                exit(0);
            }
            if (option < 0 || option >= i) {
                std::cout << RED_COLOR << "Please enter a valid option" << DEFAULT_COLOR << "\n";
                if (setInput(option) && (option < 0 || option >= i)) {
                    Database::logger.Error("Invalid Option Selected!");
                    return 0;
                }
            }
        }

        return option;
    }

    [[nodiscard]] inline int takeOption(bool extra, std::vector<std::string> args) {
        if (extra) std::cout << Utility::backMessage << "\n";
        int i = 1;
        for (; i <= args.size(); i++) {
            std::cout << i << ". " << args[i - 1] << "\n";
        }
        if (extra) std::cout << Utility::exitMessage << "\n";
        int option = 0;
        if (setInput(option)) {
            if (extra && option == 100) {
                exit(0);
            }
            if (option < 0 || option >= i) {
                std::cout << RED_COLOR << "Please enter a valid option" << DEFAULT_COLOR << "\n";
                if (setInput(option) && (option < 0 || option >= i)) {
                    Database::logger.Error("Invalid Option Selected!");
                    return 0;
                }
            }
        }

        return option;
    }

    inline int getConsoleWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    inline void printHeading(const std::string& heading) {
        int consoleWidth = getConsoleWidth();
        int headingWidth = heading.length();
        int padding = (consoleWidth - headingWidth) / 2;

        std::string outputLine(consoleWidth, '=');

        std::cout << outputLine << "\n";
        std::cout << std::setw(padding) << "" << heading << std::endl;
        std::cout << outputLine << "\n";
    }

}

#endif
