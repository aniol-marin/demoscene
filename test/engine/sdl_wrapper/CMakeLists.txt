set(TEST_TARGET test-sdl)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE sdl_wrapper
)

