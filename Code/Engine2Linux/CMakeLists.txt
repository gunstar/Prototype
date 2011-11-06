include_directories("../C++")
include_directories("../Engine")

file(GLOB_RECURSE EngineAdapterSrc *.cpp *.h)

add_library(EngineAdapter STATIC ${EngineAdapterSrc})
