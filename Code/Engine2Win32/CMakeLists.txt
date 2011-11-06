include_directories("../C++")
include_directories("../Engine")
include_directories("../Win32")
include_directories("C:/Program Files/Microsoft DirectX SDK (June 2010)/Include")

file(GLOB_RECURSE Src *.cpp *.h)

add_library(EngineAdapter STATIC ${Src})
