enable_testing()
set(TEST_TARGET test-audio)

add_executable(${TEST_TARGET} EXCLUDE_FROM_ALL)

set_target_properties(${TEST_TARGET}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test
)

target_link_libraries( ${TEST_TARGET}
    PRIVATE Catch2::Catch2WithMain
    PRIVATE raudio_wrapper
)

target_sources(${TEST_TARGET} PRIVATE
	FILE_SET raudio_wrapper TYPE CXX_MODULES
)

target_sources(${TEST_TARGET} PRIVATE
	test.cpp
)

add_test(NAME build-${TEST_TARGET} COMMAND cmake --build ${CMAKE_BINARY_DIR} -t ${TEST_TARGET})
add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
set_tests_properties(${TEST_TARGET} PROPERTIES DEPENDS build-${TEST_TARGET})

