#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec2i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

template< class Type >
struct Vector2DTest
{
    static void TestConstructAndAccess()
    {
        Vec2< Type > testConst;
        Vec2< Type > testConst1( (Type) 20.22 );
        Vec2< Type > testConst2( (Type) 10.11, (Type) 30.33 );
        
        ASSERT_REAL_EQ(testConst1[0], (Type) 20.22);
        ASSERT_REAL_EQ(testConst1[1], (Type) 20.22);
        
        ASSERT_REAL_EQ(testConst2[0], (Type) 10.11 );
        ASSERT_REAL_EQ(testConst2[1], (Type) 30.33 );
        
        // const version
        const Type val1 = testConst2[0];
        const Type val2 = testConst2[1];
        
        ASSERT_REAL_EQ(val1, (Type) 10.11 );
        ASSERT_REAL_EQ(val2, (Type) 30.33 );
        
        // mod
        testConst2[0] = 50.55;
        testConst2[1] = 60.66;
        
        ASSERT_REAL_EQ(testConst2[0], (Type) 50.55 );
        ASSERT_REAL_EQ(testConst2[1], (Type) 60.66 );
    }
    
    static void TestIntegerCasts()
    {
        Vec2I vec1( 10, 20 );
        
        Vec2< Type > vec2( vec1 );
        
        ASSERT_REAL_EQ(vec2[0], (Type) 10);
        ASSERT_REAL_EQ(vec2[1], (Type) 20);
        
        Vec2I vec3 = vec2.ToVec2I();
        
        ASSERT_EQ(vec3[0], (Type) 10);
        ASSERT_EQ(vec3[1], (Type) 20);
    }
    
    static void TestAssignment()
    {
        Vec2< Type > vec1( 10.11, 20.22 );
        Vec2< Type > vec2( 30.33, 40.44 );
        
        vec1 = vec2;
        
        ASSERT_REAL_EQ(vec1[0], (Type) 30.33);
        ASSERT_REAL_EQ(vec1[1], (Type) 40.44 );
    }
    
    static void TestMinAssignment()
    {
        Vec2< Type > vec1( 10.11, 20.22 );
        Vec2< Type > vec2( 30.33, 40.44 );
        
        vec2 -= vec1;
        
        ASSERT_REAL_EQ(vec2[0], (Type) ( 30.33 - 10.11 ) );
        ASSERT_REAL_EQ(vec2[1], (Type) ( 40.44 - 20.22 ) );
    }
    
    static void TestPlusAssignment()
    {
        Vec2< Type > vec1( 10.11, 20.22 );
        Vec2< Type > vec2( 30.33, 40.44 );
        
        vec2 += vec1;
        
        ASSERT_REAL_EQ(vec2[0], (Type) ( 30.33 + 10.11 ) );
        ASSERT_REAL_EQ(vec2[1], (Type) ( 40.44 + 20.22 ) );
    }
    
    static void TestMulAssignment()
    {
        Vec2< Type > vec1( 30.33, 40.44 );
        
        vec1 *= 10.11;
        
        ASSERT_REAL_EQ(vec1[0], (Type) ( 30.33 * 10.11 ) );
        ASSERT_REAL_EQ(vec1[1], (Type) ( 40.44 * 10.11 ) );
    }
    
    static void TestDivAssignment()
    {
        Vec2< Type > vec1( 30.33, 40.44 );
        
        vec1 /= 10.11;
        
        ASSERT_REAL_EQ(vec1[0], (Type) ( 30.33 / 10.11 ) );
        ASSERT_REAL_EQ(vec1[1], (Type) ( 40.44 / 10.11 ) );
    }
    
    static void TestEquality()
    {
        Vec2< Type > vec1( 10.11, 20.22 );
        Vec2< Type > vec2( 30.33, 40.44 );
        Vec2< Type > vec3( 30.33, 40.44 );
      
        ASSERT_TRUE( vec2 == vec3 );
        ASSERT_TRUE( vec1 != vec3 );
    }
    
    static void TestSetValue()
    {
        Vec2< Type > vec1( 10.11, 20.22 );
        
        vec1.SetValue( 30.33, 44.44 );
        
        ASSERT_REAL_EQ(vec1[0], (Type) 30.33 );
        ASSERT_REAL_EQ(vec1[1], (Type) 44.44 );
    }
};


TEST( P( Vec2Test ), ConstructAndAccess )
{
    Vector2DTest< F32 >::TestConstructAndAccess();
    Vector2DTest< F64 >::TestConstructAndAccess();
}

TEST(P(Vec2Test), IntegerCast)
{
    Vector2DTest< F32 >::TestIntegerCasts();
    Vector2DTest< F64 >::TestIntegerCasts();
}

TEST(P(Vec2Test), Assignment)
{
    Vector2DTest< F32 >::TestAssignment();
    Vector2DTest< F64 >::TestAssignment();
}

TEST(P(Vec2Test), MinAssignment)
{
    Vector2DTest< F32 >::TestMinAssignment();
    Vector2DTest< F64 >::TestMinAssignment();
}

TEST(P(Vec2Test), PlusAssignment)
{
    Vector2DTest< F32 >::TestPlusAssignment();
    Vector2DTest< F64 >::TestPlusAssignment();
}

TEST(P(Vec2Test), MulAssignment)
{
    Vector2DTest< F32 >::TestMulAssignment();
    Vector2DTest< F64 >::TestMulAssignment();
}

TEST(P(Vec2Test), DivAssignment)
{
    Vector2DTest< F32 >::TestDivAssignment();
    Vector2DTest< F64 >::TestDivAssignment();
}

TEST(P(Vec2Test), Equality )
{
    Vector2DTest< F32 >::TestEquality();
    Vector2DTest< F64 >::TestEquality();
}

TEST(P(Vec2Test), SetValue )
{
    Vector2DTest< F32 >::TestSetValue();
    Vector2DTest< F64 >::TestSetValue();
}

/*

TEST( P(Vec2Test), FP_Distance )
{
    Vec2 testConst1(4.89);
    Vec2 testConst2(10.11, 50.55);

    Real dist = testConst1.Distance(testConst2);

    ASSERT_REAL_EQ(dist, Mathf::Sqrt( Mathf::Square(4.89-10.11) + Mathf::Square(4.89-50.55)));
}

*/


