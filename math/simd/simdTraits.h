#pragma once
#ifndef __SIMD_TRAITS_H__
#define __SIMD_TRAITS_H__

#include "vectorize.h"

class ScalarVec4f;

// Fallback to scalar instructions
// does not exist FOR DEBUG
#if SIMD_INSTRUCTION_SET >= 6

#include "simd/avx/avx_vec8f.h"
#include "simd/avx/avx_vec4d.h"

#elif SIMD_INSTRUCTION_SET >= 4

#include "simd/sse4_1/sse4_1_vec4f.h"

#else

#include "simd/scalarFallback/scalar_vec4f.h"
#include "simd/scalarFallback/scalar_vec4d.h"

#endif //SIMD_INSTRUCTION_SET

#endif