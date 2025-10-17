function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)

endfunction()

function(add_module_target_transitional MODULE_NAME)

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_20)

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/interface.cpp")
		target_sources(${MODULE_NAME} PUBLIC
			FILE_SET ${MODULE_NAME} TYPE CXX_MODULES
			FILES
			interface.cpp
		)
	else()
		message(WARNING "didn't find module interface file
		expected route: ${CMAKE_CURRENT_SOURCE_DIR}/interface.cpp
		")
	endif()

endfunction()

function(add_module_target_no_implementation MODULE_NAME)

	add_library(${MODULE_NAME} INTERFACE)

endfunction()
