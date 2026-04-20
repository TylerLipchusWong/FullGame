#pragma once

#include <mutex>
#include <string>

namespace Engine::Core {

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    static void Initialize();
    static void Shutdown();

    static void Log(LogLevel level, const std::string& message);

private:
    static const char* LevelToString(LogLevel level);
    static std::mutex s_mutex;
};

} // namespace Engine::Core
