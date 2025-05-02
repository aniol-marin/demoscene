include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG fa43b77429ba76c462b1898d6cd2f2d7a9416b14 #v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(sdl_wrapper)
add_subdirectory(injection)
add_subdirectory(raudio)
add_subdirectory(timer)

