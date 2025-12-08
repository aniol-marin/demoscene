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

	#[=[ we go to the 3 steps indirection because of user dependencies ]=]#
	#[[ 1/3 - "install command for files"
	install(
		FILES
		EXPORT ${EXECUTABLE_NAME}
		DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/moledemo"
		NAMESPACE mole::
		FILE moledemo-targets.cmake
		COMPONENT moledemo
	)
	]]#
	#[[ 2/3 - "install command for targets"
	install(
		FILES
		"${CMAKE_CURRENT_BINARY_DIR}/moledemo-config.cmake" # helper output
		"${CMAKE_CURRENT_BINARY_DIR}/moledemo-version.cmake"
		DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/moledemo"
		COMPONENT moledemo
	)
	]]#
	#[[ 3/3 - "install command for cmake native package config file"
	install(
		EXPORT moledemo-targets
		DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/moledemo"
		NAMESPACE mole::
		FILE moledemo-targets.cmake
		COMPONENT moledemo
	)
	]]#

	#[[ unified post-modern-version ]]#
	install(
		PACKAGE_INFO moledemo
		EXPORT moledemo-targets
		DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/moledemo"
		NAMESPACE mole::
		FILE moledemo-config.cmake
		COMPONENT moledemo
		EXPORT_PACKAGE_DEPENDENCIES pugixml
	)

	#[=[ naive approach, with commments
	install(
		FILES
		"${CMAKE_CURRENT_BINARY_DIR}/moledemo-config.cmake" # helper output
		"${CMAKE_CURRENT_BINARY_DIR}/moledemo-version.cmake"
		DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/moledemo"

		TARGETS ${EXECUTABLE_NAME}
		#[[ no components yet. Add only if it really is a component
		COMPONENT ...
		]]#
		EXPORT ${EXECUTABLE_NAME}-targets # allows find_package components handling 
		#[[
		from here on:
		- CMAKE_*
		- $ENV{*}
		- install(DESTINATION)
		- "as a dev, any of the above is none of your business"
		]]#
		DESTINATION # default (not specified == everything else)
		${CMAKE_INSTALL_LIBDIR}$<$<CONFIG:Debug>:/debug>
		NAMESPACE mole::
		RUNTIME # specified == specific "artifact kinds"
		DESTINATION ${CMAKE_INSTALL_BINDIR}$<$<CONFIG:Debug>:/debug>
		FILE_SET HEADERS # "it's overloaded" == knows internal structure
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)

	include(CMakePackageConfigHelpers)
	#[[ first generator (main one) ]]
	configure_package_config_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/moledemo-config.cmake.in" # helper template
		"${CMAKE_CURRENT_BINARY_DIR}/moledemo-config.cmake" # helper output
		#[[ needs to be provided, does nothing ]]
		INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/moledemo-config.cmake"
		#[[ this is just wrong, get rid of it
		PATH_VARS PROJECT_NAME PROJECT_VERSION
		]]#
	)

	#[[ lightweight generator (for version checking) ]]
	write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/moledemo-version.cmake"
		#[[ default, can be skipped
		VERSION ${PROJECT_VERSION}
		]]#
		#[[ unless you need multiple versions, no need to specify for find_package. Skip by default ]]
		COMPATIBILITY ExactVersion
	)
	]=]#

else()
	message(WARNING "All non-experimental targets disabled")
endif()

if(NOT MoleDemo_DisableAllButExperimental AND MoleDemo_EnableEditor)
	message(NOTICE "enabling editor")
	add_subdirectory(editor)
else()
	message(STATUS "editor not enabled")
endif()

