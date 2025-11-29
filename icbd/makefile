main:
	cmake \
		-S. \
		-Bbuild \
		-GNinja \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_CXX_COMPILER=/usr/local/bin/g++\
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(shell echo $$PWD)/bin\
		--log-level=WARNING
	cmake --build build -t all
	-$(shell echo $$PWD)/bin/target
	gcov $(shell echo $$PWD)/build/CMakeFiles/target.dir/coverage.cpp.o

manual:
	g++ -O0 -coverage coverage.cpp -o coverage; ./coverage; gcov coverage

wipe:
	git clean -ffdx .
