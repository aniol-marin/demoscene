enable_testing()
set(TEST_TARGET test-render)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE Catch2::Catch2WithMain
	PRIVATE render
)
