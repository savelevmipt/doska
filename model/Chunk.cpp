//
// Created by Matvey on 12.03.2022.
//

#include "Chunk.h"
Chunk* Chunk_constructor(){
    return new Chunk();
}
void Chunk_destructor(Chunk* chunk){
    delete chunk;
}