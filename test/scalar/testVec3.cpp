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
#include "math/scalar/vec3.h"
#include "math/scalar/vec3i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

/*
TEST(P(Vec3Test), ConstructAndAccess)
{
    Vec3 testConst;
    Vec3 testConst1(10.123);
    Vec3 testConst2(10.123, 20.456, 30.789);

    ASSERT_REAL_EQ(testConst1[0], 10.123);
    ASSERT_REAL_EQ(testConst1[1], 10.123);
    ASSERT_REAL_EQ(testConst1[2], 10.123);

    ASSERT_REAL_EQ(testConst2[0], 10.123);
    ASSERT_REAL_EQ(testConst2[1], 20.456);
    ASSERT_REAL_EQ(testConst2[2], 30.789);

    Vec2 testConst3(10.123, 20.456 );
    Vec3 testConst4( testConst3, 30.789 );

    ASSERT_REAL_EQ(testConst4[0], 10.123);
    ASSERT_REAL_EQ(testConst4[1], 20.456);
    ASSERT_REAL_EQ(testConst4[2], 30.789);
}

TEST(P(Vec3Test), IntegerCast)
{
    Vec3  testConst(10.123, 20.456, 30.789);
    Vec3i testCast(testConst);

    ASSERT_EQ(testCast[0], 10);
    ASSERT_EQ(testCast[1], 20);
    ASSERT_EQ(testCast[2], 30);
}
*/