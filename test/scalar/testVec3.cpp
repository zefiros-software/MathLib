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
#include "math/vec2.h"
#include "math/vec3.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>


template< class tT >
struct Vector3DTest
{
    static void TestConstructAndAccess()
    {
        Vector3< tT > testConst;
        ASSERT_TRUE(Mathf::Equal(testConst[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(testConst[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(testConst[2], (tT) 0.0));
        Vector3< tT > testConst1((tT) 20.22);
        Vector3< tT > testConst2((tT) 10.11, (tT) 30.33, (tT) 40.33);

        ASSERT_TRUE(Mathf::Equal(testConst1[0], (tT) 20.22));
        ASSERT_TRUE(Mathf::Equal(testConst1[1], (tT) 20.22));
        ASSERT_TRUE(Mathf::Equal(testConst1[2], (tT) 20.22));

        ASSERT_TRUE(Mathf::Equal(testConst2[0], (tT) 10.11));
        ASSERT_TRUE(Mathf::Equal(testConst2[1], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(testConst2[2], (tT) 40.33));

        const tT val1 = testConst2[0];
        const tT val2 = testConst2[1];
        const tT val3 = testConst2[2];

        ASSERT_TRUE(Mathf::Equal(val1, (tT) 10.11));
        ASSERT_TRUE(Mathf::Equal(val2, (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(val3, (tT) 40.33));

        testConst2[0] = (tT)50.55;
        testConst2[1] = (tT)60.66;
        testConst2[2] = (tT)70.66;

        ASSERT_TRUE(Mathf::Equal(testConst2[0], (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(testConst2[1], (tT) 60.66));
        ASSERT_TRUE(Mathf::Equal(testConst2[2], (tT) 70.66));
    }

    static void TestIntegerCasts()
    {
        Vec3i vec1(10, 20, 30);

        Vector3< tT > vec2(vec1);

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)10));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)20));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT)30));
    }

