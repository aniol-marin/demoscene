listify = $(subst ., ,$(1))
current_folder = $(shell echo $$PWD)
log =  $(info $(shell echo -e '[INFO] \033[35m $(1) \033[m'))
warn = $(info $(shell echo -e '[WARN] \033[33m $(1) \033[m'))
fail = $(info $(shell echo -e '[ERROR]\033[34m $(1) \033[m'))

BINARY_NAME := demoscene
BUILD_TYPE := Debug
CMAKE_LOG_LEVEL := NOTICE

CMAKE_PATH := cmake
GENERATOR := Ninja
GENERATOR_PATH := ninja
COMPILER_PATH := g++
CMAKE_ROOT_PATH := .
BUILD_PATH := $(call current_folder)/build/$(BUILD_TYPE)
BINARY_PATH := $(call current_folder)/bin/$(BUILD_TYPE)
LIBRARY_PATH := $(call current_folder)/lib/$(BUILD_TYPE)
DEPENDENCIES_PATH := $(CMAKE_ROOT_PATH)/external
TEST_PATH := $(BINARY_PATH)/test

main: build run ;

debug: build
	$(call log, "debugging")
	gdb $(BINARY_PATH)/$(BINARY_NAME)

profile: build
	$(call log, "profiling")
	valgrind $(BINARY_PATH)/$(BINARY_NAME)

build: generate
	$(call log, "building")
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(BINARY_NAME)

generate:
	$(call log, "generating config $(BUILD_TYPE) in $(BUILD_PATH)")
	$(CMAKE_PATH)\
		-S$(CMAKE_ROOT_PATH)\
		-B$(BUILD_PATH)\
		-G$(GENERATOR)\
		-DFETCHCONTENT_BASE_DIR:PATH=$(DEPENDENCIES_PATH)\
		-DCMAKE_CXX_COMPILER=$(COMPILER_PATH)\
		-DCMAKE_MAKE_PROGRAM=$(GENERATOR_PATH)\
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE)\
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$(BINARY_PATH)" \
		-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY="$(LIBRARY_PATH)" \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY="$(LIBRARY_PATH)" \
		--log-level=$(CMAKE_LOG_LEVEL)
	rm -f ./$(BUILD_PATH)/compile_commands.json compile_commands.json
	ln -s ./$(BUILD_PATH)/compile_commands.json compile_commands.json

configure: $(BUILD_PATH)/CMakeCache.txt
	$(call log, "configuring generated project in $(BUILD_PATH)/CMakeCache.txt")
	ccmake $(BUILD_PATH)

run: build 
	$(call log, "running final project")
	$(BINARY_PATH)/$(BINARY_NAME)

.PHONY: test
test: generate
	$(call log, "testing all CTest targets")
	$(CMAKE_PATH) --build $(BUILD_PATH) --target test

.PHONY: retest
retest-%:
	$(call log, "retesting all matches for pattern [$(call listify,$(subst retest-,,$@))]")
	cd $(BUILD_PATH); ctest -R ^.*$(call listify,$(subst retest-,,$@)).*\$

build-%:
	$(call log, "building dot-separated targets: $(call listify,$(subst build-,,$@))")
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(call listify,$(subst build-,,$@)) $(REDIRECT)

test-%:
	$(call log, "testing $(@)")
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(@)
	$(TEST_PATH)/$(@)

help-available-targets:
	cmake --build $(BUILD_PATH)/ -t help | grep phony | grep -v -e cache -e _deps -e install -e "/" -e lib -e Nightly -e Experimental -e Continuous -e Catch -e SDL2 -e raudio -e uninstall | tr -d : | awk '{ print $$1; }'

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

$(BUILD_PATH)/CMakeCache.txt: generate;

/tmp/output:
	echo "" >> /tmp/output
	echo "Project compilation status:" > /tmp/output
	make help-available-targets | xargs -I {} sh -c ' make build-{} $> /dev/null && echo "\033[35m{}\033[m :\033[32m ok\033[m" >> /tmp/output || echo "{}: \033[33mko\033[m" >> /tmp/output'

clean:
	$(call log, "cleaning build artifacts in $(BUILD_PATH)")
	$(CMAKE_PATH) --build $(BUILD_PATH) --target clean

wipe:
	$(call log, "wiping build info in $(BUILD_PATH)")
	rm -rf $(BUILD_PATH)

full-wipe:
	git clean -ffdx

$(VERBOSE).SILENT: ;
ifdef (FULLY_SILENT)
	REDIRECT := &> /dev/null
else
	REDIRECT := 
endif

