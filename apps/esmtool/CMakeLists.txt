set(ESMTOOL
  esmtool_cmd.c
  esmtool_cmd.h
  esmtool.cpp
)
source_group(apps\\esmtool FILES ${ESMTOOL})

# Main executable
add_executable(esmtool
  ${ESMTOOL}
  ${MISC} ${MISC_HEADER}
)

target_link_libraries(esmtool
  ${Boost_LIBRARIES}
)

#if (APPLE)
#    find_library(CARBON_FRAMEWORK Carbon)
#    target_link_libraries(openmw ${CARBON_FRAMEWORK})
#endif (APPLE)
