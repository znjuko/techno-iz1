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
	cd $(output) && gcov $(dir)/tests/unit/$(test_dir)/CMakeFiles/$(test_name).dir/$(test_value).gcno && cp -rf $(dir)/tests/unit/$(test_dir)/CMakeFiles/$(test_name).dir/ .

generate-gcov-storage:
	make generate-gcov  dir=../$(BUILD_DIR)  test_dir=storage  test_name=storage_test test_value=storage output=storage_coverage

generate-lcov:
	lcov --capture --directory $(directory) --output-file $(output_filename).info

generate-lcov-storage:
	make generate-lcov output_filename=storage_coverage/storage_test directory=storage_coverage

generate-coverage-html:
	genhtml $(filename).info --output-directory $(directory)

generate-coverage-html-storage:
	make generate-coverage-html filename=storage_coverage/storage_test directory=storage_coverage

get-storage-coverage:
	mkdir storage_coverage && make generate-gcov-storage && make generate-lcov-storage && make generate-coverage-html-storage