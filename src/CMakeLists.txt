add_executable(demoscene)

target_sources(demoscene PRIVATE
	FILE_SET demo TYPE CXX_MODULES
	FILE_SET injection TYPE CXX_MODULES
	FILES
	demo.cpp
	injection.cpp
)

target_sources(demoscene PRIVATE
	main.cpp
)
