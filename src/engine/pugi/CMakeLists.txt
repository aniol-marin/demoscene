set(MODULE_NAME pugi_wrapper)
add_library(${MODULE_NAME})

include(FetchContent)
FetchContent_Declare(
	pugixml
	EXCLUDE_FROM_ALL
	#[[ Unmerged alternative, lacks CMake integration for what it seems
	GIT_REPOSITORY https://github.com/zeux/pugixml.git
	GIT_TAG ee86beb30e4973f5feffe3ce63bfa4fbadf72f38 # v 1.15
	GIT_TAG 4a9169f0ee8e0edebf1ce0a74784883cd9506924 # PR#644 c++20 module support
	]]#
	GIT_REPOSITORY git@gitlab.com:amarinat/mirror_pugixml.git
	GIT_TAG 814878dddc4bc9e1fc79ea6f4aa3c55174765240 # PR#644 with CMake WIP
)
FetchContent_MakeAvailable(pugixml)

target_link_libraries( ${MODULE_NAME}
	PUBLIC pugixml
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	#[[
	]]#
	FILE_SET pugi_wrapper TYPE CXX_MODULES
	FILES
	pugi.cppm
)
