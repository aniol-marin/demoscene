include(${CMAKE_CURRENT_LIST_DIR}/moledemo-targets.cmake)

foreach(component IN LISTS moledemo-targets_FIND_COMPONENTS)
	if(moledemo-targets_FIND_REQUIRED_${component})
		set(moledemo_FOUND FALSE)
		return()
	endif()
endforeach()
