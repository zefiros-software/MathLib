

project "MathLib"

    kind "StaticLib"       

    files {
        "math/src/**.cpp"
    } 

    zpm.export [[
        includedirs "math/include/"
        flags "C++11"
    ]]