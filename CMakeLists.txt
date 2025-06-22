cmake_minimum_required(VERSION 4.0.3)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)

project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX
)

option(EnableTesting "enables testing targets" OFF)
option(EnableExperimentalFeatures "enables experimental features" OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(EnableExperimentalFeatures)
	include(CheckIPOSupported)
	check_ipo_supported(RESULT ipo_supported)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})
	#[[
	]]#

	include(./cmake/add_test_target.cmake RESULT_VARIABLE status)
	if(status)
		message(NOTICE "script found")
	else()
		message(ERROR_FAIL "script not found")
	endif()
else()
	message(WARNING "add_test_target is still experimental, configuration will fail")
endif()

add_subdirectory(src)

if(EnableTesting)
	message(NOTICE "enabling testing")
	include(CTest)
	enable_testing()
	add_subdirectory(test)
else()
	message(STATUS "testing not enabled")
endif()

mark_as_advanced(FORCE
	ARTS_CONFIG
	ASOUND_LIB
	BUILD_TESTING
	CCACHE_BINARY
	CMAKE_INSTALL_PREFIX
	DECOR_0_LIB
	DRM_LIB
	D_NAS_LIB
	FETCHCONTENT_FULLY_DISCONNECTED
	FETCHCONTENT_QUIET
	FETCHCONTENT_SOURCE_DIR_SDL2
	FETCHCONTENT_UPDATES_DISCONNECTED_SDL2
	FETCHCONTENT_UPDATES_DISCONNECTED
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
)

