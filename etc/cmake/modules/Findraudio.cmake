#TO DO handle other paths
set(INSTALLED_DIR /usr/local/)

if(EXISTS ${INSTALLED_DIR}/include/raudio)

	if(NOT TARGET raudio)
		add_library(raudio STATIC IMPORTED)
		target_include_directories(raudio INTERFACE
			${INSTALLED_DIR}/include/raudio
			${INSTALLED_DIR}/include/raudio/external
		)
		set_target_properties(raudio
			PROPERTIES
			IMPORTED_LOCATION ${INSTALLED_DIR}/lib/libraudio.a
		)
	endif()

	set(raudio_DIR "/usr/local/lib/")
	set(raudio_INCLUDE_DIR "/usr/local/include/raudio/")
	set(raudio_FOUND ON)

	mark_as_advanced(
		raudio_FOUND
		raudio_DIR
		raudio_INCLUDE_DIR
	)
endif()

