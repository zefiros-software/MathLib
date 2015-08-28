#pragma once
#ifndef __GENERIC_VECTOR_H__
#define __GENERIC_VECTOR_H__

#include "types.h"
#include "config.h"

#include "scalar/mathf.h"

#include <assert.h>


BEGIN_MATH_NAMESPACE

//
// Generic data construct
//
template< class TYPE, U32 N >
class GenericVectorData
{
protected:
    TYPE mValues[N];  
};

//specific unions
template< class TYPE >
class GenericVectorData< TYPE, 2 >
{
public:

    inline void SetX( const TYPE x )
    {
        mValues[0] = x;
    }
    
    inline TYPE GetX() const
    {
        return mValues[0];
    }
    
    inline void SetY( const TYPE y )
    {
        mValues[1] = y;
    }
    
    inline TYPE GetY() const
    {
        return mValues[1];
    }
    
    inline void SetValues( const TYPE &x, const TYPE &y )
    {
        mValues[0] = x;
        mValues[1] = y;
    }
    
    union 
    {
        TYPE mValues[2];
        struct { TYPE x, y; };
        struct { TYPE r, g; };
    };
};

template< class TYPE>
class GenericVectorData< TYPE, 3 >
{
public:
    
    inline void SetX( const TYPE x )
    {
        mValues[0] = x;
    }
    
    inline TYPE GetX() const
    {
        return mValues[0];
    }
    
    inline void SetY( const TYPE y )
    {
        mValues[1] = y;
    }
    
    inline TYPE GetY() const
    {
        return mValues[1];
    }
    
    inline void SetZ( const TYPE z )
    {
        mValues[2] = z;
    }
    
    inline TYPE GetZ() const
    {
        return mValues[2];
    }
    
    inline void SetValues( const TYPE &x, const TYPE &y, const TYPE &z )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
    }
    
    union 
    {
        TYPE mValues[3];
        struct { TYPE x, y, z; };
        struct { TYPE r, g, b; };
        GenericVectorData< TYPE,2 > xy;
        GenericVectorData< TYPE,2 > rg;
    };
};

template< class TYPE>
class GenericVectorData< TYPE, 4 >
{
public:

    inline void SetX( const TYPE x )
    {
        mValues[0] = x;
    }
    
    inline TYPE GetX() const
    {
        return mValues[0];
    }
    
    inline void SetY( const TYPE y )
    {
        mValues[1] = y;
    }
    
    inline TYPE GetY() const
    {
        return mValues[1];
    }
    
    inline void SetZ( const TYPE z )
    {
        mValues[2] = z;
    }
    
    inline TYPE GetZ() const
    {
        return mValues[2];
    }
    
    inline void SetW( const TYPE w )
    {
        mValues[3] = w;
    }
    
    inline TYPE GetW() const
    {
        return mValues[3];
    }
    
    inline void SetValues( const TYPE &x, const TYPE &y, const TYPE &z, const TYPE &w )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }
    
    union 
    {
        TYPE mValues[4];
        struct { TYPE x, y, z, w; };
        struct { TYPE r, g, b, a; };
        GenericVectorData< TYPE,2 > xy;
        GenericVectorData< TYPE,2 > rg;
        GenericVectorData< TYPE,3 > xyz;
        GenericVectorData< TYPE,3 > rgb;
    };
};

template< class TYPE, U32 N >
class GenericVector : public GenericVectorData< TYPE, N >
{
    friend GenericVector< TYPE, N > operator+( const GenericVector< TYPE, N > &, const GenericVector< TYPE, N > & );
    friend GenericVector< TYPE, N > operator*( const GenericVector< TYPE, N > &, const GenericVector< TYPE, N > & );
    friend GenericVector< TYPE, N > operator-( const GenericVector< TYPE, N > &, const GenericVector< TYPE, N > & );
    friend GenericVector< TYPE, N > operator-( const GenericVector< TYPE, N > & );
    friend GenericVector< TYPE, N > operator*( const GenericVector< TYPE, N > &, const TYPE );
    friend GenericVector< TYPE, N > operator*( const TYPE , const GenericVector< TYPE, N > & );
    friend GenericVector< TYPE, N > operator/( const GenericVector< TYPE, N > &, const TYPE );
    friend GenericVector< TYPE, N > operator/( const GenericVector< TYPE, N > &, const GenericVector< TYPE, N > & );
    
public:
  
    // Accessors
    inline const TYPE & operator[]( U32 i ) const
    {
        assert( i < N );
        
        return this->mValues[i];
    }
    
    inline TYPE &operator[]( U32 i )
    {
        assert( i < N );
        
        return this->mValues[i];
    }
    
    // Self operators
    inline GenericVector< TYPE, N > &operator+=( const GenericVector< TYPE, N > &v )
    {
        for ( U32 i=0; i < N; ++i )
        {
            this->mValues[i] += v[i];
        }
     
        return *this;
    }
    
    inline GenericVector< TYPE, N > &operator /= ( const TYPE s )
    {
        assert( s != 0.0f );
    
        for ( U32 i=0; i < N; ++i )
        {
            this->mValues[i] /= s;
        }
    
        return *this;
    }
    
