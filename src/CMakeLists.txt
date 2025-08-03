if(NOT DisableAllButExperimental)
	add_subdirectory(effects)
	add_subdirectory(engine)
	add_subdirectory(demo)
else()
	message(WARNING "
	all non-experimental targets disabled")
endif()

if(EnableEditor)
	message(NOTICE "enabling editor")
	add_subdirectory(editor)
else()
	message(STATUS "editor not enabled")
endif()

