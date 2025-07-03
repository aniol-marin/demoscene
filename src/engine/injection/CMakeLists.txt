set(MODULE_NAME injection)
add_module_target(${MODULE_NAME})

target_sources( ${MODULE_NAME} PUBLIC
	FILE_SET injection TYPE CXX_MODULES
	FILES
	injection.cpp
)
