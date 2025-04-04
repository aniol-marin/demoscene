enable_testing()
set(TEST_TARGET "test-injection")

add_executable(${TEST_TARGET})

target_link_libraries( ${TEST_TARGET}
    PRIVATE Catch2::Catch2WithMain
    PRIVATE engine
)

target_sources(${TEST_TARGET} PRIVATE
	FILE_SET injection TYPE CXX_MODULES
)

target_sources(${TEST_TARGET} PRIVATE
	test.cpp
)

add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

