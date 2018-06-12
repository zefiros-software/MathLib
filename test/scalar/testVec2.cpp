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

#include "math/types.h"
#include "math/vec2.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

template< class tT >
struct Vector2DTest
{
    static void TestConstructAndAccess()
    {
        Vector2< tT > testConst;
        ASSERT_TRUE(Mathf::Equal(testConst[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(testConst[1], (tT) 0.0));
        Vector2< tT > testConst1((tT) 20.22);
        Vector2< tT > testConst2((tT) 10.11, (tT) 30.33);

        ASSERT_TRUE(Mathf::Equal(testConst1[0], (tT) 20.22));
        ASSERT_TRUE(Mathf::Equal(testConst1[1], (tT) 20.22));

        ASSERT_TRUE(Mathf::Equal(testConst2[0], (tT) 10.11));
        ASSERT_TRUE(Mathf::Equal(testConst2[1], (tT) 30.33));

        const tT val1 = testConst2[0];
        const tT val2 = testConst2[1];

        ASSERT_TRUE(Mathf::Equal(val1, (tT) 10.11));
        ASSERT_TRUE(Mathf::Equal(val2, (tT) 30.33));

        testConst2[0] = (tT)50.55;
        testConst2[1] = (tT)60.66;

        ASSERT_TRUE(Mathf::Equal(testConst2[0], (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(testConst2[1], (tT) 60.66));
    }

    static void TestIntegerCasts()
    {
        Vec2i vec1(10, 20);

        Vector2< tT > vec2(vec1);

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 10));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 20));

        Vec2i vec3 = vec2.ToVec2i();

        ASSERT_EQ(vec3[0], (tT) 10);
        ASSERT_EQ(vec3[1], (tT) 20);
    }

