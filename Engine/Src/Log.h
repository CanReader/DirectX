#ifndef _LOG_H_
#define _LOG_H_

#include <memory>
#include <iostream>

namespace Messanger
{
#define DX_TRACE(text) std::cout<<"anan";//SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::trace, text)
#define DX_INFO(text)  std::cout<<"anan";//SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::info, text)
#define DX_DEBUG(text) std::cout<<"anan";//SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::debug,  text)
#define DX_WARN(text)  std::cout<<"anan";//SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::warn, text)
#define DX_ERROR(text) std::cout<<"anan";//SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::err,  text)
#define DX_FATAL(text) std::cout<<"anan";//SPDLOG_LOGGER_CALL(Messanger::Log::GetLogger(), spdlog::level::critical,  text)

    class __declspec(dllexport) Log
    {
    public:
    	static void Initialize();
    //	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }
    
    private:
  //  	static std::shared_ptr<spdlog::logger> m_Logger;
    
    };
    
}
#endif // !_LOG_H_