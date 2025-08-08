# Configurable fields
BINARY_NAME := demoscene
EDITOR_BINARY_NAME := editor
BUILD_TYPE := Debug
CMAKE_PATH := cmake
CMAKE_LOG_LEVEL := NOTICE
GENERATOR := Ninja
COMPILER_PATH := g++

# Internal definitions
listify = $(subst ., ,$(1))
current_folder = $(shell echo $$PWD)
RUNTIME = export LD_LIBRARY_PATH=/usr/local/lib64/:LD_LIBRARY_PATH;
CMAKE_ROOT_PATH := .
BUILD_PATH := $(call current_folder)/build/$(BUILD_TYPE)
BINARY_PATH := $(call current_folder)/bin
LIBRARY_PATH := $(call current_folder)/lib
TEMP_PATH := /tmp
DEPENDENCIES_PATH := $(call current_folder)/external
CACHE := $(BUILD_PATH)/CMakeCache.txt
STATUS_FOLDER := /tmp/$(BUILD_PATH)
STATUS_OUTPUT := $(STATUS_FOLDER)/status_output
TEST_PATH := $(BINARY_PATH)/test

# Default action: run demo for final users
main:
	make .call_log MESSAGE="building and running final demo" --no-print-directory
	make \
		BUILD_TYPE=Release \
		CMAKE_LOG_LEVEL=WARNING \
		--no-print-directory \
		generate build run

# Public recipes

run: .final
	make .call_log MESSAGE="running final project"
	$(RUNTIME) $(BINARY_PATH)/$(BINARY_NAME)

.PHONY: build
build: build-$(BINARY_NAME)
	make .call_log MESSAGE="main build done"

edit: .editor
	make .call_log MESSAGE="launching editor"
	$(RUNTIME) $(BINARY_PATH)/$(EDITOR_BINARY_NAME)

debug: #build-$(BINARY_NAME)
	if ! command -v gdb > /dev/null 2>&1; then \
		make .call_fail MESSAGE="couldnt find gdb at path, recipe cannot be completed"; \
	else \
		make .call_log MESSAGE="debugging"; \
		gdb $(BINARY_PATH)/$(BINARY_NAME); \
	fi

attach:
	gdb attach $$(pgrep $(EDITOR_BINARY_NAME))

profile: .final
	if ! command -v valgrind > /dev/null 2>&1; then \
		make .call_fail MESSAGE="couldnt find valgrind at path, recipe cannot be completed"; \
	else \
		make .call_log MESSAGE="profiling"; \
		valgrind --track-origins=yes $(BINARY_PATH)/$(BINARY_NAME); \
	fi

#needed for:
# - glad generation (curl, python)
# - glfw generation (alsa sound 2, wayland scanner, pkg-config, xkb, opengl)
# - sdl  generation (ext, only when opengl is added?)
initialize:
	sudo apt install \
		curl python3 \
		libasound2-dev libwayland-dev pkg-config libxkbcommon-dev mesa-common-dev \
		libxext-dev
	curl -L https://bootstrap.pypa.io/get-pip.py -o $(TEMP_PATH)/get-pip.py -z $(TEMP_PATH)/get-pip.py
	python3 $(TEMP_PATH)/get-pip.py
	python3 -m pip install Jinja2

generate:
	make .call_log MESSAGE="generating config $(BUILD_TYPE) in $(BUILD_PATH)"
	$(CMAKE_PATH) \
		   -S$(CMAKE_ROOT_PATH) \
		   -B$(BUILD_PATH) \
		   -G$(GENERATOR) \
		   -DConfig_PathFor_Binaries:PATH=$(BINARY_PATH) \
		   -DConfig_PathFor_Libraries:PATH=$(LIBRARY_PATH) \
		   -DConfig_PathFor_Dependencies:PATH=$(DEPENDENCIES_PATH) \
		   -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		   -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		   --log-level=$(CMAKE_LOG_LEVEL)
	rm -f compile_commands.json
	ln -s ./$(BUILD_PATH)/compile_commands.json compile_commands.json

configure: $(CACHE)
	make .call_log MESSAGE="configuring project"
	ccmake $(BUILD_PATH)

.PHONY: test
test: generate
	make .call_log MESSAGE="testing all CTest targets"
	$(CMAKE_PATH) --build $(BUILD_PATH) --target test

.PHONY: run-
run-%: $(CACHE)
	make .call_log MESSAGE="running target: $(subst run-,,$@)"
	$(BINARY_PATH)/$(subst run-,,$@) $(REDIRECT)

.PHONY: profile-
profile-%: $(CACHE)
	make .call_log MESSAGE="profiling target: $(subst profile-,,$@)"
	valgrind --track-origins=yes --leak-check=full $(BINARY_PATH)/$(subst profile-,,$@) $(REDIRECT)

