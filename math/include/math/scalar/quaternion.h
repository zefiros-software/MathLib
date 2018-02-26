/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016-2018 Zefiros Software.
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
#ifndef __ENGINE_QUATERNION_H__
#define __ENGINE_QUATERNION_H__

#include "math/scalar/mathf.h"
#include "math/scalar/vec3.h"
#include "math/scalar/vec4.h"

#include <assert.h>

template< class Number >
class Quaternion;

typedef Quaternion< F32 > Quaternionf;
typedef Quaternion< F64 > Quaterniond;

#ifndef REAL_UNDEFINED
typedef Quaternion< Real > Quaternionr;
#endif

template< class Number >
class Quaternion
{
public:

    inline Quaternion()
    {
    }

    inline Quaternion( const Number yaw, const Number pitch, const Number roll )
    {
        SetEuler( yaw, pitch, roll );
    }

    inline Quaternion( const Number x, const Number y, const Number z, const Number w )
    {
        SetValue( x, y, z, w );
    }

    inline Quaternion( const Vec3< Number > &axis, const Number angle )
    {
        SetRotation( axis, angle );
    }

    inline Quaternion( const Quaternion &other )
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
        mValues[3] = other.mValues[3];
    }

    inline Quaternion( const Vec4< Number > &axis )
    {
        SetValue( axis[0], axis[1], axis[2], axis[3] );
    }

    inline Quaternion &operator=( const Quaternion &q )
    {
        mValues[0] = q[0];
        mValues[1] = q[1];
        mValues[2] = q[2];
        mValues[3] = q[3];

        return *this;
    }

    inline Quaternion &operator+=( const Quaternion &q )
    {
        mValues[0] += q[0];
        mValues[1] += q[1];
        mValues[2] += q[2];
        mValues[3] += q[3];

        return *this;
    }

    inline Quaternion &operator-=( const Quaternion &q )
    {
        mValues[0] -= q[0];
        mValues[1] -= q[1];
        mValues[2] -= q[2];
        mValues[3] -= q[3];

        return *this;
    }

    inline Quaternion &operator*=( const Quaternion &q )
    {
        SetValue( mValues[3] * q[0] + mValues[0] * q[3] + mValues[1] * q[2] - mValues[2] * q[1],
                  mValues[3] * q[1] + mValues[1] * q[3] + mValues[2] * q[0] - mValues[0] * q[2],
                  mValues[3] * q[2] + mValues[2] * q[3] + mValues[0] * q[1] - mValues[1] * q[0],
                  mValues[3] * q[3] - mValues[0] * q[0] - mValues[1] * q[1] - mValues[2] * q[2] );

        return *this;
    }

    inline Quaternion &operator*=( const Number s )
    {
        mValues[0] *= s;
        mValues[1] *= s;
        mValues[2] *= s;
        mValues[3] *= s;

        return *this;
    }

    inline Quaternion &operator/=( const Number s )
    {
        assert( s != 0.0f );
        return *this / s;
    }

    inline Quaternion operator+( const Quaternion &q ) const
    {
        return Quaternion( mValues[0] + q[0], mValues[1] + q[1], mValues[2] + q[2], mValues[3] + q[3] );
    }

    inline Quaternion operator-( const Quaternion &q ) const
    {
        return Quaternion( mValues[0] - q[0], mValues[1] - q[1], mValues[2] - q[2], mValues[3] - q[3] );
    }

    inline Quaternion operator*( const Number s ) const
    {
        return Quaternion( mValues[0] * s, mValues[1] * s, mValues[2] * s, mValues[3] * s );
    }

    inline Quaternion operator/( const Number s ) const
    {
        assert( s != 0.0f );
        return *this / s;
    }

    inline Quaternion operator-() const
    {
        return Quaternion( -mValues[0], -mValues[1],  -mValues[2],  -mValues[3] );
    }

    inline Number operator[]( const U8 axis ) const
    {
        return mValues[ axis ];
    }

    inline Number operator[]( const U8 axis )
    {
        return mValues[ axis ];
    }

    inline void SetEuler( const Number yaw, const Number pitch, const Number roll )
    {
        const Number p = yaw * 0.5f;
        const Number y = pitch * 0.5f;
        const Number r = roll * 0.5f;

        const Number siny = Mathf::Sin( y );
        const Number sinp = Mathf::Sin( p );
        const Number sinr = Mathf::Sin( r );
        const Number cosy = Mathf::Cos( y );
        const Number cosp = Mathf::Cos( p );
        const Number cosr = Mathf::Cos( r );

        SetValue( cosr * sinp * cosy + sinr * cosp * siny,
                  cosr * cosp * siny - sinr * sinp * cosy,
                  sinr * cosp * cosy - cosr * sinp * siny,
                  cosr * cosp * cosy + sinr * sinp * siny );
    }

    inline void SetRotation( const Vec3< Number > &axis, const Number angle )
    {
        assert( axis.Length() != 0.0f );

        Number s = Mathf::Sin( angle * 0.5f ) / axis.Length();
        SetValue( axis[0] * s, axis[1] * s, axis[2] * s, Mathf::Cos( angle * 0.5f ) );
    }

    inline void SetValue( Number x, Number y, Number z, Number w )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }

    inline Quaternion GetInverse() const
    {
        return Quaternion( -mValues[0], -mValues[1], -mValues[2], mValues[3] );
    }

    inline Quaternion SafeNormalise()
    {
        const Vec4< Number > absv = Vec4< Number >( mValues[0], mValues[1], mValues[2], mValues[3] ).Absolute();
        const U8 max = absv.MaxAxis();

        if ( absv[max] > 0 )
        {
            *this /= absv[max];

            return *this /= Length();
        }
        else
        {
            SetValue( 1.0f, 0.0f, 0.0f, 0.0f );
        }

        return *this;
    }

    inline Quaternion Normalise()
    {
        assert( Length() != 0.0f );

        return *this /= Length();
    }

    inline Vec3< Number > RotateVector( const Vec3< Number > &vec ) const
    {
        //     Quaternion q = vec * ( *this );
        //
        //     q *= ( *this ).GetInverse();
        //
        //     return Vec3( q[0], q[1], q[2] );

        // Faster path ! https://molecularmusings.wordpress.com/2013/05/24/a-faster-quaternion-vector-multiplication/

        Vec3< Number > qXYZ = this->xyz();
        Vec3< Number > t = 2 * qXYZ.Cross( vec );

        return ( vec + mValues[3] * t + qXYZ.Cross( t ) );
    }

    inline Quaternion GetViewRotation() const
    {
        return GetInverse();
    }

    inline Number GetAngleFromQuaternion( const Quaternion &q ) const
    {
        const Number s = Mathf::Sqrt( Length2() * q.Length2() );

        assert( s != 0.0f );

        return Mathf::Acos( Mathf::Clamp( Dot( q ) / s, ( Number ) - 1.0, ( Number )1.0 ) );
    }

    inline Number GetAngle() const
    {
        return 2.0f * Mathf::Acos( Mathf::Clamp( mValues[3], ( Number ) - 1.0, ( Number )1.0 ) );
    }

    inline Vec3< Number > GetAxis() const
    {
        const Number s2 = 1.0f - mValues[3] * mValues[3];

        if ( s2 < Mathf::GetEpsilon< Number >() )
        {
            return Vec3< Number >( 1.0f, 0.0f, 0.0f );
        }

        const Number s = 1.0f / Mathf::Sqrt( s2 );
        return Vec3< Number >( mValues[0] * s, mValues[1] * s, mValues[2] * s );
    }

    inline Number Dot( const Quaternion &q ) const
    {
        return mValues[0] * q.mValues[0] + mValues[1] * q.mValues[1] + mValues[2] * q.mValues[2] + mValues[3] * q.mValues[3];
    }

    inline Number Length2() const
    {
        return Dot( *this );
    }

    inline Number Length() const
    {
        return Mathf::Sqrt( Length2() );
    }

    inline Quaternion Slerp( const Quaternion &q, const Number t ) const
    {
        const Number dotp = Dot( q );

        if ( dotp > ( 1.0f - Mathf::GetEpsilon< Number >() ) )
        {
            return Lerp( q, t );
        }

        const Number theta = Mathf::Acos( Mathf::Clamp( dotp, ( Number ) - 1.0, ( Number )1.0 ) ) * t;
        Quaternion q2 = q - *this * dotp;
        q2.Normalise();

        return *this * Mathf::Cos( theta ) + q2 * Mathf::Sin( theta );
    }

    inline Quaternion Nlerp( const Quaternion &q, const Number t ) const
    {
        const Vec4< Number > tv( mValues[0], mValues[1], mValues[2], mValues[3] );
        const Vec4< Number > qv( q.mValues[0], q.mValues[1], q.mValues[2], q.mValues[3] );
        return Quaternion( tv.Lerp( qv, t ).Normalise() );
    }


    inline Quaternion Lerp( const Quaternion &q, const Number t ) const
    {
        const Vec4< Number > tv( mValues[0], mValues[1], mValues[2], mValues[3] );
        const Vec4< Number > qv( q.mValues[0], q.mValues[1], q.mValues[2], q.mValues[3] );
        return Quaternion( tv.Lerp( qv, t ) );
    }

    inline void Clear()
    {
        SetValue( 0.0f, 0.0f, 0.0f, 1.0f );
    }

    inline Quaternion GetIdentity()
    {
        return Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
    }

