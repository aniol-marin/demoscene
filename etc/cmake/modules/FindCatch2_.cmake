#TO DO handle other paths
set(INSTALLED_DIR /usr/local/)

if(EXISTS ${INSTALLED_DIR}/lib/libCatch2WithMain.a)

	if(NOT TARGET Catch2::Catch2)
		add_library(Catch2::Catch2 STATIC IMPORTED)
		set_target_properties(Catch2::Catch2
			PROPERTIES
			IMPORTED_LOCATION ${INSTALLED_DIR}/lib/libCatch2.a
			#[[ according to official find:
			INTERFACE_COMPILE_FEATURES "cxx_alignas;cxx_alignof;cxx_attributes;cxx_auto_type;cxx_constexpr;cxx_defaulted_functions;cxx_deleted_functions;cxx_final;cxx_lambdas;cxx_noexcept;cxx_override;cxx_range_for;cxx_rvalue_references;cxx_static_assert;cxx_strong_enums;cxx_trailing_return_types;cxx_unicode_literals;cxx_user_literals;cxx_variadic_macros"
			]]#
			INTERFACE_INCLUDE_DIRECTORIES ${INSTALLED_DIR}/include/
		)
	endif()
	if(NOT TARGET Catch2::Catch2WithMain)
		add_library(Catch2::Catch2WithMain STATIC IMPORTED)
		set_target_properties(Catch2::Catch2WithMain
			PROPERTIES
			IMPORTED_LOCATION ${INSTALLED_DIR}/lib/libCatch2Main.a
			INTERFACE_LINK_LIBRARIES Catch2::Catch2
			INTERFACE_INCLUDE_DIRECTORIES ${INSTALLED_DIR}/include/
		)
	endif()

	set(Catch2_DIR "/usr/local/lib/")
	set(Catch2_INCLUDE_DIR "/usr/local/include/catch2/")
	set(Catch2_FOUND ON)

	mark_as_advanced(
		Catch2_FOUND
		Catch2_DIR
		Catch2_INCLUDE_DIR
	)
endif()

