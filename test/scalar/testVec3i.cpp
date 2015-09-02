#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec3.h"
#include "math/scalar/vec2i.h"
#include "math/scalar/vec3i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

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