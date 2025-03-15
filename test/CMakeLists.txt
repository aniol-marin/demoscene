set(TEST_TARGET "test")

add_executable(${TEST_TARGET})

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG fa43b77429ba76c462b1898d6cd2f2d7a9416b14 #v3.7.1
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries( ${TEST_TARGET}
    PRIVATE Catch2::Catch2WithMain
    PRIVATE engine
)

target_sources(${TEST_TARGET} PRIVATE
	FILE_SET injection TYPE CXX_MODULES
)

target_sources(${TEST_TARGET} PRIVATE
	test.cpp
)
