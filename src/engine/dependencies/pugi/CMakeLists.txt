set(MODULE_NAME serialization)
add_library(${MODULE_NAME})

FetchContent_Declare(
	pugixml
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/zeux/pugixml.git
	GIT_TAG ee86beb30e4973f5feffe3ce63bfa4fbadf72f38 # v 1.15
	#[[ forward compatibility
	GIT_REPOSITORY git@gitlab.com:amarinat/mirror_pugixml.git
	GIT_TAG 254e2ce6972a8731230f492f1f1d2d10022ebdc1 # custom branch WIP
	]]#
)
FetchContent_MakeAvailable(pugixml)

target_link_libraries( ${MODULE_NAME}
	#[[
	PUBLIC pugixml_experimental
	]]#
	PUBLIC pugixml
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	#[[ forward compatibility
	FILE_SET serialization TYPE CXX_MODULES
	FILES
	]]#
	pugi.cppm
)

mark_as_advanced(FORCE
	FETCHCONTENT_SOURCE_DIR_PUGIXML
	FETCHCONTENT_UPDATES_DISCONNECTED_PUGIXML
	PUGIXML_BUILD_DEFINES
	PUGIXML_COMPACT
	PUGIXML_INSTALL
	PUGIXML_WCHAR_MODE
)

