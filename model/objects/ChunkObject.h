//
// Created by Matvey on 29.03.2022.
//

#ifndef DOSKA_CHUNKOBJECT_H
#define DOSKA_CHUNKOBJECT_H
#include "../Chunk.h"

class ChunkObject:public Object {
public:
    Chunk chunk;
    void render(Camera& cam, const Vector2& c_pos) override;
    void rotate(const Vector2& _ang) override;
    Object* lightCopy() override;
    ~ChunkObject() override;
};


#endif //DOSKA_CHUNKOBJECT_H
