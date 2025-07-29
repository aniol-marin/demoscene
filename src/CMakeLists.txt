add_subdirectory(effects)
add_subdirectory(engine)
add_subdirectory(demo)

if(EnableEditor)
	message(NOTICE "enabling editor")
	add_subdirectory(editor)
else()
	message(STATUS "editor not enabled")
endif()

