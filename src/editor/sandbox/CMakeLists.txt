add_executable(sandbox)

target_link_libraries(sandbox PRIVATE
	engine
	effect
	stars
	sdl_wrapper
)

target_sources(sandbox PUBLIC
	main.cpp
)
