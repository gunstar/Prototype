file(GLOB_RECURSE BootSrc *.cpp *.h)

add_library(Boot STATIC ${BootSrc})