    static void TestAssignment()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 50.55);
        const Vector3< tT > vec3(30.33, 40.44, 50.55);

        vec1 = vec2;

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec1[2], (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(vec1.Data()[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec1.Data()[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec1.Data()[2], (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(vec3.Data()[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec3.Data()[1], (tT) 40.44));
        ASSERT_TRUE(Mathf::Equal(vec3.Data()[2], (tT) 50.55));
    }

    static void TestMinAssignment()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 50.55);

        vec2 -= vec1;

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)30.33 - (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)40.44 - (tT)20.22));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT)50.55 - (tT)30.33));
    }

    static void TestPlusAssignment()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 50.55);

        vec2 += vec1;

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)30.33 + (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)40.44 + (tT)20.22));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT)50.55 + (tT)30.33));
    }

    static void TestMulAssignment()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);

        vec1 *= (tT)10.11;

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT)10.11 * (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT)20.22 * (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec1[2], (tT)30.33 * (tT)10.11));
    }

    static void TestDivAssignment()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);

        vec1 /= (tT)10.11;

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT)10.11 / (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT)20.22 / (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec1[2], (tT)30.33 / (tT)10.11));
    }

    static void TestEquality()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 30.33);
        Vector3< tT > vec3(30.33, 40.44, 30.33);
        Vector3< tT > vec4(0.0, 0.0, 0.0);
        Vector3< tT > vec5(30.33, 41.44, 30.33);
        Vector3< tT > vec6(0.0, 40.45, 30.33);
        Vector3< tT > vec7(0.0, 0.0, 30.33);
        Vector3< tT > vec8(0.0, 0.0, 40.33);

        ASSERT_TRUE(vec2 == vec3);
        ASSERT_TRUE(vec2 != vec5);
        ASSERT_TRUE(vec1 != vec3);
        ASSERT_TRUE(vec7 != vec8);
        ASSERT_TRUE(vec4.IsZero());
        ASSERT_FALSE(vec5.IsZero());
        ASSERT_FALSE(vec6.IsZero());
        ASSERT_FALSE(vec7.IsZero());
        ASSERT_TRUE(vec4.IsFuzzyZero());
    }

    static void TestSet()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);

        vec1.Set((tT)30.33, (tT)44.44, (tT)55.55);

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 30.33));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 44.44));
        ASSERT_TRUE(Mathf::Equal(vec1[2], (tT)55.55));

        vec1.X((tT)50.55);
        vec1.Y((tT)60.66);
        vec1.Z((tT)70.77);

        ASSERT_TRUE(Mathf::Equal(vec1.X(), (tT) 50.55));
        ASSERT_TRUE(Mathf::Equal(vec1.Y(), (tT) 60.66));
        ASSERT_TRUE(Mathf::Equal(vec1.Z(), (tT) 70.77));

        vec1.Clear();

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec1[2], (tT) 0.0));

        Vector3< tT > vec2(10.11, 20.22, 30.33);
        vec2.Clear();

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT) 0.0));
    }

    static void TestDot()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 50.55);

        const tT dotr = vec1.Dot(vec2);

        ASSERT_TRUE(Mathf::Equal(dotr, (tT)10.11 * (tT)30.33 + (tT)20.22 * (tT)40.44 + (tT)30.33 * (tT)50.55));
    }

    static void TestLength()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);

        const Scalar l2 = vec1.Length2();
        const Scalar l = vec1.Length();

        ASSERT_TRUE(Mathf::Equal((tT)l2, (tT)10.11 * (tT)10.11 + (tT)20.22 * (tT)20.22 + (tT)30.33 * (tT)30.33));
        ASSERT_TRUE(Mathf::Equal((tT)l, (tT)Mathf::Sqrt((F64)((tT)10.11 * (tT)10.11 + (tT)20.22 * (tT)20.22 + (tT)30.33 * (tT)30.33))));
    }

    static void TestDistance()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 60.66, 80.88);

        const tT dx = (tT)30.33 - (tT)10.11;
        const tT dy = (tT)60.66 - (tT)20.22;
        const tT dz = (tT)80.88 - (tT)30.33;

        const Scalar d2 = vec1.Distance2(vec2);
        const Scalar d = vec1.Distance(vec2);

        ASSERT_TRUE(Mathf::Equal((tT)d2, dx * dx + dy * dy + dz * dz));
        ASSERT_TRUE(Mathf::Equal((tT)d, (tT)Mathf::Sqrt((F64)(dx * dx + dy * dy + dz * dz))));
    }

    static void TestNormalise()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        const Scalar l_1 = vec1.Length();

        vec1.Normalise();
        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT)(10.11 / l_1)));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT)(20.22 / l_1)));

        Vector3< tT > vec2(0.0, 0.0, 3.33);
        const Scalar l_2 = vec2.Length();

        vec2.SafeNormalise();
        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT)(0.0 / l_2)));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT)(0.0 / l_2)));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT)(3.33 / l_2)));

        Vector3< tT > vec3;
        vec3.SafeNormalise();
        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)1.0));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)0.0));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)0.0));
    }

    static void TestStatics()
    {
        Vector3< tT > vec1 = Vector3< tT >::Zeros();
        Vector3< tT > vec2 = Vector3< tT >::Ones();
        Vector3< tT > vec3 = Vector3< tT >::Up();
        Vector3< tT > vec4 = Vector3< tT >::Down();
        Vector3< tT > vec5 = Vector3< tT >::Left();
        Vector3< tT > vec6 = Vector3< tT >::Right();
        Vector3< tT > vec7 = Vector3< tT >::Forward();
        Vector3< tT > vec8 = Vector3< tT >::Back();

        ASSERT_TRUE(Mathf::Equal(vec1[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec1[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec1[2], (tT) 0.0));

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 1.0));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 1.0));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT) 1.0));

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)1.0));

        ASSERT_TRUE(Mathf::Equal(vec4[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec4[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec4[2], (tT) - 1.0));

        ASSERT_TRUE(Mathf::Equal(vec5[0], (tT) - 1.0));
        ASSERT_TRUE(Mathf::Equal(vec5[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec5[2], (tT) 0.0));

        ASSERT_TRUE(Mathf::Equal(vec6[0], (tT) 1.0));
        ASSERT_TRUE(Mathf::Equal(vec6[1], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec6[2], (tT) 0.0));

        ASSERT_TRUE(Mathf::Equal(vec7[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec7[1], (tT) 1.0));
        ASSERT_TRUE(Mathf::Equal(vec7[2], (tT) 0.0));

        ASSERT_TRUE(Mathf::Equal(vec8[0], (tT) 0.0));
        ASSERT_TRUE(Mathf::Equal(vec8[1], (tT) - 1.0));
        ASSERT_TRUE(Mathf::Equal(vec8[2], (tT) 0.0));

    }

    static void TestLerp()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 50.55);

        Vector3< tT > vec3 = vec1.Lerp(vec2, (tT)0.4);

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)10.11 + ((tT)30.33 - (tT)10.11) * (tT)0.4));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)20.22 + ((tT)40.44 - (tT)20.22) * (tT)0.4));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)30.33 + ((tT)50.55 - (tT)30.33) * (tT)0.4));
    }

    static void TestNLerp()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(30.33, 40.44, 50.55);

        Vector3< tT > vec3 = vec1.Nlerp(vec2, (tT)0.4);

        const tT dx = (tT)10.11 + ((tT)30.33 - (tT)10.11) * (tT)0.4;
        const tT dy = (tT)20.22 + ((tT)40.44 - (tT)20.22) * (tT)0.4;
        const tT dz = (tT)30.33 + ((tT)50.55 - (tT)30.33) * (tT)0.4;

        const tT l = (tT)Mathf::Sqrt((F64)(dx * dx + dy * dy + dz * dz));

        ASSERT_TRUE(Mathf::Equal(vec3[0], dx / l));
        ASSERT_TRUE(Mathf::Equal(vec3[1], dy / l));
        ASSERT_TRUE(Mathf::Equal(vec3[2], dz / l));
    }

    static void TestAbs()
    {
        Vector3< tT > vec1(-10.11, -20.22, -30.33);
        Vector3< tT > vec2 = vec1.Absolute();

        ASSERT_TRUE(Mathf::Equal(vec2[0], (tT) 10.11));
        ASSERT_TRUE(Mathf::Equal(vec2[1], (tT) 20.22));
        ASSERT_TRUE(Mathf::Equal(vec2[2], (tT) 30.33));
    }

    static void TestAngle()
    {
        Vector3< tT > vec1(2.5, 0.0, 0.0);
        Vector3< tT > vec2(-1.0, 1.0, 0.0);

        const Scalar a = vec1.Angle(vec2);

        ASSERT_TRUE(Mathf::Equal(a, (Scalar)(0.75f * Mathf::Pi< Scalar >())));
    }

    static void TestRotate()
    {
        Vector3< tT > vec1(1.0, 0.0, 0.0);
        Vector3< tT > vec2(0.0, 1.0, 0.0);
        vec2.Normalise();

        Vector3< tT > vec3 = vec1.Rotate(Vector3< tT >(0.0, 0.0, 1.0), 0.5f * Mathf::Pi< Scalar >());

        ASSERT_TRUE(Mathf::Equal(vec3[0], vec2[0]));
        ASSERT_TRUE(Mathf::Equal(vec3[1], vec2[1]));
        ASSERT_TRUE(Mathf::Equal(vec3[2], vec2[2]));
    }

    static void TestAxis()
    {
        Vector3< tT > vec1(1.0, -1.0, 0.0);

        const U32 min = vec1.MinAxis();
        const U32 max = vec1.MaxAxis();

        ASSERT_EQ(min, 1u);
        ASSERT_EQ(max, 0u);

        Vector3< tT > vec2(-1.0, 1.0, 0.0);

        const U32 min2 = vec2.MinAxis();
        const U32 max2 = vec2.MaxAxis();

        ASSERT_EQ(min2, 0u);
        ASSERT_EQ(max2, 1u);

        Vector3< tT > vec3(1.0, 0.0, -1.0);

        const U32 min3 = vec3.MinAxis();
        const U32 max3 = vec3.MaxAxis();

        ASSERT_EQ(min3, 2u);
        ASSERT_EQ(max3, 0u);

        Vector3< tT > vec4(-1.0, 0.0, 1.0);

        const U32 min4 = vec4.MinAxis();
        const U32 max4 = vec4.MaxAxis();

        ASSERT_EQ(min4, 0u);
        ASSERT_EQ(max4, 2u);

        Vector3< tT > vec5(0.0, 1.0, -1.0);

        const U32 min5 = vec5.MinAxis();
        const U32 max5 = vec5.MaxAxis();

        ASSERT_EQ(min5, 2u);
        ASSERT_EQ(max5, 1u);

        Vector3< tT > vec6(0.0, -1.0, 1.0);

        const U32 min6 = vec6.MinAxis();
        const U32 max6 = vec6.MaxAxis();

        ASSERT_EQ(min6, 1u);
        ASSERT_EQ(max6, 2u);
    }

    static void TestPlus()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(20.22, 40.44, 50.55);

        Vector3< tT > vec3 = vec2 + vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)20.22 + (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)40.44 + (tT)20.22));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)50.55 + (tT)30.33));
    }

    static void TestMin()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(20.22, 40.44, 50.55);

        Vector3< tT > vec3 = vec2 - vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)(20.22 - 10.11)));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)(40.44 - 20.22)));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)(50.55 - 30.33)));
    }

    static void TestNeg()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);

        Vector3< tT > vec3 = -vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)(-10.11)));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)(-20.22)));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)(-30.33)));
    }

    static void TestMul()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(20.22, 40.44, 50.55);

        Vector3< tT > vec3 = vec2 * vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)20.22 * (tT)10.11));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)40.44 * (tT)20.22));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)50.55 * (tT)30.33));

        Vector3< tT > vec4 = vec2 * (tT) 50.55;

        ASSERT_TRUE(Mathf::Equal(vec4[0], (tT)20.22 * (tT)50.55));
        ASSERT_TRUE(Mathf::Equal(vec4[1], (tT)40.44 * (tT)50.55));
        ASSERT_TRUE(Mathf::Equal(vec4[2], (tT)50.55 * (tT)50.55));

        Vector3< tT > vec5 = (tT) 60.66 * vec2;

        ASSERT_TRUE(Mathf::Equal(vec5[0], (tT)20.22 * (tT)60.66));
        ASSERT_TRUE(Mathf::Equal(vec5[1], (tT)40.44 * (tT)60.66));
        ASSERT_TRUE(Mathf::Equal(vec5[2], (tT)50.55 * (tT)60.66));
    }

    static void TestDiv()
    {
        Vector3< tT > vec1(10.11, 20.22, 30.33);
        Vector3< tT > vec2(20.22, 40.44, 50.55);

        Vector3< tT > vec3 = vec2 / vec1;

        ASSERT_TRUE(Mathf::Equal(vec3[0], (tT)(20.22 / 10.11)));
        ASSERT_TRUE(Mathf::Equal(vec3[1], (tT)(40.44 / 20.22)));
        ASSERT_TRUE(Mathf::Equal(vec3[2], (tT)(50.55 / 30.33)));

        Vector3< tT > vec4 = vec2 / (tT) 50.55;

        ASSERT_TRUE(Mathf::Equal(vec4[0], (tT)20.22 / (tT)50.55));
        ASSERT_TRUE(Mathf::Equal(vec4[1], (tT)40.44 / (tT)50.55));
        ASSERT_TRUE(Mathf::Equal(vec4[2], ((tT)50.55) / (tT)50.55));
    }
};


