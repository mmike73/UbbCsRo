# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/selectable_painter_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/selectable_painter_autogen.dir/ParseCache.txt"
  "selectable_painter_autogen"
  )
endif()