    static void TestAssignment()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);
        const Vector2< tT > vec3(30.33, 40.44);

        vec1 = vec2;

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec1.Data()[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec1.Data()[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec3.Data()[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec3.Data()[1], (tT) 40.44));
    }

    static void TestMinAssignment()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);

        vec2 -= vec1;

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)30.33 - (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)40.44 - (tT)20.22));
    }

    static void TestPlusAssignment()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);

        vec2 += vec1;

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)30.33 + (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)40.44 + (tT) 20.22));
    }

    static void TestMulAssignment()
    {
        Vector2< tT > vec1(30.33, 40.44);

        vec1 *= (tT)10.11;

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT)30.33 * (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT)40.44 * (tT)10.11));
    }

    static void TestDivAssignment()
    {
        Vector2< tT > vec1(30.33, 40.44);

        vec1 /= (tT)10.11;

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT)30.33 / (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT)40.44 / (tT)10.11));
    }

    static void TestEquality()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);
        Vector2< tT > vec3(30.33, 40.44);
        Vector2< tT > vec4(0.0, 0.0);
        Vector2< tT > vec5(30.33, 41.44);
        Vector2< tT > vec6(0.0, 40.45);

        ASSERT_TRUE(vec2 == vec3);
        ASSERT_TRUE(vec2 != vec5);
        ASSERT_TRUE(vec1 != vec3);
        ASSERT_TRUE(vec4.IsZero());
        ASSERT_FALSE(vec5.IsZero());
        ASSERT_FALSE(vec6.IsZero());
        ASSERT_TRUE(vec4.IsFuzzyZero());
    }

    static void TestSet()
    {
        Vector2< tT > vec1(10.11, 20.22);

        vec1.Set((tT)30.33, (tT)44.44);

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 44.44));

        vec1.X((tT)50.55);
        vec1.Y((tT)60.66);

        ASSERT_TRUE(Mathf::Equal(vec1.X(), (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(vec1.Y(), (tT) 60.66));

        vec1.Clear();

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 0.0));

        Vector2< tT > vec2(10.11, 20.22);
        vec2.Clear();

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 0.0));
    }

    static void TestDot()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);

        const tT dotr = vec1.Dot(vec2);

        ASSERT_TRUE(Mathf::Equal(dotr, (tT)10.11 * (tT)30.33 + (tT)20.22 * (tT)40.44));
    }

    static void TestLength()
    {
        Vector2< tT > vec1(10.11, 20.22);

        const Scalar l2 = vec1.Length2();
        const Scalar l  = vec1.Length();

        ASSERT_TRUE(Mathf::Equal((tT)l2, (tT)10.11 * (tT)10.11 + (tT)20.22 * (tT)20.22));
        ASSERT_TRUE(Mathf::Equal((tT)l, (tT)Mathf::Sqrt((F64)((tT)10.11 * (tT)10.11 + (tT)20.22 * (tT)20.22))));
    }

    static void TestDistance()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 60.66);

        const tT dx = (tT)30.33 - (tT)10.11;
        const tT dy = (tT)60.66 - (tT)20.22;

        const Scalar d2 = vec1.Distance2(vec2);
        const Scalar d  = vec1.Distance(vec2);

        ASSERT_TRUE(Mathf::Equal((tT)d2, dx * dx + dy * dy));
        ASSERT_TRUE(Mathf::Equal((tT)d, (tT)Mathf::Sqrt((F64)(dx * dx + dy * dy))));
    }

    static void TestNormalise()
    {
        Vector2< tT > vec1(10.11, 20.22);
        const Scalar l_1  = vec1.Length();

        vec1.Normalise();
        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT)(10.11 / l_1)));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT)(20.22 / l_1)));

        Vector2< tT > vec2(0.0, 2.22);
        const Scalar l_2 = vec2.Length();

        vec2.SafeNormalise();
        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)(0.0 / l_2)));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)(2.22 / l_2)));

        Vector2< tT > vec3;
        vec3.SafeNormalise();
        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)1.0));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)0.0));
    }

    static void TestStatics()
    {
        Vector2< tT > vec1 = Vector2< tT >::Zeros();
        Vector2< tT > vec2 = Vector2< tT >::Ones();
        Vector2< tT > vec3 = Vector2< tT >::Up();
        Vector2< tT > vec4 = Vector2< tT >::Down();
        Vector2< tT > vec5 = Vector2< tT >::Left();
        Vector2< tT > vec6 = Vector2< tT >::Right();

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 0.0));

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 1.0));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 1.0));

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT) 1.0));

        ASSERT_TRUE(Mathf::Equal(vec4[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec4[1], (tT) - 1.0));

        ASSERT_TRUE(Mathf::Equal(vec5[0], (tT) - 1.0));
        ASSERT_TRUE(Mathf::Equal(vec5[1], (tT) 0.0));

        ASSERT_TRUE(Mathf::Equal(vec6[0], (tT) 1.0));
        ASSERT_TRUE(Mathf::Equal(vec6[1], (tT) 0.0));

    }

    static void TestLerp()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);

        Vector2< tT > vec3 = vec1.Lerp(vec2, (tT)0.4);

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)10.11 + ((tT)30.33 - (tT)10.11) * (tT)0.4));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)20.22 + ((tT)40.44 - (tT)20.22) * (tT)0.4));
    }

    static void TestNLerp()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(30.33, 40.44);

        Vector2< tT > vec3 = vec1.Nlerp(vec2, (tT)0.4);

        const tT dx = (tT)10.11 + ((tT)30.33 - (tT)10.11) * (tT)0.4;
        const tT dy = (tT)20.22 + ((tT)40.44 - (tT)20.22) * (tT)0.4;

        const tT l = (tT)Mathf::Sqrt((F64)(dx * dx + dy * dy));

        ASSERT_TRUE(Mathf::Equal(vec3[0], dx / l));
        ASSERT_TRUE(Mathf::Equal(vec3[1], dy / l));
    }

    static void TestAbs()
    {
        Vector2< tT > vec1(-10.11, -20.22);
        Vector2< tT > vec2 = vec1.Absolute();

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 10.11));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 20.22));
    }

    static void TestAngle()
    {
        Vector2< tT > vec1(2.5, 0.0);
        Vector2< tT > vec2(-1.0, 1.0);

        const Scalar a = vec1.Angle(vec2);

        ASSERT_TRUE(Mathf::Equal(a, (Scalar)(0.75f * Mathf::Pi< Scalar >())));
    }

    static void TestRotate()
    {
        Vector2< tT > vec1(1.0, 0.0);
        Vector2< tT > vec2(0.0, 1.0);
        vec2.Normalise();

        Vector2< tT > vec3 = vec1.Rotate(0.5f * Mathf::Pi< Scalar >());

        ASSERT_TRUE(Mathf::Equal(vec3[0], vec2[0]));
        ASSERT_TRUE(Mathf::Equal(vec3[1], vec2[1]));
    }

    static void TestAxis()
    {
        Vector2< tT > vec1(1.0, -1.0);

        const U32 min = vec1.MinAxis();
        const U32 max = vec1.MaxAxis();

        ASSERT_EQ(min, 1u);
        ASSERT_EQ(max, 0u);

        Vector2< tT > vec2(-1.0, 1.0);

        const U32 min2 = vec2.MinAxis();
        const U32 max2 = vec2.MaxAxis();

        ASSERT_EQ(min2, 0u);
        ASSERT_EQ(max2, 1u);
    }

    static void TestPlus()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(20.22, 40.44);

        Vector2< tT > vec3 = vec2 + vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)20.22 + (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)40.44 + (tT)20.22));
    }

    static void TestMin()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(20.22, 40.44);

        Vector2< tT > vec3 = vec2 - vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)(20.22 - 10.11)));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)(40.44 - 20.22)));
    }

    static void TestNeg()
    {
        Vector2< tT > vec1(10.11, 20.22);

        Vector2< tT > vec3 = -vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)(-10.11)));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)(-20.22)));
    }

    static void TestMul()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(20.22, 40.44);

        Vector2< tT > vec3 = vec2 * vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)20.22 * (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)40.44 * (tT)20.22));

        Vector2< tT > vec4 = vec2 * (tT) 50.55;

        ASSERT_TRUE(Mathf::Equal(vec4[0], (tT)20.22 * (tT)50.55));
        ASSERT_TRUE(Mathf::Equal(vec4[1], (tT)40.44 * (tT)50.55));

        Vector2< tT > vec5 = (tT) 60.66 * vec2;

        ASSERT_TRUE(Mathf::Equal(vec5[0], (tT)20.22 * (tT)60.66));
        ASSERT_TRUE(Mathf::Equal(vec5[1], (tT)40.44 * (tT)60.66));
    }

    static void TestDiv()
    {
        Vector2< tT > vec1(10.11, 20.22);
        Vector2< tT > vec2(20.22, 40.44);

        Vector2< tT > vec3 = vec2 / vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)(20.22 / 10.11)));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)(40.44 / 20.22)));

        Vector2< tT > vec4 = vec2 / (tT) 50.55;

        ASSERT_TRUE(Mathf::Equal(vec4[0], (tT)(20.22 / 50.55)));
        ASSERT_TRUE(Mathf::Equal(vec4[1], (tT)(40.44 / 50.55)));
    }
};


