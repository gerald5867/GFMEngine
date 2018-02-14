#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
#define _WIN32
#endif /* _WIN32 */
#if defined _WIN32 || defined _WIN64
#	define GFM_PLATFORM_WINDOWS 1
#else
#	define GFM_PLATFORM_WINDOWS 0
#endif//_WIN32

#if defined (unix) || defined (__unix) || defined (__unix__) || defined (__linux__) || defined (linux) || defined (__linux) || defined (__FreeBSD__)
#	define unix
#	define GFM_IS_UNIX 1
#else
#	define GFM_PLATFORM_UNIX 0
#endif// unix

#if defined (__FreeBSD__)
#	define GFM_PLTFORM_FREEBSD 1
#else
#	define GFM_PLTFORM_FREEBSD 0
#endif//__FreeBSD__

#if GFM_PLATFORM_WINDOWS
#	define		GFM_STRING(str) L##str
#else
#	define		GFM_STRING(str) str
#endif//GFM_PLATFORM_WINDOWS

#if defined(__ANDROID__) || defined(__android__) || defined (android)
#	define GFM_PLATFORM_ANDROID 1
#else
#	define GFM_PALTFORM_ANDROID 0
#endif//android

#if GFM_PLATFORM_WINDOWS
#	define GFM_CAT(str)   L#str
#	define GFM_WSTRING(cptr)  GFM_CAT(cptr)
#else
#	define GFM_CAT(str)   #str
#	define GFM_WSTRING(cptr)  GFM_CAT(cptr)
#endif//GFM_PLATFORM_WINDOWS

#endif // PLATFORM_H