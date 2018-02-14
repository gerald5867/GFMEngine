#pragma once
#ifndef NO_INLINE_H
#define NO_INLINE_H

#if !defined(GFM_NO_INLINE)
# if defined(__clang___)
#  if __has_attribute(always_inline)
#   define GFM_NO_INLINE __attribute__((noinline)) __inline__
#  else
#    define GFM_NO_INLINE 
#  endif//HAS ATTRIBUTE
# elif defined(__GNUC__)
#  define GFM_NO_INLINE __attribute__((noinline)) __inline__
# elif defined(_MSC_VER)
#  define GFM_NO_INLINE __declspec(noinline)
# else
#  define GFM_NO_INLINE
# endif//__clang__
#endif//!GFM_BEST_INLINE

#endif //NO_INLINE_H