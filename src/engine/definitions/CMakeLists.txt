set(ENGINE_DEFINITIONS_LIBRARY_NAME "engine_definitions")
add_library(${ENGINE_DEFINITIONS_LIBRARY_NAME})
target_sources(${ENGINE_DEFINITIONS_LIBRARY_NAME} PUBLIC
	FILE_SET engine_definitions TYPE CXX_MODULES
	FILES
	definitions.cpp
)
