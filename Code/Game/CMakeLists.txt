include_directories("../C++")
include_directories("../Engine")

file(GLOB_RECURSE Src *.cpp *.h)

add_library(Game STATIC ${Src})
