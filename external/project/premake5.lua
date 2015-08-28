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
        targetdir( root .. "bin/" )
        architecture "x32"
    	defines "REAL_PRECISION_SINGLE"
        
    configuration "x32_f64"
        targetdir( root .. "bin/" )
        architecture "x32"
        defines "REAL_PRECISION_DOUBLE"

    configuration "x64_f32"
		targetdir( root .. "bin/" )
		architecture "x64"
        defines "REAL_PRECISION_SINGLE"
	
    configuration "x64_f64"
		targetdir( root .. "bin/" )
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
	
    configuration { "x32_f32" }
		targetsuffix "x32_f32"
		
    configuration { "x32_f64" }
		targetsuffix "x32_f64"
		
    configuration { "x64_f32" }
		targetsuffix "x64_f32"
		
    configuration { "x64_f64" }
		targetsuffix "x64_f64"
		
    configuration { "x32_f32", "Debug" }
		targetsuffix "dx32_f32"
		
    configuration { "x32_f64", "Debug" }
		targetsuffix "dx32_f64"
		
    configuration { "x64_f32", "Debug" }
		targetsuffix "dx64_f32"
		
    configuration { "x64_f64", "Debug" }
		targetsuffix "dx64_f64"
				
	configuration {}
			
	project "math-scalar-test"
		location(  root .. "test/scalar/" )
		
		kind "ConsoleApp"
		flags "WinMain"
		defines "GTEST_HAS_TR1_TUPLE=0"
		
		includedirs {
			root .. "external/gtest/include/",
			root .. "external/gtest/",
			
			root .. "math/",
            root .. "test/",
			root .. "test/scalar"
			}	
		
		files { 
			root .. "external/gtest/src/gtest-all.cc",
			root .. "test/scalar/**.h",
			root .. "test/scalar/*.cpp"
			}
			
		configuration "gmake"
			links "pthread"
			
		configuration { "Debug", "x32_f32" }
			targetprefix "x32_f32_"
            defines "PREFIX=x32_f32_"
		
		configuration { "Debug", "x64_f32" }
			targetprefix "x64_f32_"
            defines "PREFIX=x64_f32_"
		
		configuration { "Release", "x32_f32" }
			targetprefix "x32_f32_"
		  	defines "PREFIX=x32_f32_"
              
		configuration { "Release", "x64_f32" }
			targetprefix "x64_f32_"
		  	defines "PREFIX=x64_f32_"
              
        configuration { "Debug", "x32_f64" }
			targetprefix "x32_f64_"
		    defines "PREFIX=x32_f64_"
        
		configuration { "Debug", "x64_f64" }
			targetprefix "x64_f64_"
		    defines "PREFIX=x64_f64_"
        
		configuration { "Release", "x32_f64" }
			targetprefix "x32_f64_"
		    defines "PREFIX=x32_f64_"
        
		configuration { "Release", "x64_f64" }
			targetprefix "x64_f64_"	
            defines "PREFIX=x64_f64_"
            