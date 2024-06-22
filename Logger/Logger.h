#pragma once


#include "ILogger.h"

namespace Log {
    class Logger : public ILogger {
    public:
        void LogInfo(const std::string& data) const override;
        void LogError(const std::string& data) const override;
        void LogWarning(const std::string& data) const override;
    };
}
