CMAKE_PATH := cmake
NINJA_PATH := ninja
COMPILER_PATH := /usr/bin/g++
BINARY_PATH := ./bin/demoscene
TEST_PATH := ./bin/test
CMAKE_LOG_LEVEL := NOTICE

MF := 
EMF := 
log = $(info $(shell echo -e '[INFO]\033[35m $(1) \033[m'))
warn = $(info $(shell echo -e '[WARN]\033[33m $(1) \033[m'))
fail = $(info $(shell echo -e '[ERROR]\033[34m $(1) \033[m'))
listify = $(subst ., ,$(1))

main: build run
	echo main done

.PHONY: temp-test
temp-test:
	$(call warn, testing function with multiple arguments)
	$(call fail, testing function with multiple arguments)
	echo done

debug: build
	$(call log, "debugging")
	gdb $(BINARY_PATH)

profile: build
	valgrind $(BINARY_PATH)

build: generate
	$(call log, "building")
	$(CMAKE_PATH) --build build --target demoscene

generate:
	$(call log, generating)
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
	$(call log, building)
	$(BINARY_PATH)

.PHONY: test
test: generate
	$(call log, testing)
	$(CMAKE_PATH) --build build --target test

.PHONY: retest
retest:
	cd build/; ctest -R ^test.*\$

build-%:
	$(call log, "building dot-separated targets: $(call listify,$(subst build-,,$@))")
	$(CMAKE_PATH) --build build --target $(call listify,$(subst build-,,$@))

test-%:
	$(call log, "testing $(@)")
	$(CMAKE_PATH) --build build --target $(@)
	$(TEST_PATH)/$(@)

help-available-targets:
	$(call log, available targets)
	cmake --build build/ -t help | grep phony | grep -v -e '/' -e cache -e _deps -e lib -e Nightly -e Experimental -e Continuous -e Catch -e SDL2 -e raudio -e uninstall | tr -d : | awk '{ print $$1; }'

clean:
	$(call log, cleaning CMake artifacts)
	$(CMAKE_PATH) --build build --target clean

wipe:
	$(call log, wiping everything)
	rm -rf build
	rm -rf lib
	rm -rf bin

$(VERBOSE).SILENT: ;
