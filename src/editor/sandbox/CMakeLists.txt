add_executable(sandbox)

target_link_libraries(sandbox PRIVATE
	engine
	effects
)

target_sources(sandbox PUBLIC
	main.cpp
)
