file(GLOB test_files
	"*.cpp"
)

create_test_sourcelist(test_files_src custom_tests.cpp ${test_files})
foreach(file ${test_files})
	get_filename_component(name ${file} NAME)
	add_executable(custom_test_${name} ${file})
endforeach()