TEST(Vec2Test, ConstructAndAccess)
{
    Vector2DTest< F32 >::TestConstructAndAccess();
    Vector2DTest< F64 >::TestConstructAndAccess();
    Vector2DTest< S32 >::TestConstructAndAccess();
    Vector2DTest< S64 >::TestConstructAndAccess();
}

TEST(Vec2Test, IntegerCast)
{
    Vector2DTest< F32 >::TestIntegerCasts();
    Vector2DTest< F64 >::TestIntegerCasts();
    Vector2DTest< S32 >::TestIntegerCasts();
    Vector2DTest< S64 >::TestIntegerCasts();
}

TEST(Vec2Test, Assignment)
{
    Vector2DTest< F32 >::TestAssignment();
    Vector2DTest< F64 >::TestAssignment();
    Vector2DTest< S32 >::TestAssignment();
    Vector2DTest< S64 >::TestAssignment();
}

TEST(Vec2Test, MinAssignment)
{
    Vector2DTest< F32 >::TestMinAssignment();
    Vector2DTest< F64 >::TestMinAssignment();
    Vector2DTest< S32 >::TestMinAssignment();
    Vector2DTest< S64 >::TestMinAssignment();
}

TEST(Vec2Test, PlusAssignment)
{
    Vector2DTest< F32 >::TestPlusAssignment();
    Vector2DTest< F64 >::TestPlusAssignment();
    Vector2DTest< S32 >::TestPlusAssignment();
    Vector2DTest< S64 >::TestPlusAssignment();
}

TEST(Vec2Test, MulAssignment)
{
    Vector2DTest< F32 >::TestMulAssignment();
    Vector2DTest< F64 >::TestMulAssignment();
    Vector2DTest< S32 >::TestMulAssignment();
    Vector2DTest< S64 >::TestMulAssignment();
}

TEST(Vec2Test, DivAssignment)
{
    Vector2DTest< F32 >::TestDivAssignment();
    Vector2DTest< F64 >::TestDivAssignment();
    Vector2DTest< S32 >::TestDivAssignment();
    Vector2DTest< S64 >::TestDivAssignment();
}

TEST(Vec2Test, Equality)
{
    Vector2DTest< F32 >::TestEquality();
    Vector2DTest< F64 >::TestEquality();
    Vector2DTest< S32 >::TestEquality();
    Vector2DTest< S64 >::TestEquality();
}

