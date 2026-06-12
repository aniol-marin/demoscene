project(mole_raudio LANGUAGES C)

set(TEST_TARGET test-audio)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET} PUBLIC
	engine
)

add_custom_command(TARGET ${TEST_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources
		$<TARGET_FILE_DIR:${TEST_TARGET}>/resources
)

