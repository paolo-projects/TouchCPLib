cmake_minimum_required(VERSION 3.0)

project(TouchCPLib VERSION 1.0.0 DESCRIPTION "Touch based, desktop-free, SDL based, embedded-device-oriented GUI library")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    src/Application.cpp
    src/Button.cpp
    src/GraphicsScene.cpp
    src/ImageButton.cpp
    src/MainThreadTaskRunner.cpp
    src/SceneManager.cpp
    src/SineWaveAnimation.cpp
    src/Text.cpp
    src/TouchEventDispatcher.cpp
    src/TouchInput.cpp
    src/WavefunctionAnimation.cpp
    src/Window.cpp
    src/WorkerThread.cpp
    src/XYPlot.cpp
    )

set(LIB_PUBLIC_INCLUDE_DIR include/TouchCP)

add_library(TouchCPLib SHARED ${SRC_FILES})

set_target_properties(TouchCPLib PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(TouchCPLib PUBLIC include)
target_link_libraries(TouchCPLib SDL2 ts SDL2_ttf SDL2_image)

install(
    TARGETS TouchCPLib 
    LIBRARY DESTINATION lib
    )
install(
    DIRECTORY ${LIB_PUBLIC_INCLUDE_DIR} DESTINATION include
    )