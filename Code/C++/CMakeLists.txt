file(GLOB_RECURSE CppSrc *.cpp *.h)

add_library(Cpp STATIC ${CppSrc})
