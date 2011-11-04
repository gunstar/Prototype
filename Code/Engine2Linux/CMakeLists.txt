file(GLOB_RECURSE EngineAdapterSrc *.cpp *.h)

add_library(EngineAdapter STATIC ${EngineAdapterSrc})