    inline GenericVector< TYPE, N > &operator *= ( const TYPE s )
    { 
        for ( U32 i=0; i < N; ++i )
        {
            this->mValues[i] *= s;
        }
    
        return *this;
    }
    
    // Equality
    inline bool operator==( const GenericVector< TYPE, N > &other ) const
    {
        bool result = true;
        
        for ( U32 i=0; i < N; ++i )
        {
            result &= Mathf::Equal( this->mValues[i], other.mValues[i] );       
        }
        
        return result;
    }
    
    inline bool operator!=( const GenericVector< TYPE, N > &other ) const
    {
        return !( *this == other );
    }
    
    // Internal intrinsics
    inline TYPE Dot( const GenericVector< TYPE, N > &v ) const
    {
        TYPE result = this->mValues[0] * v.mValues[0];
        
        for ( U32 i=1; i < N; ++i )
        {
            result += this->mValues[i] * v.mValues[i];
        }
        
        return  result;
    }
    
    inline TYPE Length2() const
    {
        return Dot( *this );
    }
    
    inline TYPE Distance2( const GenericVector< TYPE, N > &v ) const
    {
        return ( *this - v ).Length2();
    }
 
    inline void SetValue( U32 axis, TYPE val )
    {
        this->mValues[axis] = val;
    }
    
    inline GenericVector< TYPE, N > Absolute() const
    {
        GenericVector< TYPE, N > newVec;
        
        for ( U32 i=0; i < N; ++i )
        {
            newVec.SetValue( i, Mathf::Abs( this->mValues[i] ));
        }
        
        return newVec;
    }
    
    inline U8 MinAxis() const
    {
        U8 axis = 0;
        TYPE val = this->mValues[0];
        
        for ( U8 i=1; i < N; ++i )
        {
            const TYPE considerate = this->mValues[i];
            
            if ( considerate < val )
            {
                val = considerate;
                axis = i;
            }
        }
        
        return axis;
    }
    
    inline U8 MaxAxis() const
    {
        U8 axis = 0;
        TYPE val = this->mValues[0];
        
        for ( U8 i=1; i < N; ++i )
        {
            const TYPE considerate = this->mValues[i];
            
            if ( considerate > val )
            {
                val = considerate;
                axis = i;
            }
        }
        
        return axis;
    }
    
    inline void SetZero()
    {
        for ( U32 i=0; i < N; ++i )
        {
            SetValue( i, 0 );   
        }
    }
    
    inline bool IsZero() const
    {
        bool result = true;
        
        for ( U32 i=0; i < N; ++i )
        {
            result &= ( this->mValues[i] == 0 );
        }
        
        return result;
    }
    
    inline bool IsFuzzyZero() const
    {
        return Length2() < Mathf::GetEpsilon();
    }
    
    inline void Clear()
    {
        SetZero();
    }
};


// Vec 3 only:
// Rotate axis angle + Cross
template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator+( const GenericVector< TYPE, N > &v1, const GenericVector< TYPE, N > &v2 )
{
    GenericVector< TYPE, N > newVec;
    
    for ( U32 i=0; i < N; ++i )
    {
        newVec[i] = v1[i] + v2[i];
    }
    
    return newVec;
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator*( const GenericVector< TYPE, N > &v1, const GenericVector< TYPE, N > &v2 )
{
    GenericVector< TYPE, N > newVec;
    
    for ( U32 i=0; i < N; ++i )
    {
        newVec[i] = v1[i] * v2[i];
    }
    
    return newVec;
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator-( const GenericVector< TYPE, N > &v1, const GenericVector< TYPE, N > &v2 )
{
    GenericVector< TYPE, N > newVec;
    
    for ( U32 i=0; i < N; ++i )
    {
        newVec[i] = v1[i] - v2[i];
    }
    
    return newVec;
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator-( const GenericVector< TYPE, N > &v )
{
    GenericVector< TYPE, N > newVec;
    
    for ( U32 i=0; i < N; ++i )
    {
        newVec[i] = -v[i];
    }
    
    return newVec;
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator*( const GenericVector< TYPE, N > &v, const TYPE s )
{
    GenericVector< TYPE, N > newVec;
    
    for ( U32 i=0; i < N; ++i )
    {
        newVec[i] = v[i] * s;
    }
    
    return newVec;
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator*( TYPE s, const GenericVector< TYPE, N > &v )
{
    return v * s;
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator/( const GenericVector< TYPE, N > &v, TYPE s )
{
    assert( s != 0.0f );
    return v * ( Real( 1.0 ) / s );
}

template< class TYPE, U32 N >
inline GenericVector< TYPE, N > operator/( const GenericVector< TYPE, N > &v1, const GenericVector< TYPE, N > &v2 )
{
    GenericVector< TYPE, N > newVec;
    
    for ( U32 i=0; i < N; ++i )
    {
        newVec[i] = v1[i] / v2[i];
    }
    
    return newVec;
}


END_MATH_NAMESPACE

#endif