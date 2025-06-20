set(MODULE_NAME program)
add_library(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	#[[ deactivation for retrocompatibility
	FILE_SET ${MODULE_NAME} TYPE CXX_MODULES
	FILES
	]]#
	program.cpp
)

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

