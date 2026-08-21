set(TEST_TARGET test-sdl)

add_test_target(${TEST_TARGET})

#[[ needs some more tweaking
set_tests_properties(${TEST_TARGET}
	PROPERTY RESOURCE_LOCK gpu
)
]]#

target_link_libraries(${TEST_TARGET} PUBLIC
	sdl_wrapper
)

