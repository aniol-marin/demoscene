set(TEST_TARGET "test-sdl")

add_executable(${TEST_TARGET})

target_link_libraries( ${TEST_TARGET}
    PRIVATE Catch2::Catch2WithMain
    PRIVATE sdl_wrapper
)

target_sources(${TEST_TARGET} PRIVATE
	FILE_SET sdl_wrapper TYPE CXX_MODULES
)

target_sources(${TEST_TARGET} PRIVATE
	test.cpp
)
