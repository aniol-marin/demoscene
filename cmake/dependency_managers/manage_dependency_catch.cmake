function(manage_dependency_catch)

	#[[
	find_package(Catch2)
	]]#
	if(NOT Catch2_FOUND OR Catch2_VERSION_MAJOR LESS 3)
		FetchContent_Declare(
			Catch2
			GIT_REPOSITORY https://github.com/catchorg/Catch2.git
			GIT_TAG fa43b77429ba76c462b1898d6cd2f2d7a9416b14 #v3.7.1
		)
		FetchContent_MakeAvailable(Catch2)
	endif()

	mark_as_advanced(FORCE
		BUILD_TESTING
		Catch2_DIR
		CATCH_DEVELOPMENT_BUILD
		CATCH_ENABLE_REPRODUCIBLE_BUILD
		CATCH_INSTALL_DOCS
		CATCH_INSTALL_EXTRAS
		FETCHCONTENT_SOURCE_DIR_CATCH2
		FETCHCONTENT_UPDATES_DISCONNECTED_CATCH2
	)

endfunction()
