add_executable_target(sandbox)

target_link_libraries(sandbox PRIVATE
	engine
	stars
)

target_sources(sandbox PUBLIC
	main.cpp
)
