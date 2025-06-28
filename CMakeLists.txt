# CMake requirements
cmake_minimum_required(VERSION 4.0.3)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX
)

# Project automated configuration
include(${CMAKE_SOURCE_DIR}/cmake/configure_project.cmake OPTIONAL RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake configure_project script found")
	configure_project()
else()
	message(WARNING "
	add_module_target.cmake script not found!

	Project will be configured with default values
	and custom user config parameters will be ignored")
endif()

# User configuration options
include(CMakeDependentOption)
if(NOT DEFINED EnableEditor)
	option(EnableEditor "enables generation of editor tool" OFF)
endif()
if(NOT DEFINED EnableExperimentalFeatures)
	option(EnableExperimentalFeatures "enables experimental features" OFF)
endif()
if(NOT DEFINED EnableTesting)
	option(EnableTesting "enables testing targets" OFF)
endif()
if(NOT DEFINED EnableInterProceduralOptimization)
	option(EnableInterProceduralOptimization "tries to enable IPO [EXPERIMENTAL]" OFF)
endif()
if(NOT DEFINED DisableAllButExperimental)
	cmake_dependent_option(
		DisableAllButExperimental "DISABLES regular targets" ON
		"EnableExperimentalFeatures" OFF
	)
endif()

# Experimental features (WIP)
if(EnableExperimentalFeatures)
	message(WARNING "experimental features enabled")

	if(EnableEditor)
		message(WARNING "editor is still experimental")
		add_subdirectory(src/editor)
	endif()
	if(EnableInterProceduralOptimization)
		include(CheckIPOSupported)
		check_ipo_supported(RESULT ipo_supported)
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})
		if(NOT ipo_supported)
			message(WARNING "Interprocedural Optimization not supported!")
		else()
			message(NOTICE "Interprocedural Optimization support enabled")
		endif()
	endif()
else()
	if(EnableInterProceduralOptimization)
		message(SEND_ERROR "
		IPO is still experimental!
		enable experimental features if you plan to use it")
	endif()
	if(EnableEditor)
		message(SEND_ERROR "
		editor is still experimental!
		enable experimental features if you plan to use it")
	endif()
endif()

# Project generation info
if(NOT DisableAllButExperimental)
	add_subdirectory(src)
	if(EnableTesting)
		message(NOTICE "enabling testing")
		include(CTest)
		enable_testing()
		add_subdirectory(test)
	else()
		message(STATUS "testing not enabled")
	endif()
else()
	message(WARNING "
	all non-experimental targets disabled")
endif()


# CMake configuration general user options cleanup
mark_as_advanced(FORCE
	CMAKE_INSTALL_PREFIX
	#[[
	ARTS_CONFIG
	ASOUND_LIB
	BUILD_TESTING
	CCACHE_BINARY
	CMAKE_EXPORT_COMPILE_COMMANDS
	DECOR_0_LIB
	DRM_LIB
	D_NAS_LIB
	FETCHCONTENT_FULLY_DISCONNECTED
	FETCHCONTENT_QUIET
	FETCHCONTENT_SOURCE_DIR_SDL2
	FETCHCONTENT_UPDATES_DISCONNECTED
	FETCHCONTENT_UPDATES_DISCONNECTED_SDL2
	GBM_LIB
	HAVE_XCURSOR_H
	HAVE_XDBE_H
	HAVE_XEXT_H
	HAVE_XFIXES_H_
	HAVE_XINPUT2_H
	HAVE_XRANDR_H
	HAVE_XRENDER_H
	HAVE_XSHAPE_H
	HAVE_XSS_H
	JACK_LIB
	PULSE_LIB
	SAMPLERATE_LIB
	SNDIO_LIB
	UDEV_LIB
	WAYLAND_CLIENT_LIB
	WAYLAND_CURSOR_LIB
	WAYLAND_EGL_LIB
	WAYLAND_SCANNER
	X11_LIB
	XCURSOR_LIB
	XEXT_LIB
	XFIXES_LIB
	XI_LIB
	XKBCOMMON_LIB
	XRANDR_LIB
	XRENDER_LIB
	XSS_LIB
	X_INCLUDEDIR
	]]#
)

