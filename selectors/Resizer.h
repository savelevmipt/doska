//
// Created by Matvey on 29.03.2022.
//

#ifndef DOSKA_RESIZER_H
#define DOSKA_RESIZER_H
#include "Selector.h"

class Object;
class Resizer:public Selector {
public:
    Position p_main, last;

    Object* resizing;
    IntPosition chunk_pos;
    bool isChunk;
    explicit Resizer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    bool finish() override;
    void render() override;

    ~Resizer() override;
};

#endif //DOSKA_RESIZER_H
