file(GLOB cmake_scripts *.cmake)

foreach(cmake_script ${cmake_scripts})
	include(${cmake_script} QUIET)
endforeach()
