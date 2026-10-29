function(manage_dependencies)

	include(dependency_managers/manage_dependency_catch.cmake REQUIRED)
	include(dependency_managers/manage_dependency_glad.cmake REQUIRED)
	include(dependency_managers/manage_dependency_glfw.cmake REQUIRED)
	include(dependency_managers/manage_dependency_imgui.cmake REQUIRED)
	include(dependency_managers/manage_dependency_pugixml.cmake REQUIRED)
	include(dependency_managers/manage_dependency_raudio.cmake REQUIRED)
	include(dependency_managers/manage_dependency_sdl.cmake REQUIRED)
	include(dependency_managers/manage_dependency_protobuf.cmake REQUIRED)

endfunction()
