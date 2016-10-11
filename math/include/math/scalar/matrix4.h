/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016 Koen Visscher, Paul Visscher and individual contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @endcond
 */

#pragma once
#ifndef __ENGINE_MATRIX4_H__
#define __ENGINE_MATRIX4_H__

#include "math/scalar/matrix3.h"
#include "math/scalar/vec4.h"

#include <assert.h>

template< class Number >
class Matrix4;

typedef Matrix3< F32 > Matrix4f;
typedef Matrix3< F64 > Matrix4d;

#ifndef REAL_UNDEFINED
typedef Matrix3< Real > Matrix4r;
#endif

template< class Number >
class Matrix4
{
    friend Matrix4 operator+( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator-( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator*( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator*( const Matrix4 &m, const Number s );
    friend Vec4< Number > operator*( const Matrix4 &m, const Vec4< Number > &v );

public:

    inline Matrix4()
    {
    }
    
    inline Matrix4( const Number a11, const Number a12, const Number a13, const Number a14, const Number a21, const Number a22,
                     const Number a23, const Number a24, const Number a31, const Number a32, const Number a33, const Number a34, const Number a41, const Number a42,
                     const Number a43, const Number a44 )
    {
        SetValue( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44 );
    }
    
    inline Matrix4( const Vec4< Number > &v1, const Vec4< Number > &v2, const Vec4< Number > &v3, const Vec4< Number > &v4 )
    {
        mValues[0] = v1;
        mValues[1] = v2;
        mValues[2] = v3;
        mValues[3] = v4;
    }
    
    inline Matrix4( const Matrix4 &other )
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
        mValues[3] = other.mValues[3];
    }
    
    inline Matrix4 &operator=( const Matrix4 &m )
    {
        mValues[0] = m.mValues[0];
        mValues[1] = m.mValues[1];
        mValues[2] = m.mValues[2];
        mValues[3] = m.mValues[3];
        
        return *this;
    }
    
    inline Matrix4 &operator*=( const Matrix4 &m )
    {
        SetValue( m.Dotx( mValues[0] ), m.Doty( mValues[0] ), m.Dotz( mValues[0] ), m.Dotw( mValues[0] ),
                 m.Dotx( mValues[1] ), m.Doty( mValues[1] ), m.Dotz( mValues[1] ), m.Dotw( mValues[1] ),
                 m.Dotx( mValues[2] ), m.Doty( mValues[2] ), m.Dotz( mValues[2] ), m.Dotw( mValues[2] ),
                 m.Dotx( mValues[3] ), m.Doty( mValues[3] ), m.Dotz( mValues[3] ), m.Dotw( mValues[3] ) );
        
        return *this;
    }
    
    inline Matrix4 &operator+=( const Matrix4 &m )
    {
        SetValue( mValues[0][0] + m.mValues[0][0], mValues[0][1] + m.mValues[0][1], mValues[0][2] + m.mValues[0][2],
                 mValues[0][3] + m.mValues[0][3],
                 mValues[1][0] + m.mValues[1][0], mValues[1][1] + m.mValues[1][1], mValues[1][2] + m.mValues[1][2],
                 mValues[1][3] + m.mValues[1][3],
                 mValues[2][0] + m.mValues[2][0], mValues[2][1] + m.mValues[2][1], mValues[2][2] + m.mValues[2][2],
                 mValues[2][3] + m.mValues[2][3],
                 mValues[2][0] + m.mValues[3][0], mValues[3][1] + m.mValues[3][1], mValues[3][2] + m.mValues[3][2],
                 mValues[2][3] + m.mValues[3][3] );
        
        return *this;
    }
    
    inline Matrix4 &operator-=( const Matrix4 &m )
    {
        SetValue( mValues[0][0] - m.mValues[0][0], mValues[0][1] - m.mValues[0][1], mValues[0][2] - m.mValues[0][2],
                 mValues[0][3] - m.mValues[0][3],
                 mValues[1][0] - m.mValues[1][0], mValues[1][1] - m.mValues[1][1], mValues[1][2] - m.mValues[1][2],
                 mValues[1][3] - m.mValues[1][3],
                 mValues[2][0] - m.mValues[2][0], mValues[2][1] - m.mValues[2][1], mValues[2][2] - m.mValues[2][2],
                 mValues[2][3] - m.mValues[2][3],
                 mValues[3][0] - m.mValues[3][0], mValues[3][1] - m.mValues[3][1], mValues[3][2] - m.mValues[3][2],
                 mValues[3][3] - m.mValues[3][3] );
        
        return *this;
    }
    
    inline bool operator==( const Matrix4 &m ) const
    {
        return mValues[0] == m.mValues[0] && mValues[1] == m.mValues[1] && mValues[2] == m.mValues[2] &&
        mValues[3] == m.mValues[3];
    }
    
    inline bool operator!=( const Matrix4 &m ) const
    {
        return !( *this == m );
    }
    
    inline void SetColumn( const U8 column, const Vec4< Number > &v )
    {
        mValues[0][column] = v[0];
        mValues[1][column] = v[1];
        mValues[2][column] = v[2];
        mValues[3][column] = v[3];
    }
    
    inline Vec4< Number > GetColumn( const U8 column ) const
    {
        return Vec4< Number >( mValues[0][column], mValues[1][column], mValues[2][column], mValues[3][column] );
    }
    
    inline void SetRow( const U8 row, const Vec4< Number > &v )
    {
        mValues[row] = v;
    }
    
    inline Vec4< Number > GetRow( const U8 row ) const
    {
        return mValues[row];
    }
    
    inline Matrix4 Scale( const Vec4< Number > &v ) const
    {
        return Matrix4( mValues[0][0] * v[0], mValues[0][1] * v[1], mValues[0][2] * v[2], mValues[0][3] * v[3],
                       mValues[1][0] * v[0], mValues[1][1] * v[1], mValues[1][2] * v[2], mValues[1][3] * v[3],
                       mValues[2][0] * v[0], mValues[2][1] * v[1], mValues[2][2] * v[2], mValues[2][3] * v[3],
                       mValues[3][0] * v[0], mValues[3][1] * v[1], mValues[3][2] * v[2], mValues[3][3] * v[3] );
    }
    
    inline Matrix4 GetTranspose() const
    {
        return Matrix4( mValues[0][0], mValues[1][0], mValues[2][0], mValues[3][0],
                       mValues[0][1], mValues[1][1], mValues[2][1], mValues[3][1],
                       mValues[0][2], mValues[1][2], mValues[2][2], mValues[3][2],
                       mValues[0][3], mValues[1][3], mValues[2][3], mValues[3][3] );
    }
    
    inline Matrix4 GetAbsolute() const
    {
        return Matrix4( Mathf::Abs( mValues[0][0] ), Mathf::Abs( mValues[0][1] ), Mathf::Abs( mValues[0][2] ),
                       Mathf::Abs( mValues[0][3] ),
                       Mathf::Abs( mValues[1][0] ), Mathf::Abs( mValues[1][1] ), Mathf::Abs( mValues[1][2] ),
                       Mathf::Abs( mValues[1][3] ),
                       Mathf::Abs( mValues[2][0] ), Mathf::Abs( mValues[2][1] ), Mathf::Abs( mValues[2][2] ),
                       Mathf::Abs( mValues[2][3] ),
                       Mathf::Abs( mValues[3][0] ), Mathf::Abs( mValues[3][1] ), Mathf::Abs( mValues[3][2] ),
                       Mathf::Abs( mValues[3][3] ) );
    }
    
    inline Matrix4 GetAdjoint() const
    {
        return Matrix4( GetCofactor( 0, 0 ), GetCofactor( 0, 1 ), GetCofactor( 0, 2 ), GetCofactor( 0, 3 ),
                       GetCofactor( 1, 0 ), GetCofactor( 1, 1 ), GetCofactor( 1, 2 ), GetCofactor( 1, 3 ),
                       GetCofactor( 2, 0 ), GetCofactor( 2, 1 ), GetCofactor( 2, 2 ), GetCofactor( 2, 3 ),
                       GetCofactor( 3, 0 ), GetCofactor( 3, 1 ), GetCofactor( 3, 2 ), GetCofactor( 3, 3 ) );
    }
    
    inline Matrix4 GetInverse() const
    {
        const Number det = GetDeterminant();
        
        assert( det != 0.0f );
        
        const Number s = 1.0f / det;
        
        Matrix4 adjoint  =  GetAdjoint();
        Matrix4 adjointT = adjoint.GetTranspose();
        
        return adjointT * s;
    }
    
    inline void SetIdentity()
    {
        SetValue( 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f );
    }
    
    inline Number GetCofactor( const U8 row, const U8 column ) const
    {
        Number values[9];
        
        U8 valIndex = 0;
        
        for ( U8 i = 0; i < 4; ++i )
        {
            for ( U8 j = 0; j < 4 && i != row; ++j )
            {
                if ( j == column )
                {
                    continue;
                }
                
                values[valIndex++] = mValues[i][j];
            }
        }
        
        Matrix3< Number > localMat( values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8] );
        
        Number cof = localMat.GetDeterminant();
        
        if ( ( ( column + row ) & 1 ) == 1 )
        {
            cof *= -1;
        }
        
        return cof;
    }
    
    inline Number GetDeterminant() const
    {
        return  mValues[0][0] * GetCofactor( 0, 0 ) +
        mValues[1][0] * GetCofactor( 1, 0 ) +
        mValues[2][0] * GetCofactor( 2, 0 ) +
        mValues[3][0] * GetCofactor( 3, 0 );
    }
    
    inline void SetValue( const Number a11, const Number a12, const Number a13, const Number a14, const Number a21, const Number a22,
                           const Number a23, const Number a24, const Number a31, const Number a32, const Number a33, const Number a34, const Number a41, const Number a42,
                           const Number a43, const Number a44 )
    {
        mValues[0].SetValue( a11, a12, a13, a14 );
        mValues[1].SetValue( a21, a22, a23, a24 );
        mValues[2].SetValue( a31, a32, a33, a34 );
        mValues[3].SetValue( a41, a42, a43, a44 );
    }
    
    inline void Compose( const Vec3< Number > &scaling, const Quaternion< Number > &rotation, const Vec3< Number > &translation )
    {
        SetIdentity();
        
        mValues[0][3] = translation[0];
        mValues[1][3] = translation[1];
        mValues[2][3] = translation[2];
        
        Matrix3< Number > rotMatrix( rotation );
        Vec3< Number > row0 = rotMatrix.GetRow( 0 ) * scaling[0];
        Vec3< Number > row1 = rotMatrix.GetRow( 1 ) * scaling[1];
        Vec3< Number > row2 = rotMatrix.GetRow( 2 ) * scaling[2];
        
        mValues[0][0] = row0[0];
        mValues[0][1] = row0[1];
        mValues[0][2] = row0[2];
        
        mValues[1][0] = row1[0];
        mValues[1][1] = row1[1];
        mValues[1][2] = row1[2];
        
        mValues[2][0] = row2[0];
        mValues[2][1] = row2[1];
        mValues[2][2] = row2[2];
    }
    
    inline void Decompose( Vec3< Number > &scaling, Quaternion< Number > &rotation, Vec3< Number > &translation ) const
    {
        translation.SetX( mValues[3].GetX() );
        translation.SetY( mValues[3].GetY() );
        translation.SetZ( mValues[3].GetZ() );
        
        //const aiMatrix4x4t<TNumber>& _this = *this;
        
        Vec3< Number > Row1( mValues[0].GetX(), mValues[0].GetY(), mValues[0].GetZ() );
        Vec3< Number > Row2( mValues[1].GetX(), mValues[1].GetY(), mValues[1].GetZ() );
        Vec3< Number > Row3( mValues[2].GetX(), mValues[2].GetY(), mValues[2].GetZ() );
        
        scaling.SetX( Row1.Length() );
        scaling.SetY( Row2.Length() );
        scaling.SetZ( Row3.Length() );
        
        Number determ = GetDeterminant();
        
        if ( determ < 0 )
        {
            scaling *= -1.0;
        }
        
        if ( scaling.GetX() > 0 )
        {
            Row1 /= scaling.GetX();
        }
        
        if ( scaling.GetY() > 0 )
        {
            Row1 /= scaling.GetY();
        }
        
        if ( scaling.GetZ() > 0 )
        {
            Row1 /= scaling.GetZ();
        }
        
        Matrix3< Number > newRotation( Row1, Row2, Row3 );
        Matrix3< Number > newRotationT = newRotation.GetTranspose();
        rotation = Quaternion< Number >( newRotationT );
    }
    
    inline Matrix3< Number > Extract3x3() const
    {
        return Matrix3< Number >( mValues[0][0], mValues[0][1], mValues[0][2],
                       mValues[1][0], mValues[1][1], mValues[1][2],
                       mValues[2][0], mValues[2][1], mValues[2][2] );
    }
    
    inline const Vec4< Number > &operator[]( const U8 row ) const
    {
        return mValues[row];
    }
    
    inline Matrix4 GetZero()
    {
        return Matrix4( Vec4< Number >::GetZero(), Vec4< Number >::GetZero(), Vec4< Number >::GetZero(), Vec4< Number >::GetZero() );
    }
    
    inline Matrix4 GetIdentity()
    {
        Matrix4 mat;
        mat.SetIdentity();
        return mat;
    }


private:

    Vec4< Number > mValues[4];

    inline Number Dotx( const Vec4< Number > &v ) const
    {
        return mValues[0][0] * v[0] + mValues[1][0] * v[1] + mValues[2][0] * v[2] + mValues[3][0] * v[3];
    }

    inline Number Doty( const Vec4< Number > &v ) const
    {
        return mValues[0][1] * v[0] + mValues[1][1] * v[1] + mValues[2][1] * v[2] + mValues[3][1] * v[3];
    }

    inline Number Dotz( const Vec4< Number > &v ) const
    {
        return mValues[0][2] * v[0] + mValues[1][2] * v[1] + mValues[2][2] * v[2] + mValues[3][2] * v[3];
    }

    inline Number Dotw( const Vec4< Number > &v ) const
    {
        return mValues[0][3] * v[0] + mValues[1][3] * v[1] + mValues[2][3] * v[2] + mValues[3][3] * v[3];
    }

};

template< class Number >
inline Matrix4< Number > operator+( const Matrix4< Number > &m1, const Matrix4< Number > &m2 )
{
    return Matrix4< Number >( m1.mValues[0][0] + m2.mValues[0][0], m1.mValues[0][1] + m2.mValues[0][1],
                              m1.mValues[0][2] + m2.mValues[0][2], m1.mValues[0][3] + m2.mValues[0][3],
                             
                              m1.mValues[1][0] + m2.mValues[1][0], m1.mValues[1][1] + m2.mValues[1][1],
                              m1.mValues[1][2] + m2.mValues[1][2], m1.mValues[1][3] + m2.mValues[1][3],
                             
                              m1.mValues[2][0] + m2.mValues[2][0], m1.mValues[2][1] + m2.mValues[2][1],
                              m1.mValues[2][2] + m2.mValues[2][2], m1.mValues[2][3] + m2.mValues[2][3],
                             
                              m1.mValues[3][0] + m2.mValues[3][0], m1.mValues[3][1] + m2.mValues[3][1],
                              m1.mValues[3][2] + m2.mValues[3][2], m1.mValues[3][3] + m2.mValues[3][3] );
}

template< class Number >
inline Matrix4< Number > operator-( const Matrix4< Number > &m1, const Matrix4< Number > &m2 )
{
    return Matrix4< Number >( m1.mValues[0][0] - m2.mValues[0][0], m1.mValues[0][1] - m2.mValues[0][1],
                              m1.mValues[0][2] - m2.mValues[0][2], m1.mValues[0][3] - m2.mValues[0][3],
                   
                              m1.mValues[1][0] - m2.mValues[1][0], m1.mValues[1][1] - m2.mValues[1][1],
                              m1.mValues[1][2] - m2.mValues[1][2], m1.mValues[1][3] - m2.mValues[1][3],
                   
                              m1.mValues[2][0] - m2.mValues[2][0], m1.mValues[2][1] - m2.mValues[2][1],
                              m1.mValues[2][2] - m2.mValues[2][2], m1.mValues[2][3] - m2.mValues[2][3],
                   
                              m1.mValues[3][0] - m2.mValues[3][0], m1.mValues[3][1] - m2.mValues[3][1],
                              m1.mValues[3][2] - m2.mValues[3][2], m1.mValues[3][3] - m2.mValues[3][3] );
}

template< class Number >
inline Matrix4< Number > operator*( const Matrix4< Number > &m1, const Matrix4< Number > &m2 )
{
    return Matrix4< Number >( m2.Dotx( m1.mValues[0] ), m2.Doty( m1.mValues[0] ), m2.Dotz( m1.mValues[0] ), m2.Dotw( m1.mValues[0] ),
                              m2.Dotx( m1.mValues[1] ), m2.Doty( m1.mValues[1] ), m2.Dotz( m1.mValues[1] ), m2.Dotw( m1.mValues[1] ),
                              m2.Dotx( m1.mValues[2] ), m2.Doty( m1.mValues[2] ), m2.Dotz( m1.mValues[2] ), m2.Dotw( m1.mValues[2] ),
                              m2.Dotx( m1.mValues[3] ), m2.Doty( m1.mValues[3] ), m2.Dotz( m1.mValues[3] ), m2.Dotw( m1.mValues[3] ) );
}

template< class Number >
inline Matrix4< Number > operator*( const Matrix4< Number > &m, const Number s )
{
    return Matrix4< Number >( m.mValues[0][0] * s, m.mValues[0][1] * s, m.mValues[0][2] * s, m.mValues[0][3] * s,
                              m.mValues[1][0] * s, m.mValues[1][1] * s, m.mValues[1][2] * s, m.mValues[1][3] * s,
                              m.mValues[2][0] * s, m.mValues[2][1] * s, m.mValues[2][2] * s, m.mValues[2][3] * s,
                              m.mValues[3][0] * s, m.mValues[3][1] * s, m.mValues[3][2] * s, m.mValues[3][3] * s );
}

template< class Number >
inline Vec4< Number > operator*( const Matrix4< Number > &m, const Vec4< Number > &v )
{
    return Vec4< Number >( m.mValues[0].Dot( v ), m.mValues[1].Dot( v ), m.mValues[2].Dot( v ), m.mValues[3].Dot( v ) );
}

#endif