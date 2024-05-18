# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CowsAndBulls_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CowsAndBulls_autogen.dir/ParseCache.txt"
  "CowsAndBulls_autogen"
  )
endif()
