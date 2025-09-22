function(manage_dependency_pugixml)

	FetchContent_Declare(
		pugixml
		EXCLUDE_FROM_ALL
		GIT_REPOSITORY https://github.com/zeux/pugixml.git
		GIT_TAG ee86beb30e4973f5feffe3ce63bfa4fbadf72f38 # v 1.15
		#[[ Original repository, without c++20 modules support
		GIT_REPOSITORY git@gitlab.com:amarinat/mirror_pugixml.git
		GIT_TAG 254e2ce6972a8731230f492f1f1d2d10022ebdc1 # custom branch WIP
		]]#
		FIND_PACKAGE_ARGS NAMES pugixml
	)
	FetchContent_MakeAvailable(pugixml)

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
