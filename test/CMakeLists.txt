include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG fa43b77429ba76c462b1898d6cd2f2d7a9416b14 #v3.7.1
)
FetchContent_MakeAvailable(Catch2)

include(${CMAKE_SOURCE_DIR}/cmake/add_test_target.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_test_target script found")
else()
	message(ERROR_FAIL "add_test_target.cmake script not found.
	Disable testing if this was intended")
endif()

add_subdirectory(engine)
add_subdirectory(editor)

mark_as_advanced(FORCE
	CATCH_DEVELOPMENT_BUILD
	CATCH_ENABLE_REPRODUCIBLE_BUILD
	CATCH_INSTALL_DOCS
	CATCH_INSTALL_EXTRAS
	FETCHCONTENT_SOURCE_DIR_CATCH2
	FETCHCONTENT_UPDATES_DISCONNECTED_CATCH2
)

