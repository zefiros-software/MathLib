#pragma once 
#ifndef __SIMD_VECTOR_BASE_H__
#define __SIMD_VECTOR_BASE_H__

// big thanks to http://jmabille.github.io/blog/2014/10/10/writing-c-plus-plus-wrappers-for-simd-intrinsics-3/
// for the idea's on how to nicely wrap

template< typename VALUE_TYPE >
struct SimdTraits;

template< typename TYPE, typename VALUE_TYPE >
class SimdVectorBase
{
public:
    
    typedef typename SimdTraits<VALUE_TYPE>::value_type value_type;
    
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
    
    inline TYPE& operator+= ( const value_type& rhs )
    {
        (*this)() = (*this)() + TYPE( rhs );
        return (*this)();
    }
    
    inline TYPE& operator-= ( const TYPE& rhs )
    {
        (*this)() = (*this)() - rhs;
        return (*this)();
    } 
    
    inline TYPE& operator-= ( const value_type& rhs )
    {
        (*this)() = (*this)() - TYPE( rhs );
        return (*this)();
    }
    
    inline TYPE& operator*= ( const TYPE& rhs )
    {
        (*this)() = (*this)() * rhs;
        return (*this)();
    } 
    
    inline TYPE& operator*= ( const value_type& rhs )
    {
        (*this)() = (*this)() * TYPE( rhs );
        return (*this)();
    }
    
    inline TYPE& operator/= ( const TYPE& rhs )
    {
        (*this)() = (*this)() / rhs;
        return (*this)();
    } 
    
    inline TYPE& operator/= ( const value_type& rhs )
    {
        (*this)() = (*this)() / TYPE( rhs );
        return (*this)();
    }
    
    // Increment decrement
    inline TYPE& operator++()
    {
        (*this)() = (*this)() + value_type( 1 );
        return (*this)();
    }
    
    inline TYPE& operator--()
    {
        (*this)() = (*this)() - value_type( 1 );
        return (*this)();
    }

protected:

    inline SimdVectorBase(){}
    inline ~SimdVectorBase(){}
    	
    inline SimdVectorBase( const SimdVectorBase & ){}
    inline SimdVectorBase( const SimdVectorBase && ){}
    inline SimdVectorBase& operator= ( const SimdVectorBase & ){ return *this; }
};

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator+( const SimdVectorBase<TYPE,VALUE_TYPE> &lhs, const typename SimdTraits<TYPE>::value_type &rhs )
{
    return lhs() + TYPE( rhs );
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator+( const typename SimdTraits<TYPE>::value_type &lhs, const SimdVectorBase<TYPE,VALUE_TYPE> &rhs )
{
    return TYPE(lhs) + rhs();
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator-( const SimdVectorBase<TYPE,VALUE_TYPE> &lhs, const typename SimdTraits<TYPE>::value_type &rhs )
{
    return lhs() - TYPE( rhs );
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator-( const typename SimdTraits<TYPE>::value_type &lhs, const SimdVectorBase<TYPE,VALUE_TYPE> &rhs )
{
    return TYPE(lhs) - rhs();
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator*( const SimdVectorBase<TYPE,VALUE_TYPE> &lhs, const typename SimdTraits<TYPE>::value_type &rhs )
{
    return lhs() * TYPE( rhs );
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator*( const typename SimdTraits<TYPE>::value_type &lhs, const SimdVectorBase<TYPE,VALUE_TYPE> &rhs )
{
    return TYPE(lhs) * rhs();
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator/( const SimdVectorBase<TYPE,VALUE_TYPE> &lhs, const typename SimdTraits<TYPE>::value_type &rhs )
{
    return lhs() / TYPE( rhs );
}

template< typename TYPE, typename VALUE_TYPE >
inline SimdVectorBase<TYPE,VALUE_TYPE> operator/( const typename SimdTraits<TYPE>::value_type &lhs, const SimdVectorBase<TYPE,VALUE_TYPE> &rhs )
{
    return TYPE(lhs) / rhs();
}

#endif