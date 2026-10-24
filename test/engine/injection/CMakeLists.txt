set(TEST_TARGET test-injection)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET} PUBLIC
	injection
)

