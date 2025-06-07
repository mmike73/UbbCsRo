# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/p3_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/p3_autogen.dir/ParseCache.txt"
  "p3_autogen"
  )
endif()
