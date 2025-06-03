CMAKE_PATH := cmake
NINJA_PATH := ninja
COMPILER_PATH := g++
BINARY_PATH := ./bin/demoscene
DEPENDENCIES_PATH := /lib/_deps
TEST_PATH := ./bin/test
CMAKE_LOG_LEVEL := NOTICE

listify = $(subst ., ,$(1))
current_folder = $(shell echo $$PWD)
log = $(info  $(shell echo -e '[INFO] \033[35m $(1) \033[m'))
warn = $(info $(shell echo -e '[WARN] \033[33m $(1) \033[m'))
fail = $(info $(shell echo -e '[ERROR]\033[34m $(1) \033[m'))

main: build run
	echo main done

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
		-DFETCHCONTENT_BASE_DIR:PATH=$(call current_folder)$(DEPENDENCIES_PATH)\
		-DCMAKE_CXX_COMPILER=$(COMPILER_PATH)\
		-DCMAKE_MAKE_PROGRAM=$(NINJA_PATH)\
		-DCMAKE_BUILD_TYPE=Debug\
		--log-level=$(CMAKE_LOG_LEVEL)

configure: generate
	cd build; ccmake .

run: build 
	$(BINARY_PATH)

.PHONY: test
test: generate
	$(CMAKE_PATH) --build build --target test

.PHONY: retest
retest:
	cd build/; ctest -R ^test.*\$

build-%:
	echo "building dot-separated targets: $(call listify,$(subst build-,,$@))"
	$(CMAKE_PATH) --build build --target $(call listify,$(subst build-,,$@)) $(REDIRECT)

test-%:
	echo "testing $(@)"
	$(CMAKE_PATH) --build build --target $(@)
	$(TEST_PATH)/$(@)

help-available-targets:
	cmake --build build/ -t help | grep phony | grep -v -e cache -e _deps -e install -e "/" -e lib -e Nightly -e Experimental -e Continuous -e Catch -e SDL2 -e raudio -e uninstall | tr -d : | awk '{ print $$1; }'

status: regenerate-status
	clear
	make previous-status

regenerate-status: generate /tmp/output
	make clear-status
	make /tmp/output

previous-status: /tmp/output
	cat /tmp/output

clear-status:
	rm /tmp/output

/tmp/output:
	echo "" >> /tmp/output
	echo "Project compilation status:" > /tmp/output
	make help-available-targets | xargs -L 1 -I {} sh -c ' make build-{} $> /dev/null && echo "\033[35m{}\033[m :\033[32m ok\033[m" >> /tmp/output || echo "{}: \033[33mko\033[m" >> /tmp/output'

clean:
	$(CMAKE_PATH) --build build --target clean

wipe:
	echo wiping build artifacts
	rm -rf build

full-wipe:
	make wipe
	rm -rf lib
	rm -rf bin

$(VERBOSE).SILENT: ;
ifdef (FULLY_SILENT)
	REDIRECT := &> /dev/null
else
	REDIRECT := 
endif

