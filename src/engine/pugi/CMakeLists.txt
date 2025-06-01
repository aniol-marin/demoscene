set(MODULE_NAME pugi_wrapper)
add_library(${MODULE_NAME})

include(FetchContent)
FetchContent_Declare(
	pugixml
	EXCLUDE_FROM_ALL
	#[[ Original repository, without c++20 modules support
	GIT_REPOSITORY https://github.com/zeux/pugixml.git
	GIT_TAG ee86beb30e4973f5feffe3ce63bfa4fbadf72f38 # v 1.15
	]]#
	GIT_REPOSITORY git@gitlab.com:amarinat/mirror_pugixml.git
	#GIT_TAG dac14184667f98e03f0a78bdfa2aa383c78484dc # PR#644 with CMake WIP
	GIT_TAG d27a82ee2faffbcf3ada50b1a9e6d2e9d946c9cb # custom branch WIP
)
FetchContent_MakeAvailable(pugixml)

target_link_libraries( ${MODULE_NAME}
	PUBLIC pugixml_experimental
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET pugixml_experimental TYPE CXX_MODULES
	FILES
	fake-pugi.cpp
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET pugi_wrapper TYPE CXX_MODULES
	FILES
	pugi.cppm
)
