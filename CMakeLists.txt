cmake_minimum_required(VERSION 2.8)
project(OpenJpeg2KTool)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 14)


FIND_PACKAGE( OpenCV )
FIND_PACKAGE( OpenJPEG )
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${OPENJPEG_INCLUDE_DIRS})



add_library(OpenJpeg2KTool

        OpenJpeg2KTool.cpp
        )

add_executable(OpenJpeg2KToolTest
        main.cpp
        )
TARGET_LINK_LIBRARIES(OpenJpeg2KTool ${OpenCV_LIBS} ${OPENJPEG_LIBRARIES})
TARGET_LINK_LIBRARIES(OpenJpeg2KToolTest OpenJpeg2KTool)