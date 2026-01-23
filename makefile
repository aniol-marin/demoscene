# -----------------------------------------------------------------
# ---------------------------- NOTE -------------------------------
# -----------------------------------------------------------------
# --  This is an internal development file.                      --
# --                                                             --
# --  It is checked in source control out of convenience.        --
# --  However, it is not meant to be used by the end user.       --
# --  Feel free to experiment with it, but please use your own   --
# --  preferred CMake workflow in order to build the project.    --
# -----------------------------------------------------------------
# -----------------------------------------------------------------

# Configurable fields
BUILD_TYPE := Debug
CMAKE_PATH := cmake
GENERATOR_NAME := Ninja
GENERATOR_PATH := ninja
CMAKE_LOG_LEVEL := NOTICE
CMAKE_PRESET := default
CXX_COMPILER_PATH := g++
C_COMPILER_PATH := gcc
MEMCHECK_BIN := valgrind
COVERAGE_BIN := gcov
USER = $(shell uname -n)

# Internal definitions
BINARY_NAME := demoscene
EDITOR_BINARY_NAME := editor
listify = $(subst ., ,$(1))
current_folder = $(shell echo $$PWD)
RUNTIME = export LD_LIBRARY_PATH=/usr/local/lib64/:LD_LIBRARY_PATH;
CMAKE_ROOT_PATH := $(call current_folder)
BUILD_PATH := $(call current_folder)/build/$(BUILD_TYPE)
RUNTIME_PATH := $(call current_folder)/bin
LIBRARY_PATH := $(call current_folder)/lib
EXTERNALS_PATH := $(call current_folder)/external
EXPORT_PATH := $(call current_folder)/export
TEMP_PATH := /tmp
CACHE_FILE := $(BUILD_PATH)/CMakeCache.txt
STATUS_PATH := /tmp/$(BUILD_PATH)
STATUS_FILE := $(STATUS_PATH)/status_output
TESTS_RUNTIME_PATH := $(RUNTIME_PATH)/test
MEMCHECK_PATH = $(shell which $(MEMCHECK_BIN))
COVERAGE_PATH = $(shell which $(COVERAGE_BIN))

###############################################################################
################################### Public recipes ###########################################################
###############################################################################

# Default action: run demo for "final users"
# [NOTE] in an uninitialized CMake project, uses the Builder preset
main:
	make .call_log MESSAGE="building and running final demo" --no-print-directory
	$(CMAKE_PATH) \
		-S$(CMAKE_ROOT_PATH) \
		-Bbuild-artifacts \
		-G$(GENERATOR_NAME) \
		-DCMAKE_MAKE_PROGRAM=$(GENERATOR_PATH)\
		-DCMAKE_CXX_COMPILER=$(CXX_COMPILER_PATH) \
		-DCMAKE_C_COMPILER=$(C_COMPILER_PATH) \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=$(call current_folder) \
		--preset=user \
		--log-level=ERROR
	cmake --build build-artifacts -t $(BINARY_NAME)
	./$(BINARY_NAME)

# Clears screen (convenience wrapper for recipe queues)
clear:
	clear;

# Runs the final demo
# [NOTE] in an uninitialized CMake project, uses the Builder preset
run: .final
	make .call_log MESSAGE="running final project"
	$(RUNTIME) $(RUNTIME_PATH)/$(BINARY_NAME)

# Runs all the executables at once
run-all:
	make .call_log MESSAGE="attemptting to build all targets"
	-make .build-all
	make .call_log MESSAGE="running all targets"
	find $(RUNTIME_PATH) -type f -executable -print -exec {} \;

# Builds the main project target
.PHONY: build
build: build.-$(BINARY_NAME)
	make .call_log MESSAGE="main build done"

# Launches the editor
# [NOTE] it will try to build it if not available, regardless of configuration
# [NOTE] in an uninitialized CMake project, uses the Developer preset
edit: .editor
	make .call_log MESSAGE="launching editor"
	$(RUNTIME) $(RUNTIME_PATH)/$(EDITOR_BINARY_NAME)

# Attempts to launch gdb
# [NOTE] in an uninitialized CMake project, uses the Developer preset
debug: .final
	if ! command -v gdb > /dev/null 2>&1; then \
		make .call_fail MESSAGE="couldnt find gdb at path, recipe cannot be completed"; \
	else \
		make .call_log MESSAGE="debugging"; \
		gdb $(RUNTIME_PATH)/$(BINARY_NAME); \
	fi

