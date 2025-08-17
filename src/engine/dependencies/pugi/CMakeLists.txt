set(MODULE_NAME serialization)
add_module_target(${MODULE_NAME})

include(${CMAKE_SOURCE_DIR}/cmake/manage_dependency_pugixml.cmake REQUIRED)
manage_dependency_pugixml()

target_link_libraries( ${MODULE_NAME}
	PUBLIC pugixml
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	#[[ forward compatibility
	FILE_SET serialization TYPE CXX_MODULES
	FILES
	pugi.cppm
	]]#
	pugi.cpp
)

