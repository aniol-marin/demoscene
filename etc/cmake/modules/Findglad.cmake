#TO DO handle other paths
set(INSTALLED_DIR /usr/local/)

if(EXISTS ${INSTALLED_DIR}/include/glad)

	if(NOT TARGET glad)
		add_library(glad STATIC IMPORTED)
		target_include_directories(glad INTERFACE
			${INSTALLED_DIR}/include/glad
		)
		set_target_properties(glad
			PROPERTIES
			IMPORTED_LOCATION ${INSTALLED_DIR}/lib/libglad.a
		)
	endif()

	set(glad_DIR "/usr/local/lib/")
	set(glad_INCLUDE_DIR "/usr/local/include/glad/")
	set(glad_FOUND ON)

	mark_as_advanced(
		glad_FOUND
		glad_DIR
		glad_INCLUDE_DIR
	)
endif()