# Attaches gdb to the already running binary
attach:
	gdb attach $$(pgrep $(BINARY_NAME))

# Attempts to launch the binary target with the defined profiler
profile: .final
	if ! command -v $(MEMCHECK_PATH) > /dev/null 2>&1; then \
		make .call_fail MESSAGE="couldnt find $(MEMCHECK_PATH) at path, recipe cannot be completed"; \
	else \
		make .call_log MESSAGE="profiling"; \
		$(MEMCHECK_PATH) --track-origins=yes $(RUNTIME_PATH)/$(BINARY_NAME); \
	fi

# Launches cpack export pipeline
.PHONY: pack
pack:
	cd $(BUILD_PATH); cpack -DCPACK_PACKAGE_DIRECTORY=$(EXPORT_PATH)

# Launches custom CTest pipeline targeting Experimental dashboard
# [NOTE] in an uninitialized CMake project, uses the Builder preset
report-experimental:
	make .call_log MESSAGE="reporting to Experimental CDash board"
	make .report BUILD_PATH=$(call current_folder)/build-experimental DASHBOARD=Experimental

# Launches custom CTest pipeline targeting Continuous dashboard
# [NOTE] in an uninitialized CMake project, uses the Builder preset
report-continuous:
	make .call_log MESSAGE="reporting to Continuous CDash board"
	make .report BUILD_PATH=$(call current_folder)/build-continuous DASHBOARD=Continuous

# Launches custom CTest pipeline targeting Experimental dashboard and templated group
# [NOTE] in an uninitialized CMake project, uses the Builder preset
.PHONY: report-experimental-cpp
report-experimental-cpp%:
	make .call_log MESSAGE="reporting to Experimental CDash board, target group: cpp$*"
	make .report \
		BUILD_PATH=$(call current_folder)/build-experimental \
		DASHBOARD=Experimental \
		CTEST_GROUP=--group=cpp$*

# Launches all tracked test targets through CTest
# [NOTE] in an uninitialized CMake project, uses the Maintainer preset
check-test: generate
	make .call_log MESSAGE="testing CTest tests"
	cd $(BUILD_PATH); ctest -T Test

# Launches coverage analysis through CTest
check-coverage:
	-make check-test
	make .call_log MESSAGE="testing CTest coverage"
	cd $(BUILD_PATH); ctest -T Coverage

# Prints information of the current toolchain
check-toolchain:
	echo "------------------------------------------"
	echo "c++ compiler:"
	$(CXX_COMPILER_PATH) --version
	echo "------------------------------------------"
	echo "cmake:"
	$(CMAKE_PATH) --version
	echo "------------------------------------------"
	echo "generator:"
	$(GENERATOR_PATH) --version
	echo "------------------------------------------"


# Launches cross-compilation pipeline
cross-compile:
	cmake --toolchain=./ctest/cross_compiled_windows_from_linux.cmake

# Initializes a fresh Trisquel 11 environment with project dependencies
# - glad generation (curl, python)
# - glfw generation (alsa sound 2, wayland scanner, pkg-config, xkb, opengl)
# - sdl generation (ext, only when opengl is added?)
initialize-trisquel-11:
	sudo apt install \
		git-lfs \
		curl python3 \
		libasound2-dev libwayland-dev pkg-config libxkbcommon-dev mesa-common-dev \
		libxext-dev
	git lfs install;
	git lfs fetch --all origin;
	git lfs update;
	git lfs checkout resources;
	curl -L https://bootstrap.pypa.io/get-pip.py -o $(TEMP_PATH)/get-pip.py -z $(TEMP_PATH)/get-pip.py
	python3 $(TEMP_PATH)/get-pip.py
	python3 -m pip install Jinja2

# Regenerates the CMake project
# [NOTE] in an uninitialized CMake project, uses the Developer preset
generate:
	make .call_log MESSAGE="generating config $(BUILD_TYPE) in $(BUILD_PATH)"
	if ! [ -f $(CACHE_FILE) ]; then \
		make $(CACHE_FILE) CMAKE_PRESET=developer; \
	fi
	$(CMAKE_PATH) \
		-S$(CMAKE_ROOT_PATH) \
		-B$(BUILD_PATH) \
		--log-level=$(CMAKE_LOG_LEVEL)
	ln -sf ./$(BUILD_PATH)/compile_commands.json compile_commands.json

