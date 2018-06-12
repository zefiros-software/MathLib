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
#include "math/vec3.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

/*
TEST(P(Vec3iTest), ConstructAndAccess)
{
    Vec3i testConst;
    Vec3i testConst1(10);
    Vec3i testConst2(10, 20, 30);

    ASSERT_EQ(testConst1[0], 10);
    ASSERT_EQ(testConst1[1], 10);
    ASSERT_EQ(testConst1[2], 10);

    ASSERT_EQ(testConst2[0], 10);
    ASSERT_EQ(testConst2[1], 20);
    ASSERT_EQ(testConst2[2], 30);

    Vec2i testConst3(10, 20);
    Vec3i testConst4(testConst3,30);

    ASSERT_EQ(testConst4[0], 10);
    ASSERT_EQ(testConst4[1], 20);
    ASSERT_EQ(testConst4[2], 30);
}

TEST(P(Vec3iTest), RealCast)
{
    Vec3i testConst(10, 20, 30);
    Vec3  testCast(testConst);

    ASSERT_REAL_EQ(testCast[0], 10.0);
    ASSERT_REAL_EQ(testCast[1], 20.0);
    ASSERT_REAL_EQ(testCast[2], 30.0);
}
*/