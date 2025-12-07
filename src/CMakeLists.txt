set(EXECUTABLE_NAME demoscene)
add_subdirectory(utils)

if(NOT MoleDemo_DisableAllButExperimental)

	add_subdirectory(effects)
	add_subdirectory(engine)
	add_subdirectory(demo)
	add_executable_target(${EXECUTABLE_NAME})

	target_sources(${EXECUTABLE_NAME} PRIVATE
		main.cpp
	)

	target_link_libraries(${EXECUTABLE_NAME} PRIVATE
		demo
	)

	add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
	)

	install(
		TARGETS ${EXECUTABLE_NAME}
		#[[ no components yet. Add only if it really is a component
		COMPONENT ...
		]]#
		EXPORT ${EXECUTABLE_NAME}-targets
		#[[
		from here on:
		- CMAKE_*
		- $ENV{*}
		- install(DESTINATION)
		- "as a dev, any of the above is none of your business"
		]]#
		DESTINATION # default (not specified == everything else)
		${CMAKE_INSTALL_LIBDIR}$<$<CONFIG:Debug>:/debug>
		RUNTIME # specified == specific "artifact kinds"
			DESTINATION ${CMAKE_INSTALL_BINDIR}$<$<CONFIG:Debug>:/debug>
		FILE_SET HEADERS # "it's overloaded" == knows internal structure
			DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
else()
	message(WARNING "All non-experimental targets disabled")
endif()

if(NOT MoleDemo_DisableAllButExperimental AND MoleDemo_EnableEditor)
	message(NOTICE "enabling editor")
	add_subdirectory(editor)
else()
	message(STATUS "editor not enabled")
endif()

