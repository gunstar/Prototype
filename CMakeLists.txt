#####################################################################
# http://www.cmake.org/Wiki/CMake
#####################################################################

cmake_minimum_required(VERSION 2.6)

project(Prototype)

#####################################################################
# Compiler flags
#####################################################################

if(WIN32)
	set(CMAKE_CXX_FLAGS "/D _CRT_SECURE_NO_WARNINGS")
else()
	set(CMAKE_CXX_FLAGS "-DLINUX -Wall -fno-strict-aliasing -Wno-deprecated -Wno-non-virtual-dtor -O3 -DNDEBUG -msse2 -mfpmath=sse")
endif()

#####################################################################
# Libraries
#####################################################################

add_subdirectory(Code/C++)
add_subdirectory(Code/Engine)
add_subdirectory(Code/Game)
add_subdirectory(Code/Games)

if(WIN32)
	add_subdirectory(Code/Engine2Win32)
	add_subdirectory(Code/Win32)
else()
	add_subdirectory(Code/Engine2Linux)
endif()

#####################################################################
# Exe
#####################################################################

include_directories("Code/C++")

include_directories("Code/Engine")
include_directories("Code/Game")

if(WIN32)
	include_directories("Code/Engine2Win32")
	include_directories("Code/Win32")
	include_directories("C:/Program Files/Microsoft DirectX SDK (June 2010)/Include")

	link_directories("C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86")

	add_executable(Prototype WIN32 Code/Boot/apBoot.cpp)
else()
	include_directories("Code/Engine2Linux")

	add_executable(Prototype Code/Boot/apBoot.cpp)
endif()

#####################################################################
# Linking:
#####################################################################

target_link_libraries(Prototype CityGame DungeonGame FencingGame FPRTSGame IGI RacingGame ShootingGame TestGame)
target_link_libraries(Prototype EngineAdapter Engine Game Cpp)

if(WIN32)
	target_link_libraries(Prototype dxguid d3d9 d3dx9 dinput8 comctl32 Win32)
endif()
