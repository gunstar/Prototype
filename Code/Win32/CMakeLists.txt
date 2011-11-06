include_directories(".")
include_directories("../C++")
include_directories("C:/Program Files/Microsoft DirectX SDK (June 2010)/Include")

file(GLOB_RECURSE Win32Src *.cpp *.h)

add_library(Win32 STATIC ${Win32Src})
