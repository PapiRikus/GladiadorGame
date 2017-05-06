cmake_minimum_required(VERSION 3.6)
project(Pruebas)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Map.cpp Map.h Matrix.h Gladiator.cpp Gladiator.h Sprite.cpp Sprite.h Entity.cpp Entity.h Tower.cpp Tower.h Tiled.cpp Tiled.h)
add_executable(Pruebas ${SOURCE_FILES})

INCLUDE_DIRECTORIES( allegro/5.0.11/include )

LINK_DIRECTORIES( allegro/5.0.11/lib )


TARGET_LINK_LIBRARIES(Pruebas  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)