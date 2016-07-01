//
//  simdHelper.h
//  math
//
//  Created by koen visscher on 6/27/16.
//
//

#ifndef simdHelper_h
#define simdHelper_h

#include "math/types.h"

#include <cstddef>
#include <cstring>

namespace SimdHelper
{
    template< typename VectorType, typename StorageType, typename ValueType >
    ValueType ExtractValueFromVector( const StorageType &storage, U32 location );
    
    template< typename VectorType, typename StorageType, typename ValueType >
    void SetValueInVector( const StorageType &storage, U32 location, ValueType val );
}


/* Inspired by part
 
 Copyright (c) 2012, 2013 Erik Schnetter <eschnetter@gmail.com>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


template< typename VectorType, typename StorageType, typename ValueType >
ValueType SimdHelper::ExtractValueFromVector( const StorageType &storage, U32 location )
{
    ValueType val;
    
    const size_t typeSize = sizeof( ValueType );
    
    memcpy(&val, ((const byte *)&storage) + typeSize * location, typeSize );
    
    return val;
}

template< typename VectorType, typename StorageType, typename ValueType >
void SimdHelper::SetValueInVector( const StorageType &storage, U32 location, ValueType val )
{
    const size_t typeSize = sizeof( ValueType );
    
    memcpy(((byte *)&storage) + typeSize * location, &val, typeSize );
}

#endif /* simdHelper_h */
