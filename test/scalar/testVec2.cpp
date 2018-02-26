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

#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec2i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

template< class Type >
struct Vector2DTest
{
    static void TestConstructAndAccess()
    {
        Vec2< Type > testConst;
        Vec2< Type > testConst1((Type) 20.22);
        Vec2< Type > testConst2((Type) 10.11, (Type) 30.33);

        ASSERT_REAL_EQ(testConst1[0], (Type) 20.22);
        ASSERT_REAL_EQ(testConst1[1], (Type) 20.22);

        ASSERT_REAL_EQ(testConst2[0], (Type) 10.11);
        ASSERT_REAL_EQ(testConst2[1], (Type) 30.33);

        // const version
        const Type val1 = testConst2[0];
        const Type val2 = testConst2[1];

        ASSERT_REAL_EQ(val1, (Type) 10.11);
        ASSERT_REAL_EQ(val2, (Type) 30.33);

        // mod
        testConst2[0] = 50.55;
        testConst2[1] = 60.66;

        ASSERT_REAL_EQ(testConst2[0], (Type) 50.55);
        ASSERT_REAL_EQ(testConst2[1], (Type) 60.66);
    }

    static void TestIntegerCasts()
    {
        Vec2I vec1(10, 20);

        Vec2< Type > vec2(vec1);

        ASSERT_REAL_EQ(vec2[0], (Type) 10);
        ASSERT_REAL_EQ(vec2[1], (Type) 20);

        Vec2I vec3 = vec2.ToVec2I();

        ASSERT_EQ(vec3[0], (Type) 10);
        ASSERT_EQ(vec3[1], (Type) 20);
    }

