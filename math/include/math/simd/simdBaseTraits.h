#pragma once
#ifndef __SIMD_BASE_TRAITS_H__
#define __SIMD_BASE_TRAITS_H__

#include "math/types.h"

#include "math/util/memory/stackAlign.h"

#include <cstddef>

template< class VALUE_TYPE, class INT_TYPE, size_t LENGTH, size_t ALIGN >
struct BaseSimdTraits
{
    typedef VALUE_TYPE value_type;
    typedef INT_TYPE int_type;
    static const size_t width = LENGTH;
    static const size_t alignment = ALIGN;
    
    struct type_array
    {
        VALUE_TYPE  StackAlign( ALIGN ) values[LENGTH];
    };
    
    struct int_array
    {
        INT_TYPE StackAlign( ALIGN ) values[LENGTH];
    };
    
    struct bool_array
    {
        bool StackAlign( ALIGN ) values[LENGTH];
    };
};


template< typename VALUE_TYPE >
struct AvxSimdTraits;

template< typename VALUE_TYPE >
struct SSE4_1SimdTraits;

template< typename VALUE_TYPE >
struct FpuSimdTraits;


#endif