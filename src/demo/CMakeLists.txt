set(MODULE_NAME demo)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME} PRIVATE
	engine
	effects
)

target_sources(${MODULE_NAME} PRIVATE
	demo.cpp
)

set(WARNING_SUPPRESSION "")
if(MSVC)
	set(${WARNING_SUPPRESSION} "/W0")
else()
	set(${WARNING_SUPPRESSION} "-w")
endif()
#directory level
add_compile_options(
	${WARNING_SUPPRESSION}
)
#target level
target_compile_options(${MODULE_NAME} PRIVATE
	${WARNING_SUPPRESSION}
)
#file level
set_source_files_properties(demo.cpp
	APPEND PROPERTY COMPILE_DEFINITIONS ${WARNING_SUPPRESSION}
)