TEST(Vec3Test, ConstructAndAccess)
{
    Vector3DTest< F32 >::TestConstructAndAccess();
    Vector3DTest< F64 >::TestConstructAndAccess();
    Vector3DTest< S32 >::TestConstructAndAccess();
    Vector3DTest< S64 >::TestConstructAndAccess();
}

TEST(Vec3Test, IntegerCast)
{
    Vector3DTest< F32 >::TestIntegerCasts();
    Vector3DTest< F64 >::TestIntegerCasts();
    Vector3DTest< S32 >::TestIntegerCasts();
    Vector3DTest< S64 >::TestIntegerCasts();
}

TEST(Vec3Test, Assignment)
{
    Vector3DTest< F32 >::TestAssignment();
    Vector3DTest< F64 >::TestAssignment();
    Vector3DTest< S32 >::TestAssignment();
    Vector3DTest< S64 >::TestAssignment();
}

TEST(Vec3Test, MinAssignment)
{
    Vector3DTest< F32 >::TestMinAssignment();
    Vector3DTest< F64 >::TestMinAssignment();
    Vector3DTest< S32 >::TestMinAssignment();
    Vector3DTest< S64 >::TestMinAssignment();
}

TEST(Vec3Test, PlusAssignment)
{
    Vector3DTest< F32 >::TestPlusAssignment();
    Vector3DTest< F64 >::TestPlusAssignment();
    Vector3DTest< S32 >::TestPlusAssignment();
    Vector3DTest< S64 >::TestPlusAssignment();
}

