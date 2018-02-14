#pragma once
#include "Debug.h"
#ifndef BEST_INLINE_H
#define BEST_INLINE_H

#if !defined(GFM_BEST_INLINE)
# if defined(__clang___)
#  if __has_attribute(always_inline)
#   define GFM_BEST_INLINE __attribute__((always_inline)) __inline__
#  else
#    define GFM_BEST_INLINE inline
#  endif//HAS ATTRIBUTE
# elif defined(__GNUC__)
#  define GFM_BEST_INLINE __attribute__((always_inline)) __inline__
# elif defined(_MSC_VER)
#  define GFM_BEST_INLINE __forceinline
# else
#  define GFM_BEST_INLINE inline
# endif//__clang__
#endif//!GFM_BEST_INLINE

#endif //BEST_INLINE_H