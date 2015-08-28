#pragma once 
#ifndef __FP_VECTOR_H__
#define __FP_VECTOR_H__

#include "genericVector.h"

template< class TYPE, U32 N >
class FloatingPointVector : public GenericVector< TYPE, N >
{
public:

    // Internal intrinsics
    inline TYPE Distance( const FloatingPointVector< TYPE, N > &v ) const
    {
        return ( *this - v ).Length();
    }
    
    inline TYPE Length() const
    {
        return Mathf::Sqrt( this->Length2() );
    }
    
    inline GenericVector< TYPE, N > SafeNormalise()
    {
        const GenericVector< TYPE, N > absv = this->Absolute();
        U8 max = absv.MaxAxis();
    
        if ( absv.mValues[max] > 0 )
        {
            assert( absv[max] != 0.0f );
            assert( Length() != 0.0f );
    
            *this /= absv.mValues[max];
            return *this /= Length();
        }
    
        this->SetValue( 0, 1.0f );
        this->SetValue( 1, 0.0f );
        this->SetValue( 2, 0.0f );
        
        return *this;
    }
    
    inline GenericVector< TYPE, N > Normalise()
    {
        assert( Length() != 0.0f );
    
        return *this /= Length();
    }
    
    inline GenericVector< TYPE, N > Lerp( const GenericVector< TYPE, N > &v, const TYPE t ) const
    {
        GenericVector< TYPE, N > newVec;
        
        for ( U32 i=0; i < N; ++i )
        {
            newVec.SetValue( i,  Mathf::Lerp( this->mValues[i], v.mValues[i], t ) ); 
        }
        
        return newVec;
    }
    
    inline GenericVector< TYPE, N > Slerp( const GenericVector< TYPE, N > &v, const TYPE t ) const
    {
        TYPE dotp = Dot( v );
    
        // Make sure the floating point accuracy doesn't
        // crash our program
        Mathf::Clamp( dotp , -1.0f, 1.0f );
    
        TYPE theta = Mathf::Acos( dotp ) * t;
        GenericVector< TYPE, N > relative = v - *this * dotp;
        relative.Normalise();
    
        return *this * Mathf::Cos( theta ) + relative * Mathf::Sin( theta );
    }
    
    inline GenericVector< TYPE, N > Nlerp( const GenericVector< TYPE, N > &v, const TYPE t ) const
    {
        return Lerp( v, t ).Normalise();
    }
    
    inline TYPE Angle( const GenericVector< TYPE, N > &v ) const
    {
        TYPE s = Mathf::Sqrt( this->Length2() * v.Length2() );
    
        assert( s != 0.0f );
    
        return Mathf::Acos( Mathf::Clamp( Dot( v ) / s, -1.0f, 1.0f ) );
    }
    
};

#endif