private:

    Vec3< Number > xyz() const
    {
        return Vec3< Number >( mValues[0], mValues[1], mValues[2] );
    }

    Number mValues[4];
};

template< class Number >
inline Quaternion< Number > operator*( const Quaternion< Number > &q1, const Quaternion< Number > &q2 )
{
    return Quaternion< Number >( q1[3] * q2[0] + q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1],
                                 q1[3] * q2[1] + q1[1] * q2[3] + q1[2] * q2[0] - q1[0] * q2[2],
                                 q1[3] * q2[2] + q1[2] * q2[3] + q1[0] * q2[1] - q1[1] * q2[0],
                                 q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] );
}

template< class Number >
inline Quaternion< Number > operator*( const Quaternion< Number > &q, const Vec3< Number > &v )
{
    return Quaternion< Number >( +q[3] * v[0] + q[1] * v[2] - q[2] * v[1],
                                 +q[3] * v[1] + q[2] * v[0] - q[0] * v[2],
                                 +q[3] * v[2] + q[0] * v[1] - q[1] * v[0],
                                 -q[0] * v[0] - q[1] * v[1] - q[2] * v[2] );
}

template< class Number >
inline Quaternion< Number > operator*( const Vec3< Number > &v, const Quaternion< Number > &q )
{
    return Quaternion< Number >( +v[0] * q[3] + v[1] * q[2] - v[2] * q[1],
                                 +v[1] * q[3] + v[2] * q[0] - v[0] * q[2],
                                 +v[2] * q[3] + v[0] * q[1] - v[1] * q[0],
                                 -v[0] * q[0] - v[1] * q[1] - v[2] * q[2] );
}

#endif