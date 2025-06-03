set(MODULE_NAME sound)
add_library(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC raudio_wrapper
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET sound TYPE CXX_MODULES
	FILES
	sound.cpp
)
