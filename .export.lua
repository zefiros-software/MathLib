

project "MathLib"

    kind "StaticLib"       

    files {
        "math/src/**.cpp"
    } 

    zpm.export [[
        includedirs "math/include/"
        cppdialect "C++11"
    ]]