cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 2.0 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-O3 -Wall -Wextra -Werror -std=c++17 -pedantic)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

add_executable(3DViewer
        main.cc
        View/View.cc
        View/View.h
        View/View.ui
        View/Singleton.h
        Controller/Controller.h
        Model/Model.cc
        Model/Model.h
        Model/ActionFacede.cc
        Model/ActionFacede.h
        QtGifImage-master/src/3rdParty/giflib/dgif_lib.c
        QtGifImage-master/src/3rdParty/giflib/egif_lib.c
        QtGifImage-master/src/3rdParty/giflib/gif_err.c
        QtGifImage-master/src/3rdParty/giflib/gif_lib.h
        QtGifImage-master/src/3rdParty/giflib/gif_hash.c
        QtGifImage-master/src/3rdParty/giflib/gifalloc.c
        QtGifImage-master/src/3rdParty/giflib/quantize.c
        QtGifImage-master/src/gifimage/qgifglobal.h
        QtGifImage-master/src/gifimage/qgifimage.h
        QtGifImage-master/src/gifimage/qgifimage_p.h
        QtGifImage-master/src/gifimage/qgifimage.cpp
)

target_link_libraries(3DViewer PRIVATE Qt6::Widgets Qt6::OpenGLWidgets)
