set(TEST_TARGET test-pugi)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE serialization
)

