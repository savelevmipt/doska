//
// Created by Matvey on 12.03.2022.
//

#ifndef DOSKA_CHUNK_H
#define DOSKA_CHUNK_H
#include <vector>
#include "Line.h"
class Chunk {
public:
    std::vector<Line> lines;
};
Chunk* Chunk_constructor();
void Chunk_destructor(Chunk* chunk);
#endif //DOSKA_CHUNK_H
