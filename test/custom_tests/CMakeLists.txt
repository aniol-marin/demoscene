file(GLOB test_files
	"*.cpp"
)

create_test_sourcelist(test_files_src custom_tests.cpp ${test_files})
add_executable(custom_tests ${test_files_src})
