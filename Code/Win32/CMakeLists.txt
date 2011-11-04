file(GLOB_RECURSE Win32Src *.cpp *.h)

add_library(Win32 STATIC ${Win32Src})
