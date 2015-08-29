#pragma once
#ifndef __ZEF_MALLOC_H__
#define __ZEF_MALLOC_H__

#include <cstddef>

// Based on
// http://jmabille.github.io/blog/2014/12/06/aligned-memory-allocator/

namespace LibStruct
{
    void *_InternalAlignedMalloc( size_t bytes, size_t alignment );

    void _InternalAlignedFree( void *ptr );

    void *ZefAlignedMalloc( size_t bytes, size_t alignment );

    void ZefAlignedFree( void *ptr );
}

#endif