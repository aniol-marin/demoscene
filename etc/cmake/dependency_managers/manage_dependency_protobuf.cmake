function(manage_dependency_protobuf)

	#[[
	find_package(Protobuf CONFIG)
	]]#
	FetchContent_Declare(
		Protobuf
		EXCLUDE_FROM_ALL
		GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
		GIT_TAG a8d85ffbc7158660b4247f732371d1b07780510e # 33.1
		FIND_PACKAGE_ARGS NAMES Protobuf CONFIG
	)
	FetchContent_MakeAvailable(Protobuf)

	mark_as_advanced(FORCE
		TEST_PROTOBUF
	)

endfunction()
