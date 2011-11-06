file(GLOB_RECURSE Src *.cpp *.h)

add_library(TestGame STATIC ${Src})
