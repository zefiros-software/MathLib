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
#ifndef __ENGINE_MATRIX3_H__
#define __ENGINE_MATRIX3_H__

#include "math/scalar/vec3.h"
#include "math/scalar/quaternion.h"

template< class Number >
class Matrix3;

typedef Matrix3< F32 > Matrix3f;
typedef Matrix3< F64 > Matrix3d;

#ifndef REAL_UNDEFINED
typedef Matrix3< Real > Matrix3r;
#endif

template< class Number >
class Matrix3
{
    friend Matrix3 operator+( const Matrix3 &m1, const Matrix3 &m2 );
    friend Matrix3 operator-( const Matrix3 &m1, const Matrix3 &m2 );
    friend Matrix3 operator*( const Matrix3 &m1, const Matrix3 &m2 );
    friend Matrix3 operator*( const Matrix3 &m, const Real s );
    friend Vec3< Number > operator*( const Matrix3 &m, const Vec3< Number > &v );

public:

    inline Matrix3()
    {
    }
    
    inline Matrix3( const Quaternion< Number > &q )
    {
        SetRotation( q );
    }
    
    inline Matrix3( const Real a11, const Real a12, const Real a13,
                     const Real a21, const Real a22, const Real a23,
                     const Real a31, const Real a32, const Real a33 )
    {
        SetValue( a11, a12, a13, a21, a22, a23, a31, a32, a33 );
    }
    
