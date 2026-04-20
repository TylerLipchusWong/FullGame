#include "Engine/Core/Logger.hpp"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Engine::Core {

std::mutex Logger::s_mutex;
std::ofstream Logger::s_logFile;
bool Logger::s_isInitialized = false;

bool Logger::Initialize() {
    const std::filesystem::path logPath = std::filesystem::current_path() / "FullGame.log";

    {
        std::lock_guard<std::mutex> lock(s_mutex);

        if (s_isInitialized) {
            return true;
        }

        s_logFile.open(logPath, std::ios::out | std::ios::trunc);

        if (!s_logFile.is_open()) {
            std::cerr << "[LOGGER] Failed to open log file: " << logPath.string() << '\n';
            return false;
        }

        s_isInitialized = true;
    }

    Log(LogLevel::Info, "Logger initialized. Log file: " + logPath.string());
    return true;
}

void Logger::Shutdown() {
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_isInitialized) {
        return;
    }

    const auto now = std::chrono::system_clock::now();
    const std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime {};
#if defined(_WIN32)
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif

    s_logFile << '[' << std::put_time(&localTime, "%H:%M:%S") << "] [INFO] Logger shutdown" << '\n';
    s_logFile.flush();
    s_logFile.close();
    s_isInitialized = false;
}

void Logger::Log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(s_mutex);

    const auto now = std::chrono::system_clock::now();
    const std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime {};
#if defined(_WIN32)
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%H:%M:%S");

    const std::string line = '[' + oss.str() + "] [" + LevelToString(level) + "] " + message;
    std::cout << line << '\n';

    if (s_logFile.is_open()) {
        s_logFile << line << '\n';
        s_logFile.flush();
    }
}

const char* Logger::LevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warning:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    }
    return "UNKNOWN";
}

} // namespace Engine::Core
