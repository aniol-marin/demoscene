function(manage_dependency_glfw)

	if(MoleDemo_ForceFetchedDependencies)
		find_package(glfw3 QUIET)
	endif()

	if(NOT glfw3_FOUND)
		FetchContent_Declare(
			glfw
			EXCLUDE_FROM_ALL
			GIT_REPOSITORY https://github.com/glfw/glfw.git
			GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # v3.4
			#[[ disabled while forcing fetched dependencies is improved
			FIND_PACKAGE_ARGS NAMES glfw3
			]]#
		)
		FetchContent_MakeAvailable(glfw)

		set(GLFW_BUILD_DOCS OFF)
		set(GLFW_INSTALL OFF)
		set(GLFW_LIBRARY_TYPE STATIC)

	endif()

	mark_as_advanced(FORCE
		BUILD_SHARED_LIBS
		FETCHCONTENT_SOURCE_DIR_GLFW
		FETCHCONTENT_UPDATES_DISCONNECTED_GLFW
		GLFW_BUILD_DOCS
		GLFW_BUILD_EXAMPLES
		GLFW_BUILD_TESTS
		GLFW_BUILD_WAYLAND
		GLFW_BUILD_X11
		GLFW_DIR
		glfw3_DIR
		GLFW_INSTALL
		GLFW_LIBRARY_TYPE
		WAYLAND_SCANNER_EXECUTABLE
		X11_xcb_xkb_INCLUDE_PATH
	)

endfunction()
