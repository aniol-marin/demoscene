main:
	make prepare
	make test

prepare:
	cmake \
		-S. \
		-Bbuild \
		-GNinja \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_CXX_COMPILER=/usr/local/bin/g++\
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(shell echo $$PWD)/bin\
		--log-level=WARNING
	cmake --build build -t all

test:
	cd build; ctest -T Test
	cd build; ctest -T Coverage

clear:
	clear

wipe:
	git clean -ffdx .
