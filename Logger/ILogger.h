#pragma once

#include <string>
#include <any>

namespace Log {

    enum LogLevel {
        Info,
        Warning,
        Error
    };

    class ILogger {
    public:

        virtual ~ILogger() = default;

        virtual void log(LogLevel logLevel, const std::string &data) const = 0;

        virtual void logInfo(const std::string &data) const = 0;

        virtual void logWarning(const std::string &data) const = 0;

        virtual void logError(const std::string &data) const = 0;
    };


    template<class T>
    void prettyLogCollection(const std::string& collectionName, T begin, T end, const ILogger& logger, LogLevel level){
        unsigned int count = 0;
        std::string out{};
        while (begin != end) {
            out = out + *begin + "; ";
            count++;
            begin++;
        }
        out = collectionName + " (total " + std::to_string(count) + ") { " + out + " }";
        logger.log(level, out);
    }
}