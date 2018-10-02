project(Babel)
	cmake_minimum_required(VERSION 3.9.6)
	set(CMAKE_CXX_STANDARD 17)
	include_directories(${PROJECT_SOURCE_DIR}/include)

	#sources
	file(GLOB_RECURSE SOURCES_SERVER RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*.cpp")
	file(GLOB_RECURSE SOURCES_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*.cpp")

	#lpthread
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)

	#conan
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
		include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
	else()
		include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
	endif()
	conan_basic_setup()

	#fid necessary boost packages
	find_package(Boost 1.67.0 COMPONENTS system REQUIRED)

	add_executable(babel_server ${SOURCES_SERVER})
	target_link_libraries(babel_server Threads::Threads)
	target_link_libraries(babel_server ${Boost_LIBRARIES})

	#add_executable(babel_client ${SOURCES_CLIENT})