#pragma once 
#ifndef __SIMD_VECTOR_BASE_H__
#define __SIMD_VECTOR_BASE_H__

// big thanks to http://jmabille.github.io/blog/2014/10/10/writing-c-plus-plus-wrappers-for-simd-intrinsics-3/
// for the idea's on how to nicely wrap





/*
template<>
struct BaseSimdTraits<F64, 8 >
{
    typedef F64 value_type;
    static const size_t width = 8;
    
    struct TypeArray
    {
        value_type array[width];
    };
    
    struct BoolArray
    {
        bool array[width];
    };
};



template<>
struct BaseSimdTraits<F32>
{
    typedef F32 value_type;
};
*/

// Big thanks again http://jmabille.github.io/blog/2014/11/20/performance-considerations-about-simd-wrappers/
#define DEFINE_OPERATOR_PLUS_ASSIGN( RTYPE, ARG )\
    inline RTYPE& operator+=( const ARG &rhs )\
    {\
        *this = *this + RTYPE( rhs );\
        return *this;\
    }

#define DEFINE_OPERATOR_MIN_ASSIGN( RTYPE, ARG )\
    inline RTYPE& operator-=( const ARG &rhs )\
    {\
        *this = *this - RTYPE( rhs );\
        return *this;\
    }

#define DEFINE_OPERATOR_MUL_ASSIGN( RTYPE, ARG )\
    inline RTYPE& operator*=( const ARG &rhs )\
    {\
        *this = *this * RTYPE( rhs );\
        return *this;\
    }

#define DEFINE_OPERATOR_DIV_ASSIGN( RTYPE, ARG )\
    inline RTYPE& operator/=( const ARG &rhs )\
    {\
        *this = *this / RTYPE( rhs );\
        return *this;\
    }

#define DEFINE_OPERATOR_PLUSPLUS(RTYPE, ARG)\
    inline RTYPE& operator++()\
    {\
        (*this) += ARG( 1 );\
        return (*this);\
    }\
    inline RTYPE operator++(int)\
    {\
        RTYPE r = (*this);\
        (*this) += ARG( 1 );\
        return r;\
    }

#define DEFINE_OPERATOR_MINMIN(RTYPE, ARG)\
    inline RTYPE& operator--()\
    {\
        (*this) -= ARG( 1 );\
        return (*this);\
    }\
    inline RTYPE operator--(int)\
    {\
        RTYPE r = (*this);\
        (*this) -= ARG( 1 );\
        return r;\
    }

#define DEFINE_OPERATOR_PLUS( RTYPE, VALUE_TYPE )\
    inline RTYPE operator+( const RTYPE &lhs, const VALUE_TYPE rhs )\
    {\
        return lhs + RTYPE( rhs );\
    }\
    inline RTYPE operator+( const VALUE_TYPE lhs, const RTYPE &rhs )\
    {\
        return RTYPE(lhs) + rhs;\
    }

#define DEFINE_OPERATOR_MIN( RTYPE, VALUE_TYPE )\
    inline RTYPE operator-( const RTYPE &lhs, const VALUE_TYPE rhs )\
    {\
        return lhs - RTYPE( rhs );\
    }\
    inline RTYPE operator-( const VALUE_TYPE lhs, const RTYPE &rhs )\
    {\
        return RTYPE(lhs) - rhs;\
    }

#define DEFINE_OPERATOR_MUL( RTYPE, VALUE_TYPE )\
    inline RTYPE operator*( const RTYPE &lhs, const VALUE_TYPE rhs )\
    {\
        return lhs * RTYPE( rhs );\
    }\
    inline RTYPE operator*( const VALUE_TYPE lhs, const RTYPE &rhs )\
    {\
        return RTYPE(lhs) * rhs;\
    }

#define DEFINE_OPERATOR_DIV( RTYPE, VALUE_TYPE )\
    inline RTYPE operator/( const RTYPE &lhs, const VALUE_TYPE rhs )\
    {\
        return lhs / RTYPE( rhs );\
    }\
    inline RTYPE operator/( const VALUE_TYPE lhs, const RTYPE &rhs )\
    {\
        return RTYPE(lhs) / rhs;\
    }

/*
#define DEFINE_ASSIGNMENT_OPERATORS( VEC_TYPE, VALUE_TYPE )\
    DEFINE_OPERATOR_PLUS_ASSIGN( VEC_TYPE, VEC_TYPE );\
    DEFINE_OPERATOR_PLUS_ASSIGN( VEC_TYPE, VALUE_TYPE );\
    DEFINE_OPERATOR_MIN_ASSIGN( VEC_TYPE,VEC_TYPE );\
    DEFINE_OPERATOR_MIN_ASSIGN( VEC_TYPE,VALUE_TYPE );\
    DEFINE_OPERATOR_MUL_ASSIGN( VEC_TYPE,VEC_TYPE );\
    DEFINE_OPERATOR_MUL_ASSIGN( VEC_TYPE,VALUE_TYPE );\
    DEFINE_OPERATOR_DIV_ASSIGN( VEC_TYPE,VEC_TYPE );\
    DEFINE_OPERATOR_DIV_ASSIGN( VEC_TYPE,VALUE_TYPE );
*/

#define DEFINE_ASSIGNMENT_BASE_OPERATORS( VEC_TYPE, VALUE_TYPE )\
    DEFINE_OPERATOR_PLUS_ASSIGN( VEC_TYPE, VEC_TYPE );\
    DEFINE_OPERATOR_MIN_ASSIGN( VEC_TYPE,VEC_TYPE );\

#define DEFINE_ASSIGNMENT_EXT_OPERATORS( VEC_TYPE, VALUE_TYPE )\
    DEFINE_OPERATOR_MUL_ASSIGN( VEC_TYPE,VEC_TYPE );\
    DEFINE_OPERATOR_DIV_ASSIGN( VEC_TYPE,VEC_TYPE );\

#define DEFINE_INC_OPERATORS( VEC_TYPE, VALUE_TYPE )\
    DEFINE_OPERATOR_PLUSPLUS(VEC_TYPE,VEC_TYPE);\
    DEFINE_OPERATOR_MINMIN(VEC_TYPE,VEC_TYPE);

/*
#define DEFINE_COMMON_OPERATORS( VEC_TYPE, VALUE_TYPE )\
    DEFINE_OPERATOR_PLUS(VEC_TYPE,VALUE_TYPE);\
    DEFINE_OPERATOR_MIN(VEC_TYPE,VALUE_TYPE);\
    DEFINE_OPERATOR_MUL(VEC_TYPE,VALUE_TYPE);\
    DEFINE_OPERATOR_DIV(VEC_TYPE,VALUE_TYPE);
*/

#endif