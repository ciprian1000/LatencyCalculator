cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
	set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
	foreach(CompilerFlag ${CompilerFlags})
	  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()
endif()

#add_subdirectory(external/googletest)
add_subdirectory(external/rapidjson)
add_subdirectory(src)

enable_testing()
