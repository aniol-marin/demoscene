CMAKE_PATH := cmake
NINJA_PATH := ninja
COMPILER_PATH := /usr/bin/g++
BINARY_PATH := ./bin/demoscene
TEST_PATH := ./bin/test
CMAKE_LOG_LEVEL := NOTICE

log = $(shell echo, $(1))
listify = $(subst ., ,$(1))

main: build run
	echo main done

debug: build
	$(call log, "debugging")
	gdb $(BINARY_PATH)

profile: build
	valgrind $(BINARY_PATH)

build: generate
	$(call log, "building")
	$(CMAKE_PATH) --build build --target demoscene

generate:
	$(CMAKE_PATH)\
		-S.\
		-Bbuild\
		-GNinja\
		-DCMAKE_CXX_COMPILER=$(COMPILER_PATH)\
		-DCMAKE_MAKE_PROGRAM=$(NINJA_PATH)\
		-DCMAKE_BUILD_TYPE=Debug\
		-DEnableTesting=ON\
		--log-level=$(CMAKE_LOG_LEVEL)

run: build 
	$(BINARY_PATH)

.PHONY: test
test: generate
	$(call log, "generating")
	$(CMAKE_PATH) --build build --target test

.PHONY: retest
retest:
	cd build/; ctest -R ^test.*\$

build-%:
	echo "building dot-separated targets: $(call listify,$(subst build-,,$@))"
	$(CMAKE_PATH) --build build --target $(call listify,$(subst build-,,$@))

test-%:
	echo "testing $(@)"
	$(CMAKE_PATH) --build build --target $(@)
	$(TEST_PATH)/$(@)

help-available-targets:
	cmake --build build/ -t help | grep phony | grep -v -e cache -e _deps -e test -e lib -e Nightly -e Experimental -e Continuous -e Catch -e SDL2 -e raudio -e uninstall | tr -d : | awk '{ print $$1; }'

clean:
	$(CMAKE_PATH) --build build --target clean

wipe:
	rm -rf build
	rm -rf lib
	rm -rf bin

$(VERBOSE).SILENT: ;