    static void TestAssignment()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);

        vec1 = vec2;

        ASSERT_REAL_EQ(vec1[0], (Type) 30.33);
        ASSERT_REAL_EQ(vec1[1], (Type) 40.44);
    }

    static void TestMinAssignment()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);

        vec2 -= vec1;

        ASSERT_REAL_EQ(vec2[0], (Type)(30.33 - 10.11));
        ASSERT_REAL_EQ(vec2[1], (Type)(40.44 - 20.22));
    }

    static void TestPlusAssignment()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);

        vec2 += vec1;

        ASSERT_REAL_EQ(vec2[0], (Type)(30.33 + 10.11));
        ASSERT_REAL_EQ(vec2[1], (Type)(40.44 + 20.22));
    }

    static void TestMulAssignment()
    {
        Vec2< Type > vec1(30.33, 40.44);

        vec1 *= 10.11;

        ASSERT_REAL_EQ(vec1[0], (Type)(30.33 * 10.11));
        ASSERT_REAL_EQ(vec1[1], (Type)(40.44 * 10.11));
    }

    static void TestDivAssignment()
    {
        Vec2< Type > vec1(30.33, 40.44);

        vec1 /= 10.11;

        ASSERT_REAL_EQ(vec1[0], (Type)(30.33 / 10.11));
        ASSERT_REAL_EQ(vec1[1], (Type)(40.44 / 10.11));
    }

    static void TestEquality()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);
        Vec2< Type > vec3(30.33, 40.44);
        Vec2< Type > vec4(0.0, 0.0);

        ASSERT_TRUE(vec2 == vec3);
        ASSERT_TRUE(vec1 != vec3);
        ASSERT_TRUE(vec4.IsZero());
        ASSERT_TRUE(vec4.IsFuzzyZero());
    }

    static void TestSetValue()
    {
        Vec2< Type > vec1(10.11, 20.22);

        vec1.SetValue(30.33, 44.44);

        ASSERT_REAL_EQ(vec1[0], (Type) 30.33);
        ASSERT_REAL_EQ(vec1[1], (Type) 44.44);

        vec1.SetX(50.55);
        vec1.SetY(60.66);

        ASSERT_REAL_EQ(vec1.GetX(), (Type) 50.55);
        ASSERT_REAL_EQ(vec1.GetY(), (Type) 60.66);

        vec1.SetZero();

        ASSERT_REAL_EQ(vec1[0], (Type) 0.0);
        ASSERT_REAL_EQ(vec1[1], (Type) 0.0);

        Vec2< Type > vec2(10.11, 20.22);
        vec2.Clear();

        ASSERT_REAL_EQ(vec2[0], (Type) 0.0);
        ASSERT_REAL_EQ(vec2[1], (Type) 0.0);
    }

    static void TestDot()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);

        const Type dotr = vec1.Dot(vec2);

        ASSERT_REAL_EQ(dotr, (Type)(10.11 * 30.33 + 20.22 * 40.44));
    }

    static void TestLength()
    {
        Vec2< Type > vec1(10.11, 20.22);

        const Type l2 = vec1.Length2();
        const Type l  = vec1.Length();

        ASSERT_REAL_EQ(l2, (Type)(10.11 * 10.11 + 20.22 * 20.22));
        ASSERT_REAL_EQ(l, (Type) Mathf::Sqrt(10.11 * 10.11 + 20.22 * 20.22));
    }

    static void TestDistance()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 60.66);

        const Type dx = 30.33 - 10.11;
        const Type dy = 60.66 - 20.22;

        const Type d2 = vec1.Distance2(vec2);
        const Type d  = vec1.Distance(vec2);

        ASSERT_REAL_EQ(d2, (Type)(dx * dx + dy * dy));
        ASSERT_REAL_EQ(d, (Type) Mathf::Sqrt(dx * dx + dy * dy));
    }

    static void TestNormalise()
    {
        Vec2< Type > vec1(10.11, 20.22);
        const Type l_1  = vec1.Length();

        vec1.Normalise();
        ASSERT_REAL_EQ(vec1[0], (Type)(10.11 / l_1));
        ASSERT_REAL_EQ(vec1[1], (Type)(20.22 / l_1));

        Vec2< Type > vec2(10.11, 20.22);
        const Type l_2  = vec2.Length();

        vec2.SafeNormalise();
        ASSERT_REAL_EQ(vec2[0], (Type)(10.11 / l_2));
        ASSERT_REAL_EQ(vec2[1], (Type)(20.22 / l_2));
    }

    static void TestStatics()
    {
        Vec2< Type > vec1 = Vec2< Type >::GetZero();
        Vec2< Type > vec2 = Vec2< Type >::GetOne();
        Vec2< Type > vec3 = Vec2< Type >::GetUp();
        Vec2< Type > vec4 = Vec2< Type >::GetDown();
        Vec2< Type > vec5 = Vec2< Type >::GetLeft();
        Vec2< Type > vec6 = Vec2< Type >::GetRight();

        ASSERT_REAL_EQ(vec1[0], (Type) 0.0);
        ASSERT_REAL_EQ(vec1[1], (Type) 0.0);

        ASSERT_REAL_EQ(vec2[0], (Type) 1.0);
        ASSERT_REAL_EQ(vec2[1], (Type) 1.0);

        ASSERT_REAL_EQ(vec3[0], (Type) 0.0);
        ASSERT_REAL_EQ(vec3[1], (Type) 1.0);

        ASSERT_REAL_EQ(vec4[0], (Type) 0.0);
        ASSERT_REAL_EQ(vec4[1], (Type) - 1.0);

        ASSERT_REAL_EQ(vec5[0], (Type) - 1.0);
        ASSERT_REAL_EQ(vec5[1], (Type) 0.0);

        ASSERT_REAL_EQ(vec6[0], (Type) 1.0);
        ASSERT_REAL_EQ(vec6[1], (Type) 0.0);

    }

    static void TestLerp()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);

        Vec2< Type > vec3 = vec1.Lerp(vec2, 0.4);

        ASSERT_REAL_EQ(vec3[0], (Type)(10.11 + (30.33 - 10.11) * 0.4));
        ASSERT_REAL_EQ(vec3[1], (Type)(20.22 + (40.44 - 20.22) * 0.4));
    }

    static void TestNLerp()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(30.33, 40.44);

        Vec2< Type > vec3 = vec1.Nlerp(vec2, 0.4);

        const Type dx = (Type)(10.11 + (30.33 - 10.11) * 0.4);
        const Type dy = (Type)(20.22 + (40.44 - 20.22) * 0.4);

        const Type l = Mathf::Sqrt(dx * dx + dy * dy);

        ASSERT_REAL_EQ(vec3[0], dx / l);
        ASSERT_REAL_EQ(vec3[1], dy / l);
    }

    static void TestAbs()
    {
        Vec2< Type > vec1(-10.11, -20.22);
        Vec2< Type > vec2 = vec1.Absolute();

        ASSERT_REAL_EQ(vec2[0], (Type) 10.11);
        ASSERT_REAL_EQ(vec2[1], (Type) 20.22);
    }

    static void TestAngle()
    {
        Vec2< Type > vec1(2.5, 0.0);
        Vec2< Type > vec2(-1.0, 1.0);

        const Type a = vec1.Angle(vec2);

        ASSERT_REAL_EQ(a, (Type)(0.75 * Mathf::GetPi< Type >()));
    }

    static void TestRotate()
    {
        Vec2< Type > vec1(1.0, 0.0);
        Vec2< Type > vec2(-1.0, -1.0);
        vec2.Normalise();

        Vec2< Type > vec3 = vec1.Rotate(1.25 * Mathf::GetPi< Type >());

        ASSERT_REAL_EQ(vec3[0], vec2[0]);
        ASSERT_REAL_EQ(vec3[1], vec2[1]);
    }

    static void TestAxis()
    {
        Vec2< Type > vec1(1.0, -1.0);

        const U32 min = vec1.MinAxis();
        const U32 max = vec1.MaxAxis();

        ASSERT_EQ(min, 1);
        ASSERT_EQ(max, 0);
    }

    static void TestPlus()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(20.22, 40.44);

        Vec2< Type > vec3 = vec2 + vec1;

        ASSERT_REAL_EQ(vec3[0], (Type)(20.22 + 10.11));
        ASSERT_REAL_EQ(vec3[1], (Type)(40.44 + 20.22));
    }

    static void TestMin()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(20.22, 40.44);

        Vec2< Type > vec3 = vec2 - vec1;

        ASSERT_REAL_EQ(vec3[0], (Type)(20.22 - 10.11));
        ASSERT_REAL_EQ(vec3[1], (Type)(40.44 - 20.22));
    }

    static void TestNeg()
    {
        Vec2< Type > vec1(10.11, 20.22);

        Vec2< Type > vec3 = -vec1;

        ASSERT_REAL_EQ(vec3[0], (Type)(-10.11));
        ASSERT_REAL_EQ(vec3[1], (Type)(-20.22));
    }

    static void TestMul()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(20.22, 40.44);

        Vec2< Type > vec3 = vec2 * vec1;

        ASSERT_REAL_EQ(vec3[0], (Type)(20.22 * 10.11));
        ASSERT_REAL_EQ(vec3[1], (Type)(40.44 * 20.22));

        Vec2< Type > vec4 = vec2 * (Type) 50.55;

        ASSERT_REAL_EQ(vec4[0], (Type)(20.22 * 50.55));
        ASSERT_REAL_EQ(vec4[1], (Type)(40.44 * 50.55));

        Vec2< Type > vec5 = (Type) 60.66 * vec2;

        ASSERT_REAL_EQ(vec5[0], (Type)(20.22 * 60.66));
        ASSERT_REAL_EQ(vec5[1], (Type)(40.44 * 60.66));
    }

    static void TestDiv()
    {
        Vec2< Type > vec1(10.11, 20.22);
        Vec2< Type > vec2(20.22, 40.44);

        Vec2< Type > vec3 = vec2 / vec1;

        ASSERT_REAL_EQ(vec3[0], (Type)(20.22 / 10.11));
        ASSERT_REAL_EQ(vec3[1], (Type)(40.44 / 20.22));

        Vec2< Type > vec4 = vec2 / (Type) 50.55;

        ASSERT_REAL_EQ(vec4[0], (Type)(20.22 / 50.55));
        ASSERT_REAL_EQ(vec4[1], (Type)(40.44 / 50.55));
    }
};


