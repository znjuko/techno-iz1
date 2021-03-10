BUILD_DIR?=build

run-test-template:
	./$(dir)/tests/unit/$(test_dir)/$(test_name)

run-storage-test:
	make run-test-template  dir=$(BUILD_DIR)  test_dir=storage  test_name=storage_test

run-all-tests:
	echo "RUNNING TESTS :" \
				&& make run-storage-test

build-project:
	mkdir build && cd build && cmake -Dtest=ON --build .. && make

generate-gcov:
	cd $(output) && gcov $(dir)/src/$(test_dir)/CMakeFiles/$(test_name).dir/$(test_value).c.gcno && cp -rf $(dir)/src/$(test_dir)/CMakeFiles/$(test_name).dir/ .

generate-gcov-storage:
	make generate-gcov  dir=../$(BUILD_DIR)  test_dir=storage  test_name=storage test_value=storage output=coverage

generate-lcov:
	lcov --capture --directory $(directory) --output-file $(output_filename).info

generate-lcov-storage:
	make generate-lcov output_filename=coverage_output/storage_test directory=coverage

generate-coverage-html:
	genhtml $(filename).info --output-directory $(directory)

generate-coverage-html-storage:
	make generate-coverage-html filename=coverage_output/storage_test directory=coverage_output

get-storage-coverage:
	mkdir coverage \
 		&& mkdir coverage_output \
	 		&& make generate-gcov-storage \
 				&& make generate-lcov-storage \
      				&& make generate-coverage-html-storage

get-all-coverage:
	make get-storage-coverage

valgrind-check:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --undef-value-errors=no --verbose --log-file=$(filename)  $(directory)

valgrind-check-storage-test:
	make valgrind-check directory=./build/tests/unit/storage/storage_test filename=valgrind_output/storage_report

valgrind-check-all:
	mkdir valgrind_output && make valgrind-check-storage-test


