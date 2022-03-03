#ifndef _LOG_H_
#define _LOG_H_

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Messanger
{
#define DX_TRACE(text) SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::trace, text)
#define DX_INFO(text)  SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::info, text)
#define DX_DEBUG(text) SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::debug,  text)
#define DX_WARN(text)  SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::warn, text)
#define DX_ERROR(text) SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::err,  text)
#define DX_FATAL(text) SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::critical,  text)

    class Log
    {
    public:
        static void Test();
    	static void Initialize();
    	static void ErrorBox(LPCSTR Message, LPCSTR Title);
    	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }
    
    private:
    	static std::shared_ptr<spdlog::logger> m_Logger;
    
    };
    
}
#endif // !_LOG_H_