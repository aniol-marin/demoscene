add_executable(sandbox)

target_link_libraries(sandbox PRIVATE
	engine
)

target_sources(sandbox PUBLIC
	main.cpp
)
