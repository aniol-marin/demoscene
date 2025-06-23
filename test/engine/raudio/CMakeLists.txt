set(TEST_TARGET test-audio)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE raudio_wrapper
)

