#include "../pch.h"
#ifndef _LOG_H
#define _LOG_H

#include <chrono>
#include <string_view>
#include <unordered_map>
#include <functional>
#include <array>
#include <filesystem>
#include <type_traits>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Lognspace {
    class registry {
        friend class Log;

    public:
        static registry& get_instance() {
            static registry instance;
            return instance;
        }

    private:
        std::unordered_map<unsigned int, std::shared_ptr<Log>> logger_objects;
    };

    class Log {
    public:
        enum class Level {
            LevelError = 0, LevelWarning = 1, LevelInfo = 2
        };

    private:
        int ID;
        Level m_LogLevel;
        std::string buffer{};
        std::filesystem::path file_path;
        bool printToFile;

    public:
        inline static std::vector<std::pair<std::string, std::string>> default_message = {
            {"[Error]:","\033[31m[Error]:\033[0m"},
            {"[Warming]","\033[33m[Warning]:\033[0m"},
            {"[Info]:","\033[32m[Info]:\033[0m"}
        };

        Log(Level level = Level::LevelInfo, std::string filep = "", bool to_file = false);
        void set_log_level(Level level);

        template<typename ...eles>
        void Warn(eles&&... messages);

        template<typename ...eles>
        void Error(eles&&... messages);

        template<typename ...eles>
        void Info(eles&&... messages);

        template<typename T, typename ...eles>
        void build_buffer(T&& first, eles&&... elements);

        std::string getDateTime();
        static unsigned int get_id();
        void log_it(int i);
        ~Log();
    };
}

template<typename ...eles>
void Lognspace::Log::Warn(eles&& ...messages)
{
    if (m_LogLevel >= Level::LevelWarning) {
        build_buffer(std::forward<eles>(messages)...);
        log_it(1);
    }
}

template<typename ...eles>
void Lognspace::Log::Error(eles&& ...messages)
{
    if (m_LogLevel >= Level::LevelError) {
        build_buffer(std::forward<eles>(messages)...);
        log_it(0);
    }
}

template<typename ...eles>
void Lognspace::Log::Info(eles&& ...messages)
{
    if (m_LogLevel >= Level::LevelInfo) {
        build_buffer(std::forward<eles>(messages)...);
        log_it(2);
    }
}

template<typename T, typename ...eles>
void Lognspace::Log::build_buffer(T&& first, eles&&... elements) {
    // Append the first element to the buffer
    std::string res;
    if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
        res = std::forward<T>(first);
    }
    else if constexpr (std::is_arithmetic_v<std::decay_t<T>>) {
        res = std::to_string(std::forward<T>(first));
    }
    else {
        res = std::string{ std::forward<T>(first) };
    }
    buffer = buffer + res + " ";

    if constexpr (sizeof...(elements) > 0) {
        build_buffer(std::forward<eles>(elements)...);
    }
}

#endif
