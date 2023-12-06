#-----------------------------------------------
#!                Estructura General
#?1. Author : Santiago Arellano,
#?2. Definition: Main Cmake List for the compiling of main.cpp
#?3. Directions: DO NOT TOUCH
#-----------------------------------------------


cmake_minimum_required(VERSION 3.26)
project(StickerAlbumV1)
set(PROJECT_VERSION 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_DESCRIPTION "Representacion Por Medio de OOP de un Album de Cromos")

set(CMAKE_CXX_STANDARD 23)

add_executable(StickerAlbumV1 main.cpp
        #Files For General Sticker Class
        source/Implementations/SVV1_GeneralSticker.cpp
        source/Headers/SVV1_GeneralSticker.hpp
        #Files for General Pack Class
        source/Implementations/SVV1_StickerPack.cpp
        source/Headers/SVV1_StickerPack.hpp
        #Files for General Album CLass
        source/Implementations/SVV1_Album.cpp
        source/Headers/SVV1_Album.hpp
        #Files for Utilities Functional Programming Modules
        source/Headers/SVV1_Utilities.hpp
        source/Implementations/SVV1_Utilities.cpp
)
