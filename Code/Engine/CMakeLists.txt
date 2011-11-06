include_directories("../C++")

file(GLOB_RECURSE Src *.cpp *.h)

add_library(Engine STATIC ${Src})
