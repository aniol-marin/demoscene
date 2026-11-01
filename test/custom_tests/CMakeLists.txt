file(GLOB test_files
	"*.cpp"
)

create_test_sourcelist(test_files_src custom_tests.cpp ${test_files})
foreach(file ${test_files})
	get_filename_component(name ${file} NAME)
	set(test_name custom_test_${name})
	add_executable(${test_name} ${file})
	if(MoleDemo_Testing_EnableCoverage)
		if(MSVC)
			target_compile_options(${test_name} PRIVATE "/fsanitize-coverage")

		else()
			target_compile_options(${test_name} PRIVATE -coverage)
			target_link_options(${test_name} PRIVATE -coverage)
		endif()
	endif()
endforeach()
