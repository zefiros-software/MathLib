#include "malloc.h"

#include <stdlib.h>

#include "common/util.h"

#include "math/simd/vectorize.h"

void *LibStruct::_InternalAlignedMalloc( size_t bytes, size_t alignment )
{
    size_t offset = alignment; //+ sizeof( size_t );

    void *ptr = malloc( bytes + offset );

    if ( !ptr )
    {
        return nullptr;
    }

    //offset and truncate under alignment
    void **ptr2 = ( void ** )( ( ( size_t )( ptr ) & ~( alignment - 1 ) ) + offset );

    //store malloc address above the requested memory
    ptr2[-1] = ptr;

    return ptr2;
}

void LibStruct::_InternalAlignedFree( void *ptr )
{
    if ( ptr != 0 )
    {
        free( *( ( void ** )( ptr ) - 1 ) );
    }
}

void *LibStruct::ZefAlignedMalloc( size_t bytes, size_t alignment )
{

#if SIMD_INSTRUCTION_SET > 0
    return _mm_malloc( bytes, alignment );
#else
    return _InternalAlignedMalloc( bytes, alignment );
#endif
}

void LibStruct::ZefAlignedFree( void *ptr )
{
#if SIMD_INSTRUCTION_SET > 0
    return _mm_free( ptr );
#else
    return _InternalAlignedFree( ptr );
#endif
}
