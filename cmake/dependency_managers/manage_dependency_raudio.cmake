function(manage_dependency_raudio)

	if(NOT MoleDemo_ForceFetchedDependencies)
		find_package(raudio QUIET)
	endif()

	if(NOT raudio_FOUND)
		FetchContent_Declare(
			raudio
			EXCLUDE_FROM_ALL
			GIT_REPOSITORY https://github.com/raysan5/raudio.git
			GIT_TAG 711c86eae17db9a94af575f7a5b496244b48b22d # master
			SOURCE_SUBDIR projects/CMake
		)
		set(BUILD_RAUDIO_EXAMPLES OFF)
		set(SUPPORT_FILEFORMAT_WAV OFF)
		set(SUPPORT_FILEFORMAT_OGG OFF)
		set(SUPPORT_FILEFORMAT_MP3 ON)
		set(SUPPORT_FILEFORMAT_QOA OFF)
		set(SUPPORT_FILEFORMAT_FLAC OFF)
		set(SUPPORT_FILEFORMAT_XM OFF)
		set(SUPPORT_FILEFORMAT_MOD OFF)
		add_compile_options( -fPIE)
		add_compile_definitions(TRACELOG="TRACELOG( ...)")
		FetchContent_MakeAvailable(raudio)

		mark_as_advanced(FORCE
			FETCHCONTENT_SOURCE_DIR_RAUDIO
			FETCHCONTENT_UPDATES_DISCONNECTED_RAUDIO
			BUILD_RAUDIO_EXAMPLES
			SUPPORT_FILEFORMAT_FLAC
			SUPPORT_FILEFORMAT_MOD
			SUPPORT_FILEFORMAT_MP3
			SUPPORT_FILEFORMAT_OGG
			SUPPORT_FILEFORMAT_QOA
			SUPPORT_FILEFORMAT_WAV
			SUPPORT_FILEFORMAT_XM
		)
	endif()

endfunction()
