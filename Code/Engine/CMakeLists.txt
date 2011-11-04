include_directories("../C++")

file(GLOB_RECURSE EngineSrc *.cpp *.h)

add_library(Engine STATIC ${EngineSrc})
