# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Observer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Observer_autogen.dir/ParseCache.txt"
  "Observer_autogen"
  )
endif()