TEST(P(Vec2Test), ConstructAndAccess)
{
    Vector2DTest< F32 >::TestConstructAndAccess();
    Vector2DTest< F64 >::TestConstructAndAccess();
}

TEST(P(Vec2Test), IntegerCast)
{
    Vector2DTest< F32 >::TestIntegerCasts();
    Vector2DTest< F64 >::TestIntegerCasts();
}

TEST(P(Vec2Test), Assignment)
{
    Vector2DTest< F32 >::TestAssignment();
    Vector2DTest< F64 >::TestAssignment();
}

TEST(P(Vec2Test), MinAssignment)
{
    Vector2DTest< F32 >::TestMinAssignment();
    Vector2DTest< F64 >::TestMinAssignment();
}

TEST(P(Vec2Test), PlusAssignment)
{
    Vector2DTest< F32 >::TestPlusAssignment();
    Vector2DTest< F64 >::TestPlusAssignment();
}

TEST(P(Vec2Test), MulAssignment)
{
    Vector2DTest< F32 >::TestMulAssignment();
    Vector2DTest< F64 >::TestMulAssignment();
}

TEST(P(Vec2Test), DivAssignment)
{
    Vector2DTest< F32 >::TestDivAssignment();
    Vector2DTest< F64 >::TestDivAssignment();
}

