//
// Created by Asus on 6/22/2024.
//

#include <iostream>
#include <chrono>
#include "Logger.h"

void Log::Logger::LogInfo(const std::string &data) const {
    std::cout << "[UTC " << std::chrono::utc_clock::now() << ']' << " (Info) : " << data << std::endl;
}

void Log::Logger::LogError(const std::string &data) const {
    std::cerr << "[UTC " << std::chrono::utc_clock::now() << ']' << " (Error) : " << data << std::endl;
}

void Log::Logger::LogWarning(const std::string &data) const {
    std::cout << "[UTC " << std::chrono::utc_clock::now() << ']' << " (Warning) : " << data << std::endl;
}
