local root      = "../../"
local getldflags = premake.tools.gcc.getldflags;
function premake.tools.gcc.getldflags(cfg)
    local ldflags = { pthread = "-pthread" }
    local r = getldflags(cfg);
    local r2 = table.translate(cfg.flags, ldflags);
    for _,v in ipairs(r2) do table.insert(r, v) end
    return r;
end
table.insert(premake.fields.flags.allowed, "pthread");

solution "zefirosMath"

	location( root )
	objdir( root .. "bin/obj/" )
	debugdir( root .. "bin/" )
	
	configurations { "Debug", "Release" }

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
				
	configuration {}
	
	project "math"
		
		kind "StaticLib"
		
		location(  root .. "math/" )
		
		includedirs {
			root .. "math"
			}	
		
		files { 
			root .. "math/**.h",
			root .. "math/*.cpp"
			}
	
	project "math-test"
	
		location(  root .. "test/" )
		
		kind "ConsoleApp"
		flags "WinMain"
		defines "GTEST_HAS_TR1_TUPLE=0"
		
		includedirs {
			root .. "external/gtest/include/",
			root .. "external/gtest/",
			root .. "math/",
            root .. "test/"
			}	
		
		files { 
			root .. "external/gtest/src/gtest-all.cc",
			root .. "test/**.h",
			root .. "test/**.cpp"
			}
			
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
            