PROJECT(Math)
INCLUDE(CollectSrcs)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES($ENV{BOOST_INCLUDE})

SET(Math_SUBDIRS )

GET_SRCS(Math_SRCLISTS Math_SUBDIRS)
ADD_LIBRARY(Math ${Math_SRCLISTS})

LINK_LIBRARIES(${CMAKE_BINARY_DIR}/Common)
TARGET_LINK_LIBRARIES(Math Common)

#install configure
INSTALL(TARGETS Math
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/Include/Math
    DESTINATION include/Math
    FILES_MATCHING PATTERN "*.h")

