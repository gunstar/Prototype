file(GLOB_RECURSE GamesSrc *.cpp *.h)

add_library(Games STATIC ${GamesSrc})
