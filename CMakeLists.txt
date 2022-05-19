cmake_minimum_required(VERSION 3.21)
project(doska)

set(CMAKE_CXX_STANDARD 23)


if (WIN32)
    set(SDL2_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20)
    set(SDL2_IMAGE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5)
    include_directories(${SDL2_DIR}/include)
    include_directories(${SDL2_IMAGE_DIR}/include)
    link_directories(${SDL2_DIR}/lib/x64)
    link_directories(${SDL2_IMAGE_DIR}/lib/x64)
elseif(APPLE)
    set(SDL2_DIR ${PROJECT_SOURCE_DIR}/lib/SDL2.framework)
    include_directories(${SDL2_DIR}/Headers)
endif ()



add_executable(doska
        main.cpp selectors/MouseState.h
        map/ChunkNet.cpp map/ChunkNet.h map/ChunkNode.h
        map/ChunkIterator.cpp map/ChunkIterator.h map/ChunkNode.cpp
        model/Chunk.cpp model/Chunk.h
        view/Camera.cpp view/Camera.h
        utils/Position.cpp utils/Position.h utils/Vector2.cpp utils/Vector2.h
        model/Doska2.cpp model/Doska2.h model/Line.h selectors/Selector.cpp selectors/Selector.h selectors/CurveDrawer.cpp selectors/CurveDrawer.h selectors/CamMover.cpp selectors/CamMover.h selectors/Deleter.cpp selectors/Deleter.h selectors/MouseState.cpp selectors/RectDrawer.cpp selectors/RectDrawer.h model/objects/Object.cpp model/objects/Object.h model/objects/Square.cpp model/objects/Square.h model/objects/ChunkObject.cpp model/objects/ChunkObject.h selectors/Copyer.cpp selectors/Copyer.h selectors/Resizer.cpp selectors/Resizer.h)


if(WIN32)
    target_link_libraries(doska SDL2main SDL2 SDL2test SDL2_image)
elseif(APPLE)
    target_link_libraries(doska ${SDL2_DIR}/SDL2)
endif()

target_link_libraries(
        ${PROJECT_NAME}
)
