//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_CAMMOVER_H
#define DOSKA_CAMMOVER_H

#include "Selector.h"

class CamMover:public Selector {
public:
    Position last;
    explicit CamMover(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    void finish() override;
    void render() override;
};


#endif //DOSKA_CAMMOVER_H
