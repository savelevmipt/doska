//
// Created by Matvey on 12.03.2022.
//

#ifndef DOSKA_CHUNK_H
#define DOSKA_CHUNK_H
#include <vector>
#include "Line.h"
#include "Object.h"
class Chunk {
public:
    std::vector<Line> lines;
    std::vector<Object*> objects;
};
Chunk* Chunk_constructor();
void Chunk_destructor(Chunk* chunk);
#endif //DOSKA_CHUNK_H
