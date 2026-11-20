# Internal definitions
BINARY_NAME := demoscene
RUN_TARGET := run_demoscene
EDITOR_BINARY_NAME := editor
listify = $(subst ., ,$(1))
current_folder = $(shell echo $$PWD)
RUNTIME = export LD_LIBRARY_PATH=/usr/local/lib64/;
CMAKE_ROOT_PATH := $(call current_folder)
BUILD_PATH := $(call current_folder)/build/$(BUILD_TYPE)/$(C_COMPILER)
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
ifeq ($(GENERATOR_NAME),Ninja)
	BUILD_ALL_FLAG := -k 0
else ifeq ($(GENERATOR_NAME),Unix Makefiles)
	BUILD_ALL_FLAG := -k
endif

