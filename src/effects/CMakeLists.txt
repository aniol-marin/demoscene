target_sources(${MODULE_NAME} PUBLIC
	FILE_SET effect TYPE CXX_MODULES
	FILE_SET effect TYPE CXX_MODULES
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
	Effect.cpp
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
