#pragma once

#include "spdlog/spdlog.h"

namespace Creator
{
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}


//------------------------------------------------------------------------------------
// ---------------------------------- CORE LOGGING ----------------------------------

#define CREATOR_ERROR_LOG(...)  ::Creator::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CREATOR_WARN_LOG(...)   ::Creator::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CREATOR_INFO_LOG(...)   ::Creator::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CREATOR_TRACE_LOG(...)  ::Creator::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CREATOR_FATAL_LOG(...)  ::Creator::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// --------------------------------- CLIENT LOGGING ----------------------------------

#define CLIENT_ERROR_LOG(...)  ::Creator::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_WARN_LOG(...)   ::Creator::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_INFO_LOG(...)   ::Creator::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_TRACE_LOG(...)  ::Creator::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_FATAL_LOG(...)  ::Creator::Log::GetClientLogger()->fatal(__VA_ARGS__)

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------