cmake_minimum_required(VERSION 2.8)

# set app name
set(PROJECT_NAME imgproc)
set(PROJECT_NAME_LIB ${PROJECT_NAME})
set(PROJECT_NAME_GUI g${PROJECT_NAME}app)
set(PROJECT_NAME_NOGUI ${PROJECT_NAME}app)

project(${PROJECT_NAME})

#set c++14
set(CMAKE_CXX_STANDARD 14)          # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) # ...is required...
set(CMAKE_CXX_EXTENSIONS OFF)       # ...without compiler extensions like gnu++14

#Set debug profile, also maximum level of optimalization O3
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_COMPILER_IS_GNUCC)
    # set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
    set(CMAKE_C_FLAGS_DEBUG "-Wall -O3")
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
    # set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")
    add_definitions(-Wall -Wextra -Wpedantic -g3 -gdwarf-4)
endif()

enable_language(CXX)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE TRUE)


#-------------------
# Main
#-------------------

# set headers (put all your .hpp files here)
set(HEADERS
    include/img/Image.hpp
    include/img/ImageCV.hpp
    include/img/Histogram.hpp
    include/img/utils.hpp
    include/img/utils/BasicUtils.hpp
    include/img/utils/GeometricUtils.hpp
    include/img/utils/NoiseRemovalUtils.hpp
    include/img/utils/ErrorMeasureUtils.hpp
    include/img/utils/CharacteristicUtils.hpp
    include/img/utils/QualityImprovementUtils.hpp
    include/img/utils/LinearFiltrationUtils.hpp
    include/img/utils/NonLinearFiltrationUtils.hpp
    include/gui/SimpleGui.hpp
    include/gui/SimpleGuiCV.hpp
    include/Controller.hpp
    include/GuiController.hpp
    )

# set sources (put all your .cpp files here)
set(SOURCES
    src/img/Image.cpp
    src/img/ImageCV.cpp
    src/img/Histogram.cpp
    src/img/utils/BasicUtils.cpp
    src/img/utils/GeometricUtils.cpp
    src/img/utils/NoiseRemovalUtils.cpp
    src/img/utils/ErrorMeasureUtils.cpp
    src/img/utils/CharacteristicUtils.cpp
    src/img/utils/QualityImprovementUtils.cpp
    src/img/utils/LinearFiltrationUtils.cpp
    src/img/utils/NonLinearFiltrationUtils.cpp
    src/gui/SimpleGui.cpp
    src/gui/SimpleGuiCV.cpp
    src/Controller.cpp
    src/GuiController.cpp
    )

# request opencv library
if(NOT WIN32)
    find_package(OpenCV REQUIRED)
else()
    # Olek's custom settings
    set(OPENCV_ROOT "D:/OpenCV")
    set(OpenCV_INCLUDE_DIR "${OPENCV_ROOT}/opencv/build/include")
    set(OpenCV_LIBRARY_DIR"${OPENCV_ROOT}/opencv/build/x64/vc14")
    set(OpenCV_LIBS "${OPENCV_ROOT}/opencv/build/x64/vc14/lib/opencv_world310d.lib")
    include_directories(${OpenCV_INCLUDE_DIR})
endif()

# set output bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# specify headers directory
include_directories(${PROJECT_SOURCE_DIR}/include)
# compile library
add_library(${PROJECT_NAME_LIB} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME_LIB} ${OpenCV_LIBS})

# create executable
add_executable(${PROJECT_NAME_GUI} src/main_gui.cpp)
add_executable(${PROJECT_NAME_NOGUI} src/main_nogui.cpp)
# link libs
target_link_libraries(${PROJECT_NAME_GUI} ${PROJECT_NAME_LIB})
target_link_libraries(${PROJECT_NAME_NOGUI} ${PROJECT_NAME_LIB})


#-------------------
# Test
#-------------------

if(NOT WIN32)

find_package(Threads REQUIRED)

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/include
    )

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_TEST_NAME}
    ${PROJECT_SOURCE_DIR}/external/lib/libgtest.a
    ${PROJECT_SOURCE_DIR}/external/lib/libgmock.a
    ${PROJECT_SOURCE_DIR}/external/lib/libgmock_main.a
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROJECT_NAME_LIB}
)

add_test(test1 ${PROJECT_TEST_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

endif()
