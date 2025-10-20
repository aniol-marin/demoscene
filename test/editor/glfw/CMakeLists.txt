set(TEST_TARGET test-glfw)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE glfw_wrapper
)

