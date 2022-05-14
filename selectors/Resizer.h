//
// Created by Matvey on 29.03.2022.
//

#ifndef DOSKA_RESIZER_H
#define DOSKA_RESIZER_H
#include "Selector.h"

#define RESIZER_SELECTING 0
#define RESIZER_ROTATING 1
#define RESIZER_MOVING 2
#define RESIZER_SCALING 3

class Object;
class Resizer:public Selector {
public:
    Position p_main, last;
    Vector2 scaling_pos;

    Object* resizing;
    IntPosition chunk_pos;
    bool isChunk;
    int active_mod;

    explicit Resizer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    bool finish() override;
    void render() override;
    void releaseObj();
    ~Resizer() override;
};

#endif //DOSKA_RESIZER_H
