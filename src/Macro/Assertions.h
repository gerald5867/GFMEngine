#pragma once
#ifndef _MSC_VER
	#include <assert.h>
#endif
#include "Debug.h"
#include "../GPUApi/ErrorHandler.h"
#include "../Utils/Logger.h"

#ifndef GFM_DEBUG_BREAK
#	ifdef _MSC_VER
#		define GFM_DEBUG_BREAK __debugbreak()
#	else
#		error Define GFM_DEBUG_BREAK !!
#	endif
#endif


#if GFM_IS_DEBUG_MODE 
#	ifndef GFM_DEBUG_ASSERT
#		define GFM_DEBUG_ASSERT(assertion, msgFormat, ...)											  \
			if(!(assertion)) {																		  \
				gfm::String message = gfm::String::Format(msgFormat, __VA_ARGS__);					  \
				gfm::utils::Logger::instance().AssertionFailure(gfm::String(__FUNCTION__).CStr(), GFM_WSTRING(__FILE__), GFM_WSTRING(__LINE__), message, GFM_WSTRING(assertion)); \
				GFM_DEBUG_BREAK; \
			} 
#	endif
#else
#	ifndef GFM_DEBUG_ASSERT
#		define GFM_DEBUG_ASSERT(assertion, failMessage, ...)
#	endif
#endif

#ifndef ASSERT_GL
#	if GFM_IS_DEBUG_MODE
#		define ASSERT_GL(x) \
		gfm::INTERNAL::gpu::ErrorHandler::Instance().ClearLastError(); \
		x; \
		if(!gfm::INTERNAL::gpu::ErrorHandler::Instance().LogCall(GFM_WSTRING(x), GFM_WSTRING(__FILE__), GFM_WSTRING(__LINE__))) \
		{ \
			gfm::utils::Logger::instance().Error(gfm::INTERNAL::gpu::ErrorHandler::Instance().GetLastError(), GFM_WSTRING(""), GFM_WSTRING(""), GFM_WSTRING("")); \
			GFM_DEBUG_BREAK; \
		}
#	else
#		define ASSERT_GL(x) x;
#	endif
#endif