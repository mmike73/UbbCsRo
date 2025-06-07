# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Practic_OOP_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Practic_OOP_autogen.dir/ParseCache.txt"
  "Practic_OOP_autogen"
  )
endif()
