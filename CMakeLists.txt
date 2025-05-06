# CMakeList.txt : CMake project for TeyoClient, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.21)

project ("TeyoClient")
add_compile_definitions(_WIN32_WINNT=0x0A00)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
	Boost::boost
	nlohmann_json::nlohmann_json
	Qt6::Core 
	Qt6::Gui 
	Qt6::Widgets
)

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET TeyoClient PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.
