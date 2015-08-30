#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec2i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

TEST(P(Vec2iTest), ConstructAndAccess)
{
    Vec2 testConst;
    Vec2 testConst1(20);
    Vec2 testConst2(10, 50);

    ASSERT_REAL_EQ(testConst1[0], 20);
    ASSERT_REAL_EQ(testConst1[1], 20);

    ASSERT_REAL_EQ(testConst2[0], 10);
    ASSERT_REAL_EQ(testConst2[1], 50);
}

TEST(P(Vec2Test), RealCast)
{
    Vec2i testConst(10, 50);
    Vec2  testCast(testConst);
    
    ASSERT_REAL_EQ(testCast[0], 10.0);
    ASSERT_REAL_EQ(testCast[1], 50.0);
}