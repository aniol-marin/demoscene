set(CTEST_NIGHTLY_START_TIME "0:00:00 UTC")
#set(CTEST_SUBMIT_URL "https://...")

set(CTEST_SITE "molegames.net")
set(CTEST_BUILD_NAME "Trisquel")
set(CTEST_SOURCE_DIRECTORY "/home/bru/demoscene/")
set(CTEST_BINARY_DIRECTORY "${CTEST_SOURCE_DIRECTORY}/build")
set(CTEST_CMAKE_GENERATOR "Ninja")
find_program(CTEST_UPDATE_COMMAND "git")

#[[
ctest_start("Experimental")
ctest_update()
ctest_configure()
ctest_build()
ctest_test()
ctest_submit()
]]#
