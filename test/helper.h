#pragma once
#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

#include "math/types.h"

#define CONCATEXT( a, b ) a##b
#define CONCAT( a, b ) CONCATEXT( a, b )
#define P( prefix ) CONCAT( PREFIX, prefix )

template< class Type >
inline void ASSERT_REAL_EQ( Type q, Type r );

template<>
inline void ASSERT_REAL_EQ( F32 q, F32 r )
{
    ASSERT_FLOAT_EQ(r,q);
}

template<>
inline void ASSERT_REAL_EQ( F64 q, F64 r )
{
    ASSERT_DOUBLE_EQ(r,q);
}

#endif