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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE TRUE)


#-------------------
# Main
#-------------------

# set headers (put all your .hpp files here)
set(HEADERS
    ./include/core/Image.hpp
    ./include/core/Histogram.hpp
    ./include/core/utils/BasicUtils.hpp
    ./include/core/utils/GeometricUtils.hpp
    ./include/core/utils/NoiseRemovalUtils.hpp
    ./include/core/utils/ErrorMeasureUtils.hpp
    ./include/core/utils/CharacteristicUtils.hpp
    ./include/core/utils/QualityImprovementUtils.hpp
    ./include/core/utils/LinearFiltrationUtils.hpp
    ./include/core/utils/NonLinearFiltrationUtils.hpp
    ./include/core/core.hpp
    ./include/opencv/OpenCVImageHelper.hpp
    ./include/opencv/OpenCVWindows.hpp
    ./include/cli/Controller.hpp
    ./include/cli/GuiController.hpp
)

# set sources (put all your .cpp files here)
set(SOURCES
    ./src/core/Image.cpp
    ./src/core/Histogram.cpp
    ./src/core/utils/BasicUtils.cpp
    ./src/core/utils/GeometricUtils.cpp
    ./src/core/utils/NoiseRemovalUtils.cpp
    ./src/core/utils/ErrorMeasureUtils.cpp
    ./src/core/utils/CharacteristicUtils.cpp
    ./src/core/utils/QualityImprovementUtils.cpp
    ./src/core/utils/LinearFiltrationUtils.cpp
    ./src/core/utils/NonLinearFiltrationUtils.cpp
    ./src/opencv/OpenCVImageHelper.cpp
    ./src/opencv/OpenCVWindows.cpp
    ./src/cli/Controller.cpp
    ./src/cli/GuiController.cpp
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
add_executable(${PROJECT_NAME_NOGUI} ./src/cli/main_nogui.cpp)
add_executable(${PROJECT_NAME_GUI} ./src/cli/main_gui.cpp)
# link libs
target_link_libraries(${PROJECT_NAME_NOGUI} ${PROJECT_NAME_LIB})
target_link_libraries(${PROJECT_NAME_GUI} ${PROJECT_NAME_LIB})


#-------------------
# Test
#-------------------

if(MSVC)
    if(NOT BOOST_ROOT)
        set(BOOST_ROOT "C:/local/boost_1_60_0")
    endif()
    set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
    set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib64-msvc-14.0")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)

    if(NOT EXISTS ${Boost_LIBRARY_DIR})
        message(WARNING "Boost library requires manual installation in Windows")
        message("1) Browse: https://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/")
        message("2) Download: boost_1_60_0-msvc-14.0-32.exe")
        message("3) Install into default directory: C:\\local")
        message("")
        message(FATAL_ERROR "Boost libraries not found at ${Boost_LIBRARY_DIR}")
    endif()

    find_package(Boost COMPONENTS unit_test_framework system filesystem REQUIRED)

    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})

else()
    find_package(Boost COMPONENTS unit_test_framework system filesystem REQUIRED)
endif()

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

set(TEST_SOURCES
    ./test/master.cpp
    ./test/core/ImageTest.cpp
    ./test/opencv/OpenCVImageHelperTest.cpp
    ./include/test/ImageFixture.hpp
    ./test/ImageFixture.cpp
    ./test/core/utils/BasicUtilsTest.cpp
    ./test/core/utils/GeometricUtilsTest.cpp
    ./test/core/utils/NoiseRemovalUtilsTest.cpp
)

add_executable(${PROJECT_TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_TEST_NAME}
    ${PROJECT_NAME_LIB}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
    ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

enable_testing()
add_test(${PROJECT_TEST_NAME}s ${PROJECT_TEST_NAME})

