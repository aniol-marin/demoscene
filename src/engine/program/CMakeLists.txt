set(MODULE_NAME program)
add_library(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET ${MODULE_NAME} TYPE CXX_MODULES
	FILES
	program.cpp
)
