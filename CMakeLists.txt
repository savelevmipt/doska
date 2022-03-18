cmake_minimum_required(VERSION 3.21)
project(doska)

set(CMAKE_CXX_STANDARD 23)

# Объявить переменную SDL2_DIR как путь установки SDL2
set(SDL2_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20)
set(SDL2_IMAGE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5)

include_directories(${SDL2_DIR}/include)
include_directories(${SDL2_IMAGE_DIR}/include)

link_directories(${SDL2_DIR}/lib/x64)
link_directories(${SDL2_IMAGE_DIR}/lib/x64)



add_executable(doska main.cpp map/ChunkNet.cpp map/ChunkNet.h map/ChunkNode.h Chunk.cpp Chunk.h map/ChunkIterator.cpp map/ChunkIterator.h map/ChunkNode.cpp view/Camera.cpp view/Camera.h utils/Position.cpp utils/Position.h utils/Vector2.cpp utils/Vector2.h)



target_link_libraries(doska SDL2main SDL2 SDL2test SDL2_image)

