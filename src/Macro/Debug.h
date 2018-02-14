#ifndef DEBUG_H
#define DEBUG_H

#ifndef GFM_IS_DEBUG_MODE
#	if defined (_DEBUG) || defined(DEBUG) || defined(__DEBUG) || defined (__DEBUG__) || defined (DEBUG_) || defined (DEBUG__) || defined (_DEBUG_)
#		define GFM_IS_DEBUG_MODE 1
#	elif defined NDEBUG
#		define GFM_IS_DEBUG_MODE 0
#	else
#		define GFM_IS_DEBUG_MODE 0
#	endif
#endif

#endif//DEBUG_H