    inline Matrix3( const Matrix3 &other )
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
    }
    
    inline Matrix3( const Vec3< Number > &v1, const Vec3< Number > &v2, const Vec3< Number > &v3 )
    {
        mValues[0] = v1;
        mValues[1] = v2;
        mValues[2] = v3;
    }
    
    inline Matrix3 &operator=( const Matrix3 &m )
    {
        mValues[0] = m.mValues[0];
        mValues[1] = m.mValues[1];
        mValues[2] = m.mValues[2];
        
        return *this;
    }
    
    inline Matrix3 &operator*=( const Matrix3 &m )
    {
        SetValue( m.Dotx( mValues[0] ), m.Doty( mValues[0] ), m.Dotz( mValues[0] ),
                 m.Dotx( mValues[1] ), m.Doty( mValues[1] ), m.Dotz( mValues[1] ),
                 m.Dotx( mValues[2] ), m.Doty( mValues[2] ), m.Dotz( mValues[2] ) );
        
        return *this;
    }
    
    inline Matrix3 &operator+=( const Matrix3 &m )
    {
        SetValue( mValues[0][0] + m.mValues[0][0], mValues[0][1] + m.mValues[0][1], mValues[0][2] + m.mValues[0][2],
                  mValues[1][0] + m.mValues[1][0], mValues[1][1] + m.mValues[1][1], mValues[1][2] + m.mValues[1][2],
                  mValues[2][0] + m.mValues[2][0], mValues[2][1] + m.mValues[2][1], mValues[2][2] + m.mValues[2][2] );
        
        return *this;
    }
    
    inline Matrix3 &operator-=( const Matrix3 &m )
    {
        SetValue( mValues[0][0] - m.mValues[0][0], mValues[0][1] - m.mValues[0][1], mValues[0][2] - m.mValues[0][2],
                 mValues[1][0] - m.mValues[1][0], mValues[1][1] - m.mValues[1][1], mValues[1][2] - m.mValues[1][2],
                 mValues[2][0] - m.mValues[2][0], mValues[2][1] - m.mValues[2][1], mValues[2][2] - m.mValues[2][2] );
        
        return *this;
    }
    
    inline bool operator==( const Matrix3 &m ) const
    {
        return mValues[0] == m.mValues[0] && mValues[1] == m.mValues[1] && mValues[2] == m.mValues[2];
    }
    
    bool operator!=( const Matrix3 &m ) const
    {
        return !( *this == m );
    }
    
    inline void SetColumn( const U8 column, const Vec3< Number > &v )
    {
        mValues[0][column] = v[0];
        mValues[1][column] = v[1];
        mValues[2][column] = v[2];
    }
    
    inline Vec3< Number > GetColumn( const U8 column ) const
    {
        return Vec3< Number >( mValues[0][column], mValues[1][column], mValues[2][column] );
    }
    
    inline void SetRow( const U8 row, const Vec3< Number > &v )
    {
        mValues[row] = v;
    }
    
    inline Vec3< Number > GetRow( const U8 row ) const
    {
        return mValues[row];
    }
    
    inline void SetRotation( const Quaternion< Number > &q )
    {
        const Real norm2 = q.Length2();
        
        assert( norm2 != 0.0f );
        
        const Real s     = 2.0f / norm2;
        
        const Real xs  = q[0] * s;
        const Real ys  = q[1] * s;
        const Real zs  = q[2] * s;
        const Real wxs = q[3] * xs;
        const Real wys = q[3] * ys;
        const Real wzs = q[3] * zs;
        const Real xxs = q[0] * xs;
        const Real xys = q[0] * ys;
        const Real xzs = q[0] * zs;
        const Real yys = q[1] * ys;
        const Real yzs = q[1] * zs;
        const Real zzs = q[2] * zs;
        
        SetValue( 1.0f - ( yys + zzs ), xys - wzs, xzs + wys,
                 xys + wzs, 1.0f - ( xxs + zzs ), yzs - wxs,
                 xzs - wys, yzs + wxs, 1.0f - ( xxs + yys ) );
    }
    
    inline Quaternion< Number > GetRotation() const
    {
        Real t[4];
        const Real trace = mValues[0][0] + mValues[1][1] + mValues[2][2];
        
        
        if ( trace > 0.0f )
        {
            const Real s  = Mathf::Sqrt( trace + 1.0f );
            const Real s2 = 0.5f / s;
            
            t[0] = ( mValues[2][1] - mValues[1][2] ) * s2;
            t[1] = ( mValues[0][2] - mValues[2][0] ) * s2;
            t[2] = ( mValues[1][0] - mValues[0][1] ) * s2;
            t[3] = 0.5f * s;
        }
        else
        {
            const U8 i = mValues[0][0] < mValues[1][1] ?
            ( mValues[1][1] < mValues[2][2] ? 2 : 1 ) :
            ( mValues[0][0] < mValues[2][2] ? 2 : 0 );
            
            const U8 j = ( i + 1 ) % 3;
            const U8 k = ( i + 2 ) % 3;
            
            const Real s = Mathf::Sqrt( mValues[i][i] - mValues[j][j] - mValues[k][k] + 1.0f );
            
            assert( s != 0.0f );
            
            const Real s2 = 0.5f / s;
            
            t[i] = 0.5f * s;
            t[j] = ( mValues[j][i] - mValues[i][j] ) * s2;
            t[k] = ( mValues[k][i] - mValues[i][k] ) * s2;
            t[3] = ( mValues[k][j] - mValues[j][k] ) * s2;
        }
        
        return Quaternion< Number >( t[0], t[1], t[2], t[3] );
    }
    
    inline void SetEuler( const Real yaw, const Real pitch, const Real roll )
    {
        Real cy( Mathf::Cos( yaw ) );
        Real cp( Mathf::Cos( pitch ) );
        Real cr( Mathf::Cos( roll ) );
        
        Real sy( Mathf::Sin( yaw ) );
        Real sp( Mathf::Sin( pitch ) );
        Real sr( Mathf::Sin( roll ) );
        
        
        Real cc = cr * cy;
        Real cs = cr * sy;
        Real sc = sr * cy;
        Real ss = sr * sy;
        
        SetValue( cp * cy, sp * sc - cs, sp * cc + ss,
                 cp * sy, sp * ss + cc, sp * cs - sc,
                 -sp, cp * sr, cp * cr );
    }
    
    inline Vec3< Number > GetEuler() const
    {
        return GetRotation().GetAxis();
    }
    
    inline Matrix3 Scale( const Vec3< Number > &v ) const
    {
        return Matrix3( mValues[0][0] * v[0], mValues[0][1] * v[1], mValues[0][2] * v[2],
                       mValues[1][0] * v[0], mValues[1][1] * v[1], mValues[1][2] * v[2],
                       mValues[2][0] * v[0], mValues[2][1] * v[1], mValues[2][2] * v[2] );
    }
    
    inline Matrix3 GetTranspose() const
    {
        return Matrix3( mValues[0][0], mValues[1][0], mValues[2][0],
                       mValues[0][1], mValues[1][1], mValues[2][1],
                       mValues[0][2], mValues[1][2], mValues[2][2] );
    }
    
    inline Matrix3 GetAbsolute() const
    {
        return Matrix3( Mathf::Abs( mValues[0][0] ), Mathf::Abs( mValues[0][1] ), Mathf::Abs( mValues[0][2] ),
                       Mathf::Abs( mValues[1][0] ), Mathf::Abs( mValues[1][1] ), Mathf::Abs( mValues[1][2] ),
                       Mathf::Abs( mValues[2][0] ), Mathf::Abs( mValues[2][1] ), Mathf::Abs( mValues[2][2] ) );
    }
    
    inline Matrix3 GetAdjoint() const
    {
        return Matrix3( GetCofactor( 0, 0 ), GetCofactor( 0, 1 ), GetCofactor( 0, 2 ),
                       GetCofactor( 1, 0 ), GetCofactor( 1, 1 ), GetCofactor( 1, 2 ),
                       GetCofactor( 2, 0 ), GetCofactor( 2, 1 ), GetCofactor( 2, 2 ) );
    }
    
    inline Matrix3 GetInverse() const
    {
        const Real det = GetDeterminant();
        
        assert( det != 0.0f );
        
        const Real s = 1.0f / det;
        return GetAdjoint().GetTranspose() * s;
    }
    
    inline void SetIdentity()
    {
        SetValue( 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f );
    }
    
    inline Real GetCofactor( const U8 row, const U8 column ) const
    {
        Real cof = mValues[( row + 1 ) % 3][( column + 1 ) % 3] * mValues[( row + 2 ) % 3][( column + 2 ) % 3] -
        mValues[( row + 1 ) % 3][( column + 2 ) % 3] * mValues[( row + 2 ) % 3][( column + 1 ) % 3];
        
        if ( ( ( column + row ) & 1 ) == 1 )
        {
            cof *= -1;
        }
        
        return cof;
    }
    
    inline Real GetDeterminant() const
    {
        return  mValues[0][0] * GetCofactor( 0, 0 ) +
        mValues[1][0] * GetCofactor( 1, 0 ) +
        mValues[2][0] * GetCofactor( 2, 0 );
    }
    
    inline void SetValue( const Real a11, const Real a12, const Real a13,
                           const Real a21, const Real a22, const Real a23,
                           const Real a31, const Real a32, const Real a33 )
    {
        mValues[0].SetValue( a11, a12, a13 );
        mValues[1].SetValue( a21, a22, a23 );
        mValues[2].SetValue( a31, a32, a33 );
    }
    
    inline Vec3< Number > &operator[]( const U8 axis )
    {
        return mValues[axis];
    }
    
    
    
    static inline Matrix3 GetZero()
    {
        return Matrix3( Vec3< Number >::GetZero(), Vec3< Number >::GetZero(), Vec3< Number >::GetZero() );
    }
    
    static inline Matrix3 GetIdentity()
    {
        Matrix3 mat;
        mat.SetIdentity();
        return mat;
    }

