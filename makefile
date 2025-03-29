CMAKE_BINARY := /usr/bin/cmake
NINJA_PATH := /usr/local/bin/ninja
COMPILER_PATH := /usr/local/bin/g++

main: build run
	@echo main done

debug: build
	gdb ./bin/demoscene

profile: build
	valgrind ./bin/demoscene

build: generate
	cmake --build build --target demoscene

generate:
	cmake\
		-S.\
		-Bbuild\
		-GNinja\
		-DCMAKE_CXX_COMPILER=$(COMPILER_PATH)\
		-DCMAKE_MAKE_PROGRAM=$(NINJA_PATH)\
		-DCMAKE_BUILD_TYPE=Debug\
		--log-level=NOTICE

run: 
	./bin/demoscene

.PHONY: test
test:
	cmake --build build --target test
	./bin/test

clean:
	cmake --build build --target clean

wipe:
	rm -rf build
	rm -rf lib
	rm -rf bin