# Reconfigures the CMake project
# [NOTE] in an uninitialized CMake project, uses the Maintainer preset
# which allows to fine tune before generation
configure:
	if ! [ -f $(CACHE_FILE) ]; then \
		make $(CACHE_FILE) CMAKE_PRESET=maintainer; \
	fi
	make .call_log MESSAGE="configuring project";
	ccmake $(BUILD_PATH);

# Launches all tracked test targets through CMake
# [NOTE] in an uninitialized CMake project, uses the Developer preset
.PHONY: test
test: generate
	make .call_log MESSAGE="testing all CMake test targets"
	$(CMAKE_PATH) --build $(BUILD_PATH) --target test

# Prints a list of all the project-specific CMake targets
.PHONY:help-available-targets
help-available-targets:
	make --no-print-dir .help

# Attempts to build each CMake project-specific target,
# then generates and caches an on-screen report
# [NOTE] in an uninitialized CMake project, uses the Developer preset
status:
	make .regenerate-status
	clear
	make previous-status

# Shows the last cached report, generates a new one otherwise
# [NOTE] in an uninitialized CMake project, uses the Developer preset
previous-status: $(STATUS_FILE)
	cat $(STATUS_FILE)

# Applies clang-format to all .h and cpp source files
# [NOTE] aplied to src/ only, excludes test/ and vendored code
format:
	find src/ -type f | grep -e '.cpp' -e '.h' | xargs -L1 clang-format -i

# Cleans all CMake build artifacts for the current build tree.
clean:
	make .call_warn MESSAGE="are you sure you want to clear all CMake artifacts? [yes]"
	echo -n ">> " && \
	read safe; \
	if [ "$${safe}" = yes ]; then \
		make .clean; \
	else \
		make .call_fail MESSAGE="safe word not provided, aborting"; \
	fi

# Removes the current CMake build tree.
wipe:
	make .call_warn MESSAGE="are you sure you want to wipe all artifacts from $(BUILD_PATH)? [yes]"
	echo -n ">> " && \
	read safe; \
	if [ "$${safe}" = yes ]; then \
		make .call_warn MESSAGE="wiping build info in $(BUILD_PATH)"; \
		rm -rf $(BUILD_PATH); \
		find $(EXTERNALS_PATH) -wholename '$(EXTERNALS_PATH)/*-build' -exec rm -rf {} +; \
	else \
		make .call_fail MESSAGE="safe word not provided, aborting"; \
	fi

# Removes all the untracked files from the git workspace.
full-wipe:
	make .call_warn MESSAGE="are you sure you want to clear ALL untracked files? [yes]"
	echo -n ">> " && \
	read safe; \
	if [ "$${safe}" = yes ]; then \
		make .call_warn MESSAGE="wiping ALL untracked info in $(call current_folder)"; \
		git clean -ffdx; \
	else \
		make .call_fail MESSAGE="safe word not provided, aborting"; \
	fi

###############################################################################
################# Private recipes and implementation details ##################
###############################################################################
# NOTE implementation-detail recipes in this internal file
# are undocumented by choice

.report:
	if ! [ -f $(CACHE_FILE) ]; then \
		make $(CACHE_FILE) CMAKE_PRESET=builder; \
	fi
	make .clean
	ctest \
		-DCTEST_SOURCE_DIRECTORY=$(call current_folder) \
		-DCTEST_BINARY_DIRECTORY=$(BUILD_PATH) \
		-DCTEST_CMAKE_GENERATOR=$(GENERATOR_NAME) \
		-DCTEST_MEMORYCHECK_COMMAND=$(MEMCHECK_PATH) \
		-DCTEST_COVERAGE_COMMAND=$(COVERAGE_PATH) \
		-DDASHBOARD=$(DASHBOARD) \
		-DUSER=$(USER) \
		$(CTEST_GROUP) \
		-S ctest/full-report.cmake

.run-%: $(CACHE_FILE)
	make .call_log MESSAGE="running target: $(subst run-,,$@)"
	$(RUNTIME_PATH)/$(subst run-,,$@) $(REDIRECT)

.profile-%: $(CACHE_FILE)
	make .call_log MESSAGE="profiling target: $(subst profile-,,$@)"
	$(MEMCHECK_PATH) --track-origins=yes --leak-check=full $(RUNTIME_PATH)/$(subst profile-,,$@) $(REDIRECT)

