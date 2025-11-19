set(MODULE_NAME raudio_wrapper)
add_module_target(${MODULE_NAME})

manage_dependency_raudio()

target_link_libraries( ${MODULE_NAME} PUBLIC
	raudio
	engine_definitions
)

target_sources(${MODULE_NAME} PRIVATE
	raudio.cpp
)

