rm -rf gcov
rm -rf target/site/clover
mkdir gcov
cd gcov/
gcov --object-directory ../bin/obj/x32/Coverage/math-scalar-test/* ../math-scalar-test
lcov --capture --base-directory ../math-scalar-test --directory .. --directory ../math-scalar-test/ --directory ../math/include/ --output-file coverage.info --no-external
genhtml coverage.info --output-directory ../target/site/clover
python  ../extern/gcov/gcov_to_clover.py *.gcov