.retest-%:
	make .call_log MESSAGE="retesting all matches for pattern [$(call listify,$(subst retest-,,$@))]"
	cd $(BUILD_PATH); ctest -R ^.*$(call listify,$(subst retest-,,$@)).*$$

.PHONY: .build-
.build-%: $(CACHE_FILE)
	make .call_log MESSAGE="building dot-separated targets: $(call listify,$(subst build-,,$@))"
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(call listify,$(subst .build-,,$@)) $(REDIRECT)

.PHONY: test-
test-%:
	make .call_log MESSAGE="testing $(@)"
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(@)
	$(TESTS_RUNTIME_PATH)/$(@)

.clean:
	make .call_log MESSAGE="cleaning build artifacts in $(BUILD_PATH)";
	$(CMAKE_PATH) --build $(BUILD_PATH) --target clean;

.final: $(RUNTIME_PATH)/$(BINARY_NAME) ;

$(RUNTIME_PATH)/$(BINARY_NAME):
	make .build_final

.build_final: generate .build-$(BINARY_NAME) ;

.editor: $(RUNTIME_PATH)/$(EDITOR_BINARY_NAME) ;
$(RUNTIME_PATH)/$(EDITOR_BINARY_NAME):
	make .build_editor
.build_editor: generate .build-$(EDITOR_BINARY_NAME) ;

.help:
	cmake --build $(BUILD_PATH) -t help | grep phony \
		| grep -v \
		-e all -e cache -e codegen -e  _deps -e install -e "/" \
		-e lib -e Nightly -e Experimental -e Continuous -e uninstall \
		-e Catch \
		-e SDL2 -e sdl_headers_copy \
		-e pugixml[^_]  \
		-e raudio[^_]  \
		-e glad[^_]  \
		-e imgui[^_]  \
		-e ^glfw[^_] -e update_mappings \
		-e test[^\-] \
		| tr -d : | awk '{ print $$1; }'

$(CACHE_FILE):
	make .call_log MESSAGE="starting custom configuration of the project in $(BUILD_PATH)/CMakeCache.txt"
	mkdir -p $(BUILD_PATH)
	cmake \
		-S$(CMAKE_ROOT_PATH) \
		-B$(BUILD_PATH) \
		-G$(GENERATOR_NAME) \
		-DCMAKE_MAKE_PROGRAM=$(GENERATOR_PATH)\
		-DCMAKE_CXX_COMPILER=$(CXX_COMPILER_PATH) \
		-DCMAKE_C_COMPILER=$(C_COMPILER_PATH) \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=$(RUNTIME_PATH) \
		-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=$(LIBRARY_PATH) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY:PATH=$(RUNTIME_PATH) \
		--preset=$(CMAKE_PRESET) \
		--log-level=$(CMAKE_LOG_LEVEL)

.regenerate-status:
	make generate
	make .clear-status
	make $(STATUS_FILE)

.clear-status:
	rm -rf $(STATUS_PATH);

.clear-config:
	rm $(CACHE_FILE)

$(STATUS_FILE):
	mkdir -p $(STATUS_PATH)
	echo "" >> $(STATUS_FILE)_temp
	echo "Project compilation status:" >> $(STATUS_FILE)_temp
	make help-available-targets | xargs -I '{}' sh -c 'make .build-{} && echo "\033[35m{}\033[m :\033[32m ok\033[m" >> $(STATUS_FILE)_temp || echo "{}: \033[33mko\033[m" >> $(STATUS_FILE)_temp'
	mv $(STATUS_FILE)_temp $(STATUS_FILE)

$(VERBOSE).SILENT: ;

ifdef (FULLY_SILENT)
	REDIRECT := &> /dev/null
else
	REDIRECT :=
endif

MESSAGE := no message
.PHONY: .call_log
.call_log:
	$(call log, $(MESSAGE))

.PHONY: .call_warn
.call_warn:
	$(call warn, $(MESSAGE))

.PHONY: .call_fail
.call_fail:
	$(call fail, $(MESSAGE))

log =  $(info  $(shell echo -e '[INFO] \033[35m $(1) \033[m'))
warn = $(info  $(shell echo -e '[WARN] \033[33m $(1) \033[m'))
fail = $(error $(shell echo -e '[ERROR]\033[31m $(1) \033[m'))

%:
	make .call_fail MESSAGE="Inexisting recipe: [ $@ ]"

