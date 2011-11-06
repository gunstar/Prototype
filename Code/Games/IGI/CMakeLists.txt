file(GLOB_RECURSE Src *.cpp *.h)

add_library(IGI STATIC ${Src})
