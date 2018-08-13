cmake_minimum_required (VERSION 2.8)

project (GeoPad)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

aux_source_directory (src DIR_SRCS)

add_executable (GeoPad.elf ${DIR_SRCS})

target_link_libraries (GeoPad.elf m)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

