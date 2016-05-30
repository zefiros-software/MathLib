#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec3.h"
#include "math/scalar/vec4.h"
#include "math/scalar/vec4i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

/*
TEST(P(Vec4Test), ConstructAndAccess)
{
    Vec4 testConst;
    Vec4 testConst1(10.123);
    Vec4 testConst2(10.123, 20.456, 30.789, 40.012);

    ASSERT_REAL_EQ(testConst1[0], 10.123);
    ASSERT_REAL_EQ(testConst1[1], 10.123);
    ASSERT_REAL_EQ(testConst1[2], 10.123);
    ASSERT_REAL_EQ(testConst1[3], 10.123);
    
    ASSERT_REAL_EQ(testConst2[0], 10.123);
    ASSERT_REAL_EQ(testConst2[1], 20.456);
    ASSERT_REAL_EQ(testConst2[2], 30.789);
    ASSERT_REAL_EQ(testConst2[3], 40.012);
    
    Vec2 testConst3(10.123, 20.456);
    Vec2 testConst4(30.789, 40.012);
 
    Vec4 testConst5( testConst3, testConst4 );
    
    ASSERT_REAL_EQ(testConst5[0], 10.123);
    ASSERT_REAL_EQ(testConst5[1], 20.456);
    ASSERT_REAL_EQ(testConst5[2], 30.789);
    ASSERT_REAL_EQ(testConst5[3], 40.012);
    
    Vec3 testConst6(10.123, 20.456, 30.789);
    
    Vec4 testConst7( testConst6, 40.012 );
    
    ASSERT_REAL_EQ(testConst7[0], 10.123);
    ASSERT_REAL_EQ(testConst7[1], 20.456);
    ASSERT_REAL_EQ(testConst7[2], 30.789);
    ASSERT_REAL_EQ(testConst7[3], 40.012);
    
    Vec4 testConst8( 40.012, testConst6 );
    
    ASSERT_REAL_EQ(testConst8[0], 40.012);
    ASSERT_REAL_EQ(testConst8[1], 10.123);
    ASSERT_REAL_EQ(testConst8[2], 20.456);
    ASSERT_REAL_EQ(testConst8[3], 30.789);
}

TEST(P(Vec4Test), IntegerCast)
{
    Vec4  testConst(10.123, 20.456, 30.789, 40.012);
    Vec4i testCast(testConst);

    ASSERT_EQ(testCast[0], 10);
    ASSERT_EQ(testCast[1], 20);
    ASSERT_EQ(testCast[2], 30);
    ASSERT_EQ(testCast[3], 40);
}

TEST(P(Vec4Test), Length)
{
    Vec4  testConst1(10.123, 20.456, 30.789, 40.012);
    //Vec4  testConst2(20.456, 30.789, 40.012, 50.345);
    
    ASSERT_REAL_EQ( testConst1.Length(), Mathf::Sqrt( 10.123*10.123 + 
                                                      20.456*20.456 + 
                                                      30.789*30.789 + 
                                                      40.012*40.012 ));
}

TEST(P(Vec4Test), Distance)
{
    Vec4  testConst1(10.123, 20.456, 30.789, 40.012);
    Vec4  testConst2(20.456, 30.789, 40.012, 50.345);
    
    ASSERT_REAL_EQ( testConst1.Distance(testConst2),  Mathf::Sqrt( Mathf::Square( 10.123-20.456 ) + 
                                                        	       Mathf::Square( 20.456-30.789 ) + 
                                                                   Mathf::Square( 30.789-40.012 ) + 
                                                                   Mathf::Square( 40.012-50.345 ) ) );
}

TEST(P(Vec4Test), Normalise)
{
    Vec4  testConst1(10.123, 20.456, 30.789, 40.012);
    
    Vec4  testConst3 = testConst1.Normalise();
    
    const Real length1 = testConst1.Length();
                                                                   
    ASSERT_REAL_EQ(testConst3[0], testConst1[0] / length1);
    ASSERT_REAL_EQ(testConst3[1], testConst1[1] / length1);
    ASSERT_REAL_EQ(testConst3[2], testConst1[2] / length1);
    ASSERT_REAL_EQ(testConst3[3], testConst1[3] / length1);
    
    Vec4  testConst4 = testConst1.SafeNormalise();
    
    ASSERT_REAL_EQ(testConst4[0], testConst1[0] / length1);
    ASSERT_REAL_EQ(testConst4[1], testConst1[1] / length1);
    ASSERT_REAL_EQ(testConst4[2], testConst1[2] / length1);
    ASSERT_REAL_EQ(testConst4[3], testConst1[3] / length1);
    
    Vec4  testConst5(0.0);
    
    Vec4  testConst6 = testConst5.SafeNormalise();
    
    ASSERT_REAL_EQ(testConst6[0], 1.0);
    ASSERT_REAL_EQ(testConst6[1], 0.0);
    ASSERT_REAL_EQ(testConst6[2], 0.0);
    ASSERT_REAL_EQ(testConst6[3], 0.0);
}
*/

// TODO
// Interpolation & Angle