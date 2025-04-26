# CMakeList.txt : CMake project for TeyoClient, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

project ("TeyoClient")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

# Add source to this project's executable.
add_executable (TeyoClient  "main.cpp")

target_link_libraries(TeyoClient
	PRIVATE
	Boost::boost
	nlohmann_json::nlohmann_json
)

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET TeyoClient PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.