TEST(Vec3Test, MulAssignment)
{
    Vector3DTest< F32 >::TestMulAssignment();
    Vector3DTest< F64 >::TestMulAssignment();
    Vector3DTest< S32 >::TestMulAssignment();
    Vector3DTest< S64 >::TestMulAssignment();
}

TEST(Vec3Test, DivAssignment)
{
    Vector3DTest< F32 >::TestDivAssignment();
    Vector3DTest< F64 >::TestDivAssignment();
    Vector3DTest< S32 >::TestDivAssignment();
    Vector3DTest< S64 >::TestDivAssignment();
}

TEST(Vec3Test, Equality)
{
    Vector3DTest< F32 >::TestEquality();
    Vector3DTest< F64 >::TestEquality();
    Vector3DTest< S32 >::TestEquality();
    Vector3DTest< S64 >::TestEquality();
}

TEST(Vec3Test, Set)
{
    Vector3DTest< F32 >::TestSet();
    Vector3DTest< F64 >::TestSet();
    Vector3DTest< S32 >::TestSet();
    Vector3DTest< S64 >::TestSet();
}

TEST(Vec3Test, Dot)
{
    Vector3DTest< F32 >::TestDot();
    Vector3DTest< F64 >::TestDot();
    Vector3DTest< S32 >::TestDot();
    Vector3DTest< S64 >::TestDot();
}

