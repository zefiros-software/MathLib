#pragma once
#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

#define CONCATEXT( a, b ) a##b
#define CONCAT( a, b ) CONCATEXT( a, b )
#define P( prefix ) CONCAT( PREFIX, prefix )

#ifdef REAL_PRECISION_SINGLE
#define ASSERT_REAL_EQ(x,y) ASSERT_FLOAT_EQ(x,y)
#elif REAL_PRECISION_DOUBLE
#define ASSERT_REAL_EQ(x,y) ASSERT_DOUBLE_EQ(x,y)
#else
#error REAL EQ handling not defined
#endif

#endif