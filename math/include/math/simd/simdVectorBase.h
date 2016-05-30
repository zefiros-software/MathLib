#pragma once 
#ifndef __SIMD_VECTOR_BASE_H__
#define __SIMD_VECTOR_BASE_H__

// big thanks to http://jmabille.github.io/blog/2014/10/10/writing-c-plus-plus-wrappers-for-simd-intrinsics-3/
// for the idea's on how to nicely wrap

template< class valueType >
struct BaseSimdTraits;

template<>
struct BaseSimdTraits<F64>
{
    typedef F64 valueType;
};

template<>
struct BaseSimdTraits<F32>
{
    typedef F32 valueType;
};


template< typename TYPE, typename VALUE_TYPE >
class SimdVectorBase
{
public:
    
    typedef typename BaseSimdTraits<VALUE_TYPE>::valueType valueType;
    
    //downcast
    inline TYPE& operator()()
    {
        return *static_cast< TYPE* >( this );
    }
    
    inline const TYPE& operator()() const
    {
        return *static_cast< const TYPE* >( this );
    }
    
    //
    // handle all self operators here
    //
    inline TYPE& operator+= ( const TYPE& rhs )
    {
        (*this)() = (*this)() + rhs;
        return (*this)();
    } 
    
    inline TYPE& operator+= ( const valueType& rhs )
    {
        (*this)() = (*this)() + TYPE( rhs );
        return (*this)();
    }
    
    inline TYPE& operator-= ( const TYPE& rhs )
    {
        (*this)() = (*this)() - rhs;
        return (*this)();
    } 
    
    inline TYPE& operator-= ( const valueType& rhs )
    {
        (*this)() = (*this)() - TYPE( rhs );
        return (*this)();
    }
    
    inline TYPE& operator*= ( const TYPE& rhs )
    {
        (*this)() = (*this)() * rhs;
        return (*this)();
    } 
    
    inline TYPE& operator*= ( const valueType& rhs )
    {
        (*this)() = (*this)() * TYPE( rhs );
        return (*this)();
    }
    
    inline TYPE& operator/= ( const TYPE& rhs )
    {
        (*this)() = (*this)() / rhs;
        return (*this)();
    } 
    
    inline TYPE& operator/= ( const valueType& rhs )
    {
        (*this)() = (*this)() / TYPE( rhs );
        return (*this)();
    }
    
    // Increment decrement
    inline TYPE& operator++()
    {
        (*this)() += valueType( 1 );
        return (*this)();
    }
    
    inline TYPE& operator--()
    {
        (*this)() -= valueType( 1 );
        return (*this)();
    }

protected:

    inline SimdVectorBase(){}
    inline ~SimdVectorBase(){}
    	
    inline SimdVectorBase( const SimdVectorBase & ){}
    inline SimdVectorBase( const SimdVectorBase && ){}
    inline SimdVectorBase& operator= ( const SimdVectorBase & ){ return *this; }
};

template< typename TYPE >
inline TYPE operator+( const TYPE &lhs, const typename TYPE::valueType &rhs )
{
    return lhs() + TYPE( rhs );
}

template< typename TYPE >
inline TYPE operator+( const typename TYPE::valueType &lhs, const TYPE &rhs )
{
    return TYPE(lhs) + rhs();
}

template< typename TYPE >
inline TYPE operator-( const TYPE &lhs, const typename TYPE::valueType &rhs )
{
    return lhs() - TYPE( rhs );
}

template< typename TYPE >
inline TYPE operator-( const typename TYPE::valueType &lhs, const TYPE &rhs )
{
    return TYPE(lhs) - rhs();
}

template< typename TYPE >
inline TYPE operator*( const TYPE &lhs, const typename TYPE::valueType &rhs )
{
    return lhs() * TYPE( rhs );
}

template< typename TYPE >
inline TYPE operator*( const typename TYPE::valueType &lhs, const TYPE &rhs )
{
    return TYPE(lhs) * rhs();
}

template< typename TYPE >
inline TYPE operator/( const TYPE &lhs, const typename TYPE::valueType &rhs )
{
    return lhs() / TYPE( rhs );
}

template< typename TYPE >
inline TYPE operator/( const typename TYPE::valueType &lhs, const TYPE &rhs )
{
    return TYPE(lhs) / rhs();
}

#endif