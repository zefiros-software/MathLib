#pragma once
#ifndef __GENERIC_MATRIX_DATA_H__
#define __GENERIC_MATRIX_DATA_H__

#include "math/types.h"
#include "math/config.h"
#include "math/scalar/mathf.h"

#include "math/scalar/primaryVectorBase.h"

#include <assert.h>

BEGIN_MATH_NAMESPACE

//
// Generic data construct
//
template< class TYPE, U32 ROWS, U32 COLS >
class GenericMatrixData
{
protected:
    PrimaryVectorBase< TYPE, COLS > mRows[ROWS];
};

template< class TYPE >
class GenericMatrixData< TYPE, 2, 2 >
{
public:

    union 
    {
        PrimaryVectorBase< 2, 2 > mRows[ROWS];
        struct { TYPE _11, _12, 
                      _21, _22; };
    };
};

template< class TYPE >
class GenericMatrixData< TYPE, 3, 3 >
{
public:

    union 
    {
        PrimaryVectorBase< 3, 3 > mRows[ROWS];
        struct { TYPE _11, _12, _13,
                      _21, _22, _23,
                      _31, _32, _33; };
    };
};

template< class TYPE >
class GenericMatrixData< TYPE, 4, 4 >
{
public:

    union 
    {
        PrimaryVectorBase< 3, 3 > mRows[ROWS];
        struct { TYPE _11, _12, _13, _14,
                      _21, _22, _23, _24,
                      _31, _32, _33, _34,
                      _41, _42, _43, _44; };
    };
};

END_MATH_NAMESPACE

#endif