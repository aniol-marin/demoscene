set(MODULE_NAME effects)
add_library(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC effect
	PUBLIC engine_definitions
	PUBLIC timer
	PUBLIC serialization
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET effects TYPE CXX_MODULES
	FILE_SET stars TYPE CXX_MODULES
	FILE_SET solid TYPE CXX_MODULES
	FILE_SET gradient TYPE CXX_MODULES
	FILE_SET wheel TYPE CXX_MODULES
	FILE_SET chess TYPE CXX_MODULES
	FILE_SET plasma TYPE CXX_MODULES
	FILE_SET noise TYPE CXX_MODULES
	FILE_SET tunel TYPE CXX_MODULES
	FILE_SET fire TYPE CXX_MODULES
	FILES
	effects.cpp
	Stars.cpp
	Solid.cpp
	Gradient.cpp
	Wheel.cpp
	ChessBoard.cpp
	Plasma.cpp
	RandomNoise.cpp
	Tunel.cpp
	Fire.cpp
)

set_source_files_properties(Stars.cpp
	APPEND PROPERTY COMPILE_DEFINITIONS ${WARNING_SUPPRESSION}
)
