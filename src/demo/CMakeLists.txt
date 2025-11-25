set(EXECUTABLE_NAME demoscene)
add_executable(${EXECUTABLE_NAME})
#[[ TODO create executable cmake script
    in order to encapsulate coverate logic
]]#
if(EnableTesting)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE
		-coverage
	)
endif()

set(MODULE_NAME demo)
add_module_target_transitional(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PRIVATE engine
	PRIVATE effects
)

target_sources(${EXECUTABLE_NAME} PUBLIC
	main.cpp
)


target_link_libraries(${EXECUTABLE_NAME}
	PRIVATE demo
)

target_sources(${MODULE_NAME} PUBLIC
	demo.cpp
)


add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)

set(WARNING_SUPPRESSION "")
if(MSVC)
	set(${WARNING_SUPPRESSION} "/W0")
else()
	set(${WARNING_SUPPRESSION} "-w")
endif()
#directory level
add_compile_options(
	${WARNING_SUPPRESSION}
)
#target level
target_compile_options(${MODULE_NAME} PRIVATE
	${WARNING_SUPPRESSION}
)
#file level
set_source_files_properties(main.cpp
	APPEND PROPERTY COMPILE_DEFINITIONS ${WARNING_SUPPRESSION}
)
