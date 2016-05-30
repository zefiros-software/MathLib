#include "gtest/gtest.h"

#include <iostream>
#include <cstdio>

#include <stdlib.h>

int main( int argc, char **argv )
{

#ifdef _WIN32
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
    //_crtBreakAlloc = 4885;
#endif

    testing::InitGoogleTest( &argc, argv );

    int result = RUN_ALL_TESTS();

    return 0;
}