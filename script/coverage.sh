set -e

cd math
make config=coverage_x86
cd ../

./math-testcd

codecov