#pragma once
#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

#define CONCATEXT( a, b ) a##b
#define CONCAT( a, b ) CONCATEXT( a, b )
#define P( prefix ) CONCAT( PREFIX, prefix )

#endif