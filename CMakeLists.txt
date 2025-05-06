# CMakeList.txt : CMake project for TeyoClient, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.21)

project ("TeyoClient")
add_compile_definitions(_WIN32_WINNT=0x0A00)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE INCLUDES CONFIGURE_DEPENDS include/*.hpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(Qt6_DIR "C:/Qt/6.9.0/msvc2022_64/lib/cmake/Qt6")
# set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/include")
# set(Boost_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/include")
# set(Boost_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/lib")
# set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/include")

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCES} ${INCLUDES})

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