TEST(Vec3Test, Length)
{
    Vector3DTest< F32 >::TestLength();
    Vector3DTest< F64 >::TestLength();
    Vector3DTest< S32 >::TestLength();
    Vector3DTest< S64 >::TestLength();
}

TEST(Vec3Test, Distance)
{
    Vector3DTest< F32 >::TestDistance();
    Vector3DTest< F64 >::TestDistance();
    Vector3DTest< S32 >::TestDistance();
    Vector3DTest< S64 >::TestDistance();
}

TEST(Vec3Test, Normalise)
{
    Vector3DTest< F32 >::TestNormalise();
    Vector3DTest< F64 >::TestNormalise();
    Vector3DTest< S32 >::TestNormalise();
    Vector3DTest< S64 >::TestNormalise();
}

TEST(Vec3Test, Statics)
{
    Vector3DTest< F32 >::TestStatics();
    Vector3DTest< F64 >::TestStatics();
    Vector3DTest< S32 >::TestStatics();
    Vector3DTest< S64 >::TestStatics();
}

TEST(Vec3Test, Lerp)
{
    Vector3DTest< F32 >::TestLerp();
    Vector3DTest< F64 >::TestLerp();
    Vector3DTest< S32 >::TestLerp();
    Vector3DTest< S64 >::TestLerp();
}

TEST(Vec3Test, Nlerp)
{
    Vector3DTest< F32 >::TestNLerp();
    Vector3DTest< F64 >::TestNLerp();
    Vector3DTest< S32 >::TestNLerp();
    Vector3DTest< S64 >::TestNLerp();
}

TEST(Vec3Test, Abs)
{
    Vector3DTest< F32 >::TestAbs();
    Vector3DTest< F64 >::TestAbs();
    Vector3DTest< S32 >::TestAbs();
    Vector3DTest< S64 >::TestAbs();
}

TEST(Vec3Test, Angle)
{
    Vector3DTest< F32 >::TestAngle();
    Vector3DTest< F64 >::TestAngle();
    Vector3DTest< S32 >::TestAngle();
    Vector3DTest< S64 >::TestAngle();
}

TEST(Vec3Test, Rotate)
{
    Vector3DTest< F32 >::TestRotate();
    Vector3DTest< F64 >::TestRotate();
    Vector3DTest< S32 >::TestRotate();
    Vector3DTest< S64 >::TestRotate();
}

TEST(Vec3Test, Axis)
{
    Vector3DTest< F32 >::TestAxis();
    Vector3DTest< F64 >::TestAxis();
    Vector3DTest< S32 >::TestAxis();
    Vector3DTest< S64 >::TestAxis();
}

TEST(Vec3Test, Plus)
{
    Vector3DTest< F32 >::TestPlus();
    Vector3DTest< F64 >::TestPlus();
    Vector3DTest< S32 >::TestPlus();
    Vector3DTest< S64 >::TestPlus();
}

TEST(Vec3Test, Min)
{
    Vector3DTest< F32 >::TestMin();
    Vector3DTest< F64 >::TestMin();
    Vector3DTest< S32 >::TestMin();
    Vector3DTest< S64 >::TestMin();
}

TEST(Vec3Test, Neg)
{
    Vector3DTest< F32 >::TestNeg();
    Vector3DTest< F64 >::TestNeg();
    Vector3DTest< S32 >::TestNeg();
    Vector3DTest< S64 >::TestNeg();
}

TEST(Vec3Test, Mul)
{
    Vector3DTest< F32 >::TestMul();
    Vector3DTest< F64 >::TestMul();
    Vector3DTest< S32 >::TestMul();
    Vector3DTest< S64 >::TestMul();
}

TEST(Vec3Test, Div)
{
    Vector3DTest< F32 >::TestDiv();
    Vector3DTest< F64 >::TestDiv();
    Vector3DTest< S32 >::TestDiv();
    Vector3DTest< S64 >::TestDiv();
}