TEST(Vec2Test, Set)
{
    Vector2DTest< F32 >::TestSet();
    Vector2DTest< F64 >::TestSet();
    Vector2DTest< S32 >::TestSet();
    Vector2DTest< S64 >::TestSet();
}

TEST(Vec2Test, Dot)
{
    Vector2DTest< F32 >::TestDot();
    Vector2DTest< F64 >::TestDot();
    Vector2DTest< S32 >::TestDot();
    Vector2DTest< S64 >::TestDot();
}

TEST(Vec2Test, Length)
{
    Vector2DTest< F32 >::TestLength();
    Vector2DTest< F64 >::TestLength();
    Vector2DTest< S32 >::TestLength();
    Vector2DTest< S64 >::TestLength();
}

TEST(Vec2Test, Distance)
{
    Vector2DTest< F32 >::TestDistance();
    Vector2DTest< F64 >::TestDistance();
    Vector2DTest< S32 >::TestDistance();
    Vector2DTest< S64 >::TestDistance();
}

TEST(Vec2Test, Normalise)
{
    Vector2DTest< F32 >::TestNormalise();
    Vector2DTest< F64 >::TestNormalise();
    Vector2DTest< S32 >::TestNormalise();
    Vector2DTest< S64 >::TestNormalise();
}

TEST(Vec2Test, Statics)
{
    Vector2DTest< F32 >::TestStatics();
    Vector2DTest< F64 >::TestStatics();
    Vector2DTest< S32 >::TestStatics();
    Vector2DTest< S64 >::TestStatics();
}

TEST(Vec2Test, Lerp)
{
    Vector2DTest< F32 >::TestLerp();
    Vector2DTest< F64 >::TestLerp();
    Vector2DTest< S32 >::TestLerp();
    Vector2DTest< S64 >::TestLerp();
}

TEST(Vec2Test, Nlerp)
{
    Vector2DTest< F32 >::TestNLerp();
    Vector2DTest< F64 >::TestNLerp();
    Vector2DTest< S32 >::TestNLerp();
    Vector2DTest< S64 >::TestNLerp();
}

TEST(Vec2Test, Abs)
{
    Vector2DTest< F32 >::TestAbs();
    Vector2DTest< F64 >::TestAbs();
    Vector2DTest< S32 >::TestAbs();
    Vector2DTest< S64 >::TestAbs();
}

TEST(Vec2Test, Angle)
{
    Vector2DTest< F32 >::TestAngle();
    Vector2DTest< F64 >::TestAngle();
    Vector2DTest< S32 >::TestAngle();
    Vector2DTest< S64 >::TestAngle();
}

TEST(Vec2Test, Rotate)
{
    Vector2DTest< F32 >::TestRotate();
    Vector2DTest< F64 >::TestRotate();
    Vector2DTest< S32 >::TestRotate();
    Vector2DTest< S64 >::TestRotate();
}

TEST(Vec2Test, Axis)
{
    Vector2DTest< F32 >::TestAxis();
    Vector2DTest< F64 >::TestAxis();
    Vector2DTest< S32 >::TestAxis();
    Vector2DTest< S64 >::TestAxis();
}

TEST(Vec2Test, Plus)
{
    Vector2DTest< F32 >::TestPlus();
    Vector2DTest< F64 >::TestPlus();
    Vector2DTest< S32 >::TestPlus();
    Vector2DTest< S64 >::TestPlus();
}

TEST(Vec2Test, Min)
{
    Vector2DTest< F32 >::TestMin();
    Vector2DTest< F64 >::TestMin();
    Vector2DTest< S32 >::TestMin();
    Vector2DTest< S64 >::TestMin();
}

TEST(Vec2Test, Neg)
{
    Vector2DTest< F32 >::TestNeg();
    Vector2DTest< F64 >::TestNeg();
    Vector2DTest< S32 >::TestNeg();
    Vector2DTest< S64 >::TestNeg();
}

TEST(Vec2Test, Mul)
{
    Vector2DTest< F32 >::TestMul();
    Vector2DTest< F64 >::TestMul();
    Vector2DTest< S32 >::TestMul();
    Vector2DTest< S64 >::TestMul();
}

TEST(Vec2Test, Div)
{
    Vector2DTest< F32 >::TestDiv();
    Vector2DTest< F64 >::TestDiv();
    Vector2DTest< S32 >::TestDiv();
    Vector2DTest< S64 >::TestDiv();
}



