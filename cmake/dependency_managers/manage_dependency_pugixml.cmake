function(manage_dependency_pugixml)

	if(MoleDemo_ForceFetchedDependencies)
		find_package(pugixml 1.15 QUIET)
	endif()

	if(NOT pugixml_FOUND)
		FetchContent_Declare(
			pugixml
			EXCLUDE_FROM_ALL
			GIT_REPOSITORY https://github.com/zeux/pugixml.git
			GIT_TAG ee86beb30e4973f5feffe3ce63bfa4fbadf72f38 # v 1.15
			#[[ disabled while forcing fetched dependencies is improved
			FIND_PACKAGE_ARGS NAMES pugixml
			]]#
		)

		FetchContent_MakeAvailable(pugixml)
	endif()

	mark_as_advanced(FORCE
		FETCHCONTENT_SOURCE_DIR_PUGIXML
		FETCHCONTENT_UPDATES_DISCONNECTED_PUGIXML
		PUGIXML_BUILD_DEFINES
		PUGIXML_COMPACT
		pugixml_DIR
		PUGIXML_INSTALL
		PUGIXML_WCHAR_MODE
	)

endfunction()
