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

/*
TEST(P(Vec2iTest), ConstructAndAccess)
{
    Vec2i testConst;
    Vec2i testConst1(20);
    Vec2i testConst2(10, 50);

    ASSERT_EQ(testConst1[0], 20);
    ASSERT_EQ(testConst1[1], 20);

    ASSERT_REAL_EQ(testConst2[0], 10);
    ASSERT_REAL_EQ(testConst2[1], 50);
}

TEST(P(Vec2iTest), RealCast)
{
    Vec2i testConst(10, 50);
    Vec2  testCast(testConst);
    
    ASSERT_REAL_EQ(testCast[0], 10.0);
    ASSERT_REAL_EQ(testCast[1], 50.0);
}
*/