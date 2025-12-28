
set(MODULE_NAME effects)
add_module_target(${MODULE_NAME})

add_subdirectory(stars)
add_subdirectory(solid)

target_link_libraries(${MODULE_NAME} PUBLIC
	effect
	engine_definitions
	timer
	#[[
	serialization
	]]#
	stars
	solid
)

target_sources(${MODULE_NAME} PUBLIC
	#[[
	FILE_SET effects TYPE CXX_MODULES
	FILE_SET gradient TYPE CXX_MODULES
	FILE_SET wheel TYPE CXX_MODULES
	FILE_SET chess TYPE CXX_MODULES
	FILE_SET plasma TYPE CXX_MODULES
	FILE_SET noise TYPE CXX_MODULES
	FILE_SET tunel TYPE CXX_MODULES
	FILE_SET fire TYPE CXX_MODULES
	Fire.cpp
	FILES
	]]#
	effects.cpp
	#[[
	Gradient.cpp
	Wheel.cpp
	ChessBoard.cpp
	Plasma.cpp
	RandomNoise.cpp
	Tunel.cpp
	Fire.cpp
	]]#
)

set(WARNING_SUPPRESSION "")
if(MSVC)
	set(${WARNING_SUPPRESSION} "/W0")
else()
	set(${WARNING_SUPPRESSION} "-w")
endif()
set_source_files_properties(Stars.cpp
	APPEND PROPERTY COMPILE_DEFINITIONS ${WARNING_SUPPRESSION}
)
