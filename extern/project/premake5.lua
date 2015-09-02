local root      = "../../"

solution "math"

    location( root .. "math/" )
	objdir( root .. "bin/obj/" )
	debugdir( root .. "bin/" )
	
	configurations { "Debug", "Release", "Coverage"  }

	platforms { "x64_f32", "x64_f64", "x32_f32", "x32_f64" }

	vectorextensions "SSE2"

	floatingpoint "Fast"

	warnings "Extra"

	flags "Unicode"	

    configuration "x32_f32"
        targetdir( root .. "bin/x32_f32/" )
        architecture "x32"
    	defines "REAL_PRECISION_SINGLE"
        
    configuration "x32_f64"
        targetdir( root .. "bin/x32_f64/" )
        architecture "x32"
        defines "REAL_PRECISION_DOUBLE"

    configuration "x64_f32"
		targetdir( root .. "bin/x64_f32/" )
		architecture "x64"
        defines "REAL_PRECISION_SINGLE"
	
    configuration "x64_f64"
		targetdir( root .. "bin/x64_f64/" )
		architecture "x64"
        defines "REAL_PRECISION_DOUBLE"
    	
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
			root .. "test/scalar/"
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
			
		configuration { "Debug", "x32_f32" }
            defines "PREFIX=x32_f32_"
		
		configuration { "Debug", "x64_f32" }
            defines "PREFIX=x64_f32_"
		
		configuration { "Release", "x32_f32" }
		  	defines "PREFIX=x32_f32_"
              
		configuration { "Release", "x64_f32" }
		  	defines "PREFIX=x64_f32_"
              
        configuration { "Debug", "x32_f64" }
		    defines "PREFIX=x32_f64_"
        
		configuration { "Debug", "x64_f64" }
		    defines "PREFIX=x64_f64_"
        
		configuration { "Release", "x32_f64" }
		    defines "PREFIX=x32_f64_"
        
		configuration { "Release", "x64_f64" }
            defines "PREFIX=x64_f64_"
            
    project "math"
        targetname "math"   
        kind "StaticLib"

        includedirs {
            root .. "math/include/"
            }   
            
        files { 
            root .. "math/include/math/**.h",
            }
            