.PHONY: retest-
retest-%:
	make .call_log MESSAGE="retesting all matches for pattern [$(call listify,$(subst retest-,,$@))]"
	cd $(BUILD_PATH); ctest -R ^.*$(call listify,$(subst retest-,,$@)).*$$

.PHONY: build-
build-%: $(CACHE)
	make .call_log MESSAGE="building dot-separated targets: $(call listify,$(subst build-,,$@))"
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(call listify,$(subst build-,,$@)) $(REDIRECT)

.PHONY: test-
test-%:
	make .call_log MESSAGE="testing $(@)"
	$(CMAKE_PATH) --build $(BUILD_PATH) --target $(@)
	$(TEST_PATH)/$(@)

.PHONY:help-available-targets
help-available-targets:
	make --no-print-dir .help

status:
	make .regenerate-status
	clear
	make previous-status

previous-status: $(STATUS_OUTPUT)
	cat $(STATUS_OUTPUT)

clean:
	make .call_warn MESSAGE="are you sure you want to clear all CMake artifacts? [yes]"
	echo -n ">> " && \
	read safe; \
	if [ "$${safe}" = yes ]; then \
		make .call_log MESSAGE="cleaning build artifacts in $(BUILD_PATH)"; \
		$(CMAKE_PATH) --build $(BUILD_PATH) --target clean; \
	else \
		make .call_fail MESSAGE="safe word not provided, aborting"; \
	fi

wipe:
	make .call_warn MESSAGE="are you sure you want to wipe all artifacts from $(BUILD_PATH)? [yes]"
	echo -n ">> " && \
	read safe; \
	if [ "$${safe}" = yes ]; then \
		make .call_warn MESSAGE="wiping build info in $(BUILD_PATH)"; \
		rm -rf $(BUILD_PATH); \
	else \
		make .call_fail MESSAGE="safe word not provided, aborting"; \
	fi

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

# Internal recipes (not meant to be called from the user)

.final: $(BINARY_PATH)/$(BINARY_NAME) ;
$(BINARY_PATH)/$(BINARY_NAME):
	make .build_final
.build_final: generate build-$(BINARY_NAME) ;

.editor: $(BINARY_PATH)/$(EDITOR_BINARY_NAME) ;
$(BINARY_PATH)/$(EDITOR_BINARY_NAME):
	make .build_editor
.build_editor: generate build-$(EDITOR_BINARY_NAME) ;

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
		-e glfw[^_] -e update_mappings \
		| tr -d : | awk '{ print $$1; }'

$(CACHE):
	make .call_log MESSAGE="configuring generated project in $(BUILD_PATH)/CMakeCache.txt"
	mkdir -p $(BUILD_PATH)
	ccmake $(CMAKE_ROOT_PATH) \
		   -S$(CMAKE_ROOT_PATH) \
		   -B$(BUILD_PATH) \
		   -G$(GENERATOR) \
		   -DConfig_PathFor_Binaries:PATH=$(BINARY_PATH) \
		   -DConfig_PathFor_Libraries:PATH=$(LIBRARY_PATH) \
		   -DConfig_PathFor_Dependencies:PATH=$(DEPENDENCIES_PATH) \
		   -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		   -DEnableExperimentalFeatures:BOOL=ON \
		   -DDisableAllButExperimental:BOOL=ON
	#-DConfig_Compiler:PATH=$(COMPILER_PATH) \

.regenerate-status:
	make generate
	make .clear-status
	make $(STATUS_OUTPUT)

.clear-status:
	rm -rf $(STATUS_FOLDER);

.clear-config:
	rm $(CACHE)

$(STATUS_OUTPUT):
	mkdir -p $(STATUS_FOLDER)
	echo "" >> $(STATUS_OUTPUT)_temp
	echo "Project compilation status:" >> $(STATUS_OUTPUT)_temp
	make help-available-targets | xargs -I '{}' sh -c 'make build-{} && echo "\033[35m{}\033[m :\033[32m ok\033[m" >> $(STATUS_OUTPUT)_temp || echo "{}: \033[33mko\033[m" >> $(STATUS_OUTPUT)_temp'
	mv $(STATUS_OUTPUT)_temp $(STATUS_OUTPUT)

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

log =  $(info $(shell echo -e '[INFO] \033[35m $(1) \033[m'))
warn = $(info $(shell echo -e '[WARN] \033[33m $(1) \033[m'))
fail = $(info $(shell echo -e '[ERROR]\033[31m $(1) \033[m'))


%:
	make .call_fail MESSAGE="Inexisting recipe: [ $@ ]"

