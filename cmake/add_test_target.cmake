function(add_test_target TARGET_NAME)

	enable_testing()
	set(TEST_TARGET "${TARGET_NAME}")

	add_executable(${TEST_TARGET})

	set_target_properties(${TEST_TARGET} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY test
	)
	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${TEST_TARGET} PRIVATE -coverage)
		target_link_options(${TEST_TARGET} PRIVATE -coverage)
	endif()

	target_link_libraries(${TEST_TARGET} PRIVATE
		Catch2::Catch2WithMain
	)

	target_sources(${TEST_TARGET} PRIVATE
		test.cpp
	)

	add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

endfunction()