TEST(P(Vec2Test), Equality)
{
    Vector2DTest< F32 >::TestEquality();
    Vector2DTest< F64 >::TestEquality();
}

TEST(P(Vec2Test), SetValue)
{
    Vector2DTest< F32 >::TestSetValue();
    Vector2DTest< F64 >::TestSetValue();
}

TEST(P(Vec2Test), Dot)
{
    Vector2DTest< F32 >::TestDot();
    Vector2DTest< F64 >::TestDot();
}

TEST(P(Vec2Test), Length)
{
    Vector2DTest< F32 >::TestLength();
    Vector2DTest< F64 >::TestLength();
}

TEST(P(Vec2Test), Distance)
{
    Vector2DTest< F32 >::TestDistance();
    Vector2DTest< F64 >::TestDistance();
}

TEST(P(Vec2Test), Normalise)
{
    Vector2DTest< F32 >::TestNormalise();
    Vector2DTest< F64 >::TestNormalise();
}

TEST(P(Vec2Test), Statics)
{
    Vector2DTest< F32 >::TestStatics();
    Vector2DTest< F64 >::TestStatics();
}

TEST(P(Vec2Test), Lerp)
{
    Vector2DTest< F32 >::TestLerp();
    Vector2DTest< F64 >::TestLerp();
}

TEST(P(Vec2Test), Nlerp)
{
    Vector2DTest< F32 >::TestNLerp();
    Vector2DTest< F64 >::TestNLerp();
}

TEST(P(Vec2Test), Abs)
{
    Vector2DTest< F32 >::TestAbs();
    Vector2DTest< F64 >::TestAbs();
}

TEST(P(Vec2Test), Angle)
{
    Vector2DTest< F32 >::TestAngle();
    Vector2DTest< F64 >::TestAngle();
}

TEST(P(Vec2Test), Rotate)
{
    Vector2DTest< F32 >::TestRotate();
    Vector2DTest< F64 >::TestRotate();
}

TEST(P(Vec2Test), Axis)
{
    Vector2DTest< F32 >::TestAxis();
    Vector2DTest< F64 >::TestAxis();
}

TEST(P(Vec2Test), Plus)
{
    Vector2DTest< F32 >::TestPlus();
    Vector2DTest< F64 >::TestPlus();
}

TEST(P(Vec2Test), Min)
{
    Vector2DTest< F32 >::TestMin();
    Vector2DTest< F64 >::TestMin();
}

TEST(P(Vec2Test), Neg)
{
    Vector2DTest< F32 >::TestNeg();
    Vector2DTest< F64 >::TestNeg();
}

TEST(P(Vec2Test), Mul)
{
    Vector2DTest< F32 >::TestMul();
    Vector2DTest< F64 >::TestMul();
}

TEST(P(Vec2Test), Div)
{
    Vector2DTest< F32 >::TestDiv();
    Vector2DTest< F64 >::TestDiv();
}



