BUILD_DIR?=build

run-test-template:
	./$(dir)/tests/unit/$(test_dir)/$(test_name)

run-adder-test:
	make run-test-template  dir=$(BUILD_DIR)  test_dir=adder  test_name=adder_test

run-storage-test:
	make run-test-template  dir=$(BUILD_DIR)  test_dir=storage  test_name=storage_test

run-all-tests:
	echo "RUNNING TESTS :" \
		&& make run-adder-test \
				&& make run-storage-test

build-project:
	mkdir build && cd build && cmake -Dtest=ON --build .. && make