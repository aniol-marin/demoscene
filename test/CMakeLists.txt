if(MoleDemo_EnableTesting AND NOT MoleDemo_DisableAllButExperimental)

	message(NOTICE "enabling testing")

	manage_dependency_catch()
	add_custom_target(tests)

	add_subdirectory(engine)
	add_subdirectory(custom_tests)
	if(MoleDemo_EnableEditor)
		add_subdirectory(editor)
	endif()

else()
	message(STATUS "testing not enabled")
endif()
