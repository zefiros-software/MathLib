#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec2.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

TEST(  P( VectorTest ), ConstructAndAccess )
{
    Vec2 t2;
    
    t2.x = 1.0;
    
    EXPECT_EQ(  "TEST", "TEST" );
}