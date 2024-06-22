#pragma once

#include <string>

namespace Log {

    class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual void LogInfo(const std::string& data) const = 0;
        virtual void LogWarning(const std::string& data) const = 0;
        virtual void LogError(const std::string& data) const = 0;
    };

}