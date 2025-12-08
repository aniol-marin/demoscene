set(TEST_TARGET test-audio)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE raudio_wrapper
)

add_custom_command(TARGET ${TEST_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources
		$<TARGET_FILE_DIR:${TEST_TARGET}>/resources
)

