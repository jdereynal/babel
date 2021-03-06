project(Babel)
	cmake_minimum_required(VERSION 3.9.6)
	set(CMAKE_CXX_STANDARD 17)
	include_directories(${PROJECT_SOURCE_DIR}/include)

	set(CMAKE_BUILD_TYPE Debug)
	set(CMAKE_CXX_FLAGS_DEBUG "-g3")

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

	#find necessary boost packages
	find_package(Boost 1.67.0 COMPONENTS system REQUIRED)

	#find necessary qt packages
	find_package(Qt5 COMPONENTS Core Network Widgets REQUIRED)
	if (Qt5_POSITION_INDEPENDENT_CODE)
		add_definitions(-fPIC)
	endif()

	add_executable(babel_server ${SOURCES_SERVER})
	target_link_libraries(babel_server Threads::Threads)
	target_link_libraries(babel_server ${Boost_LIBRARIES})

	set(CMAKE_AUTOUIC on)
	set(CMAKE_AUTOMOC on)
	set(CMAKE_INCLUDE_CURRENT_DIR on)
	add_executable(babel_client ${SOURCES_CLIENT})
	target_link_libraries(babel_client ${Boost_LIBRARIES} Qt5::Core Qt5::Network Qt5::Widgets opus portaudio jack rt asound Threads::Threads)
	set_property(TARGET babel_client PROPERTY POSITION_INDEPENDENT_CODE ON)

