premake5 install-package --allow-install --allow-module  || exit /b 1
premake5 vs2015 || exit /b 1
msbuild math/MathLib.sln /property:Configuration=Release /property:Platform=Win32 || exit /b 1
::msbuild math/MathLib.sln /property:Configuration=Debug /property:Platform=Win32 || exit /b 1
msbuild math/MathLib.sln /property:Configuration=Release /property:Platform=x64 || exit /b 1
::msbuild math/MathLib.sln /property:Configuration=Debug /property:Platform=x64 || exit /b 1

cd test/
premake5 vs2015 || exit /b 1
msbuild zpm/MathLib-ZPM.sln || exit /b 1

cd ../

bin\x86\math-test.exe || exit /b 1
::bin\x86\math-testd.exe || exit /b 1

bin\x86_64\math-test.exe || exit /b 1
::bin\x86_64\math-testd.exe || exit /b 1

test\bin\x86\math-zpm-test.exe || exit /b 1