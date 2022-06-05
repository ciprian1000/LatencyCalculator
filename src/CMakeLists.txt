cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(This "LatencyCalculator")
project(${This})

include_directories(
	"${CMAKE_SOURCE_DIR}/external/rapidjson/include/"
	"include/"
)

set(HEADERS
	include/LatencyCalculator.h
	include/InterfaceController.h
	include/util.h
	include/DailyData.h
	include/DataLoader.h
	include/ServiceData.h
)

set(SOURCES
	cpp/main.cpp
	cpp/LatencyCalculator.cpp
	cpp/InterfaceController.cpp
	cpp/util.cpp
	cpp/DailyData.cpp
	cpp/DataLoader.cpp
	cpp/ServiceData.cpp
)

source_group(
    cpp
    FILES
	cpp/main.cpp
	cpp/LatencyCalculator.cpp
	cpp/InterfaceController.cpp
	cpp/util.cpp
	cpp/DailyData.cpp
	cpp/DataLoader.cpp
	cpp/ServiceData.cpp
)

source_group(
	include
	FILES
	include/LatencyCalculator.h
	include/InterfaceController.h
	include/util.h
	include/DailyData.h
	include/DataLoader.h
	include/ServiceData.h
)

add_executable(
    ${This}
	${SOURCES}
	${HEADERS}
)

#find_package(Threads)
target_link_libraries (
    ${This}
	PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
)

set(DATA_DIR_FROM ${CMAKE_SOURCE_DIR}/data)
set(DATA_DIR_TO ${CMAKE_CURRENT_BINARY_DIR}/data)

make_directory(${DATA_DIR_TO})

message(STATUS "Copying *.json from ${DATA_DIR_FROM} to ${DATA_DIR_TO}" )

file(GLOB DATA
  "${DATA_DIR_FROM}/*.json"
)
file(COPY ${DATA} DESTINATION ${DATA_DIR_TO})
