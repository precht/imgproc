cmake_minimum_required(VERSION 2.8)

# set app name
set(APP_NAME imgproc)
set(APP_NAME_LIB ${APP_NAME})
set(APP_NAME_GUI g${APP_NAME}app)
set(APP_NAME_NOGUI ${APP_NAME}app)

project(${APP_NAME})

#set c++14
set(CMAKE_CXX_STANDARD 14)          # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) # ...is required...
set(CMAKE_CXX_EXTENSIONS OFF)       # ...without compiler extensions like gnu++14

# set headers (put all your .hpp files here)
set(HEADERS
    include/img/Image.hpp
    include/img/ImageCV.hpp
    include/img/utils/utils.hpp
    include/img/utils/BasicUtils.hpp
    include/img/utils/GeometricUtils.hpp
    include/img/utils/NoiseRemovalUtils.hpp
    include/img/utils/ErrorMeasureUtils.hpp
    include/gui/SimpleGui.hpp
    include/gui/SimpleGuiCV.hpp
    include/Controller.hpp
    include/GuiController.hpp
    )

# set sources (put all your .cpp files here)
set(SOURCES
    src/img/Image.cpp
    src/img/ImageCV.cpp
    src/img/utils/BasicUtils.cpp
    src/img/utils/GeometricUtils.cpp
    src/img/utils/NoiseRemovalUtils.cpp
    src/img/utils/ErrorMeasureUtils.cpp
    src/gui/SimpleGui.cpp
    src/gui/SimpleGuiCV.cpp
    src/Controller.cpp
    src/GuiController.cpp
    )

# request opencv library
if()
find_package(OpenCV 3.1.0 REQUIRED)
else()
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
add_library(${APP_NAME_LIB} ${SOURCES} ${HEADERS})
# create executable
add_executable(${APP_NAME_GUI} src/main_gui.cpp)
add_executable(${APP_NAME_NOGUI} src/main_nogui.cpp)
# link libs
target_link_libraries(${APP_NAME_LIB} ${OpenCV_LIBS})
target_link_libraries(${APP_NAME_GUI} ${APP_NAME_LIB})
target_link_libraries(${APP_NAME_NOGUI} ${APP_NAME_LIB})

