CMAKE_PATH := /usr/local/bin/cmake
NINJA_PATH := /usr/local/bin/ninja
COMPILER_PATH := /usr/local/bin/g++
BINARY_PATH := ./bin/demoscene
TEST_PATH := ./bin/test

main: build run
	@echo main done

debug: build
	gdb $(BINARY_PATH)

profile: build
	valgrind $(BINARY_PATH)

build: generate
	$(CMAKE_PATH) --build build --target demoscene

generate:
	$(CMAKE_PATH)\
		-S.\
		-Bbuild\
		-GNinja\
		-DCMAKE_CXX_COMPILER=$(COMPILER_PATH)\
		-DCMAKE_MAKE_PROGRAM=$(NINJA_PATH)\
		-DCMAKE_BUILD_TYPE=Debug\
		--log-level=NOTICE

run: 
	export LD_LIBRARY=/usr/lib64/
	$(BINARY_PATH)

.PHONY: test
test:
	$(CMAKE_PATH) --build build --target test
	$(TEST_PATH)

clean:
	$(CMAKE_PATH) --build build --target clean

wipe:
	rm -rf build
	rm -rf lib
	rm -rf bin
