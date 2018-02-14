#include "Platform.h"
#include "Debug.h"

#if GFM_IS_DEBUG_MODE
#	define GFM_STATIC_CALL
#endif

#ifndef GFM_APICALL
#	if GFM_PLATFORM_WINDOWS
#		ifdef GFM_CORE_DLL
#			define GFM_APICALL //__declspec(dllexport)
#		elif defined(GFM_STATIC_CALL)
#			define GFM_APICALL
#		else
#			define GFM_APICALL //__declspec(dllimport)
#		endif//GFM_CORE_DLL
#	else
#		error "TODO: GFM_APICALL FOR OTHER PLATFORMS!"
#	endif//WINDOWS
#endif//GFM_APICALL