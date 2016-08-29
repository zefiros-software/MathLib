set -e

premake5 install-package --allow-install --allow-module
premake5 gmake
cd math
make config=debug_x86
make config=debug_x86_64
make config=release_x86
make config=release_x86_64
#make config=coverage_x86
#make config=coverage_x86_64

cd ../test/

premake5 gmake

cd zpm/
make
cd ../../

bin/x86/math-test
bin/x86/math-testd
#bin/x86/math-testcd

bin/x86_64/math-test
bin/x86_64/math-testd
#bin/x86_64/math-testcd

test/bin/x86/math-zpm-test