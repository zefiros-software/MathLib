local root      = "../../"

solution "math"

    location( root .. "math/" )
	objdir( root .. "bin/obj/" )
	debugdir( root .. "bin/" )
	
	configurations { "Debug", "Release", "Coverage"  }

	platforms { "x64" }

	vectorextensions "SSE2"

	floatingpoint "Fast"

	warnings "Extra"

	flags "Unicode"	

    configuration "x64"
		targetdir( root .. "bin/x64/" )
		architecture "x64"

	configuration "Debug"
		targetsuffix "d"
		defines "DEBUG"
		flags "Symbols"
		optimize "Off"

    configuration "Release"		
		flags "LinkTimeOptimization"
		optimize "Speed"
        
    configuration "Coverage"
        targetsuffix "cd"
        flags "Symbols"
        links "gcov"
        buildoptions "-coverage"
				
	configuration {}
	
	project "math-test"
		location(  root .. "test/" )
		
		kind "ConsoleApp"
		flags "WinMain"
		defines "GTEST_HAS_TR1_TUPLE=0"
		
		includedirs {
			root .. "extern/gtest/include/",
			root .. "extern/gtest/",
			root .. "math/include/",
            root .. "test/",
			root .. "test/scalar/",
            root .. "test/simd/"
			}	
		
		files { 
			root .. "extern/gtest/src/gtest-all.cc",
			root .. "test/**.cpp",
			root .. "test/**.h"
			}
			
		configuration "gmake"
			links "pthread"
            buildoptions( "-mfma" )
            buildoptions( "-mavx2" )
            buildoptions( "-mavx" )
            buildoptions( "-msse" )
            buildoptions( "-march=native" )
			
    project "math"
        targetname "math"   
        kind "StaticLib"

        includedirs {
            root .. "math/include/"
            }   
            
        files { 
            root .. "math/include/math/**.h",
            root .. "math/include/math/**.cpp",
            }
            