file(GLOB_RECURSE Engine2Src *.cpp *.h)

add_library(EngineAdapter STATIC ${Engine2Src})
