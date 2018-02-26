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
#include "math/scalar/vec3.h"
#include "math/scalar/matrix3.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

/*
TEST(P(Mat3Test), ConstructAndAccess)
{
    Matrix3 testMat( 0.1, 0.2, 0.3,
                     0.4, 0.5, 0.6,
                     0.7, 0.8, 0.9);

    ASSERT_REAL_EQ(testMat[0][0], 0.1);
    ASSERT_REAL_EQ(testMat[0][1], 0.2);
    ASSERT_REAL_EQ(testMat[0][2], 0.3);
    ASSERT_REAL_EQ(testMat[1][0], 0.4);
    ASSERT_REAL_EQ(testMat[1][1], 0.5);
    ASSERT_REAL_EQ(testMat[1][2], 0.6);
    ASSERT_REAL_EQ(testMat[2][0], 0.7);
    ASSERT_REAL_EQ(testMat[2][1], 0.8);
    ASSERT_REAL_EQ(testMat[2][2], 0.9);

    Vec3 row1(0.7, 0.8, 0.9);
    Vec3 row2(0.1, 0.2, 0.3);
    Vec3 row3(0.4, 0.5, 0.6);

    Matrix3 testMat2(row1, row2, row3);

    ASSERT_REAL_EQ(testMat2[0][0], 0.7);
    ASSERT_REAL_EQ(testMat2[0][1], 0.8);
    ASSERT_REAL_EQ(testMat2[0][2], 0.9);
    ASSERT_REAL_EQ(testMat2[1][0], 0.1);
    ASSERT_REAL_EQ(testMat2[1][1], 0.2);
    ASSERT_REAL_EQ(testMat2[1][2], 0.3);
    ASSERT_REAL_EQ(testMat2[2][0], 0.4);
    ASSERT_REAL_EQ(testMat2[2][1], 0.5);
    ASSERT_REAL_EQ(testMat2[2][2], 0.6);
}
*/
