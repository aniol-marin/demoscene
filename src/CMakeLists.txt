add_subdirectory(utils)

if(NOT DisableAllButExperimental)
	if(NOT Disable_Demo)
		add_subdirectory(demo)
		add_subdirectory(effects)
	endif()
	if(NOT Disable_Engine)
		add_subdirectory(engine)
	endif()
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

