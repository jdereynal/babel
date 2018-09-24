project(Babel)
	cmake_minimum_required(VERSION 3.9.6)
	set(CMAKE_CXX_STANDARD 17)
	include_directories(${PROJECT_SOURCE_DIR}/include)
	file(GLOB_RECURSE SOURCES_SERVER RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*.cpp")
	file(GLOB_RECURSE SOURCES_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*.cpp")

	#conan
	include(${CMAKE_BINARY_DIR}/build/conanbuildinfo.cmake)
	conan_basic_setup()
	
	add_executable(babel_server ${SOURCES_SERVER})
	add_executable(babel_client ${SOURCES_CLIENT})
