cmake_minimum_required(VERSION 2.8)

# set app name
set(APP_NAME imgprocapp)
project(${APP_NAME})

#set c++14
set(CMAKE_CXX_STANDARD 14)          # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) # ...is required...
set(CMAKE_CXX_EXTENSIONS OFF)       # ...without compiler extensions like gnu++14

# set headers (put all your .hpp files here)
set(HEADERS
    ./include/image/Image.hpp
    ./include/image/ImageCV.hpp
    ./include/image/utils/BasicUtils.hpp
    ./include/gui/SimpleGui.hpp
    ./include/gui/SimpleGuiCV.hpp
    ./include/Controller.hpp
    ./include/GuiController.hpp

    )

# set sources (put all your .cpp files here)
set(SOURCES
    ./src/image/Image.cpp
    ./src/image/ImageCV.cpp
    ./src/image/utils/BasicUtils.cpp
    ./src/gui/SimpleGui.cpp
    ./src/gui/SimpleGuiCV.cpp
    ./src/Controller.cpp
    ./src/GuiController.cpp
    ./src/main.cpp
    )

# request opencv library
find_package(OpenCV REQUIRED)
# set output bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# specify headers directory
include_directories(${PROJECT_SOURCE_DIR}/include)
# create executable
add_executable(${APP_NAME} ${SOURCES} ${HEADERS})
# link external libs
target_link_libraries(${APP_NAME} ${OpenCV_LIBS})