private:

    Vec3< Number > mValues[3];

    inline Real Dotx( const Vec3< Number > &v ) const
    {
        return mValues[0][0] * v[0] + mValues[1][0] * v[1] + mValues[2][0] * v[2];
    }
    
    inline Real Doty( const Vec3< Number > &v ) const
    {
        return mValues[0][1] * v[0] + mValues[1][1] * v[1] + mValues[2][1] * v[2];
    }
    
    inline Real Dotz( const Vec3< Number > &v ) const
    {
        return mValues[0][2] * v[0] + mValues[1][2] * v[1] + mValues[2][2] * v[2];
    }
};

template< class Number >
Matrix3< Number > operator+( const Matrix3< Number > &m1, const Matrix3< Number > &m2 )
{
    return Matrix3< Number >(
                   m1.mValues[0][0] + m2.mValues[0][0],
                   m1.mValues[0][1] + m2.mValues[0][1],
                   m1.mValues[0][2] + m2.mValues[0][2],
                   m1.mValues[1][0] + m2.mValues[1][0],
                   m1.mValues[1][1] + m2.mValues[1][1],
                   m1.mValues[1][2] + m2.mValues[1][2],
                   m1.mValues[2][0] + m2.mValues[2][0],
                   m1.mValues[2][1] + m2.mValues[2][1],
                   m1.mValues[2][2] + m2.mValues[2][2] );
}

template< class Number >
Matrix3< Number > operator-( const Matrix3< Number > &m1, const Matrix3< Number > &m2 )
{
    return Matrix3< Number >(
                   m1.mValues[0][0] - m2.mValues[0][0],
                   m1.mValues[0][1] - m2.mValues[0][1],
                   m1.mValues[0][2] - m2.mValues[0][2],
                   m1.mValues[1][0] - m2.mValues[1][0],
                   m1.mValues[1][1] - m2.mValues[1][1],
                   m1.mValues[1][2] - m2.mValues[1][2],
                   m1.mValues[2][0] - m2.mValues[2][0],
                   m1.mValues[2][1] - m2.mValues[2][1],
                   m1.mValues[2][2] - m2.mValues[2][2] );
}

template< class Number >
Matrix3< Number > operator*( const Matrix3< Number > &m1, const Matrix3< Number > &m2 )
{
    return Matrix3< Number >( m2.Dotx( m1.mValues[0] ), m2.Doty( m1.mValues[0] ), m2.Dotz( m1.mValues[0] ),
                   m2.Dotx( m1.mValues[1] ), m2.Doty( m1.mValues[1] ), m2.Dotz( m1.mValues[1] ),
                   m2.Dotx( m1.mValues[2] ), m2.Doty( m1.mValues[2] ), m2.Dotz( m1.mValues[2] ) );
}

template< class Number >
Matrix3< Number > operator*( const Matrix3< Number > &m, const Number s )
{
    return Matrix3< Number >( m.mValues[0][0] * s, m.mValues[0][1] * s, m.mValues[0][2] * s,
                   m.mValues[1][0] * s, m.mValues[1][1] * s, m.mValues[1][2] * s,
                   m.mValues[2][0] * s, m.mValues[2][1] * s, m.mValues[2][2] * s );
}

template< class Number >
Vec3< Number > operator*( const Matrix3< Number > &m, const Vec3< Number > &v )
{
    return Vec3< Number >( m.mValues[0].Dot( v ), m.mValues[1].Dot( v ), m.mValues[2].Dot( v ) );
}

#endif