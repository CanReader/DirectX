#include "Log.h"

namespace Messanger
{
    std::shared_ptr<spdlog::logger> Log::m_Logger;
    
    void Log::Test()
    {
        
        
    }

    void Log::Initialize()
    {
        spdlog::set_pattern("%^[%T] %s-%L: %v%$");
    	m_Logger = spdlog::stdout_color_mt("Directx");
    	m_Logger->set_level(spdlog::level::level_enum::debug);
    }
    
    void Log::ErrorBox(LPCSTR Message, LPCSTR Title)
    {
    	MessageBox(NULL,Message,Title,MB_OK | MB_ICONERROR);
    }
    
}