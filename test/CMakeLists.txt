if(MoleDemo_EnableTesting AND NOT MoleDemo_DisableAllButExperimental)

	message(NOTICE "enabling testing")

	manage_dependency_catch()
	add_custom_target(tests)

	add_subdirectory(engine)
	add_subdirectory(custom_tests)
	if(MoleDemo_EnableEditor)
		add_subdirectory(editor)
	endif()

	add_custom_target(report_experimental
			COMMAND ${CMAKE_CTEST_COMMAND}
			-DCTEST_SOURCE_DIRECTORY=${CMAKE_SOURCE_DIR}
			-DCTEST_BINARY_DIRECTORY=${CMAKE_BINARY_DIR}
			-DCTEST_CMAKE_GENERATOR=${CMAKE_GENERATOR}
			-DUSER=${CMAKE_CXX_COMPILER_ID}${CMAKE_CXX_COMPILER_VERSION}
			-S ${CMAKE_SOURCE_DIR}/ctest/full-report.cmake
	)

else()
	message(STATUS "testing not enabled")
endif()
