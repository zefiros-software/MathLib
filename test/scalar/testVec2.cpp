#include "gtest/gtest.h"

#include "helper.h"

#include "types.h"
#include "scalar/vec2.h"
#include "scalar/vec2i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

TEST( P( Vec2Test ), Vec2_ConstructAndAccess )
{
    Vec2 testConst;
    Vec2 testConst1(20.22);
    Vec2 testConst2( 10.11, 50.55 );
    
    ASSERT_REAL_EQ(testConst1[0], 20.22);
    ASSERT_REAL_EQ(testConst1[1], 20.22);

    ASSERT_REAL_EQ(testConst2[0], 10.11 );
    ASSERT_REAL_EQ(testConst2[1], 50.55 );
}

 
TEST( P(Vec2Test), FP_Distance )
{
    Vec2 testConst1(4.89);
    Vec2 testConst2(10.11, 50.55);

    Real dist = testConst1.Distance(testConst2);

    ASSERT_REAL_EQ(dist, Mathf::Sqrt( Mathf::Square(4.89-10.11) + Mathf::Square(4.89-50.55)));
}



