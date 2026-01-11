
set(MODULE_NAME effects)
add_module_target(${MODULE_NAME})

add_subdirectory(fire)
add_subdirectory(solid)
add_subdirectory(stars)
add_subdirectory(tunnel)

target_link_libraries(${MODULE_NAME} PUBLIC
	stars
	solid
	tunnel
	fire
)

target_sources(${MODULE_NAME} PUBLIC
	#[[
	FILE_SET effects TYPE CXX_MODULES
	FILE_SET gradient TYPE CXX_MODULES
	FILE_SET wheel TYPE CXX_MODULES
	FILE_SET chess TYPE CXX_MODULES
	FILE_SET plasma TYPE CXX_MODULES
	FILE_SET noise TYPE CXX_MODULES
	FILES
	]]#
	effects.cpp
	#[[
	Gradient.cpp
	Wheel.cpp
	ChessBoard.cpp
	Plasma.cpp
	RandomNoise.cpp
	]]#
)

