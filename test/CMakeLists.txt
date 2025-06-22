include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG fa43b77429ba76c462b1898d6cd2f2d7a9416b14 #v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(injection)
add_subdirectory(input)
add_subdirectory(program)
add_subdirectory(pugi_wrapper)
add_subdirectory(raudio)
add_subdirectory(renderables)
add_subdirectory(sdl_wrapper)
add_subdirectory(timeline)
add_subdirectory(timer)

mark_as_advanced(FORCE
	CATCH_DEVELOPMENT_BUILD
	CATCH_ENABLE_REPRODUCIBLE_BUILD
	CATCH_INSTALL_DOCS
	CATCH_INSTALL_EXTRAS
	FETCHCONTENT_SOURCE_DIR_CATCH2
	FETCHCONTENT_UPDATES_DISCONNECTED_CATCH2
)

