#pragma once
#ifndef __VECTORIZE_H__
#define __VECTORIZE_H__

//align to half cache line
#define SIMD_ALIGNMENT 32

//
//define simd widths and support
//

// **********************
// based on the really nice article: http://jmabille.github.io/blog/2014/10/25/writing-c-plus-plus-wrappers-for-simd-intrinsics-5/
// Also inspired by https://bitbucket.org/eschnett/vecmathlib/
// **********************

//#ifdef _VECTORIZE

//
// Read what static instruction set we have available
//

#ifndef _DYNAMIC_SIMD_INSTRUCTION_SET

#ifdef __AVX2__

#define _TAKE_AVX_PATH

#include <immintrin.h>

#elif  __AVX__

#define _TAKE_AVX_PATH

#include <immintrin.h>

#elif __SSE4_2__

#define _TAKE_SSE_PATH

#include <nmmintrin.h>

#elif ( __SSE4_1__ || ( _M_IX86_FP == 2 ) )

#define _TAKE_SSE_PATH

#include <smmintrin.h>

#elif  __SSE3__

#define _TAKE_SSE_PATH

#include <pmmintrin.h>

#elif ( __SSE2__ || _M_X86 )

#define _TAKE_SSE_PATH

#include <emmintrin.h>

#elif  __SSE__

#define _TAKE_SSE_PATH

#include <xmmintrin.h>

#endif

// Fallback to scalar instructions
#ifdef _TAKE_AVX_PATH

#include "math/simd/avx.h"

#define SimdTraits AvxSimdTraits

#endif

#ifdef _TAKE_SSE_PATH

#include "math/simd/sse41.h"

#define SimdTraits SSE4_1SimdTraits


#endif

#if 0

#include "math/simd/fpu.h"

#define SimdTraits FpuSimdTraits


#endif //SIMD_INSTRUCTION_SET

#endif // _DYNAMIC_SIMD_INSTRUCTION_SET

#endif