//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_CURVEDRAWER_H
#define DOSKA_CURVEDRAWER_H

#include "Selector.h"

class CurveDrawer:public Selector {
public:
    Position last;
    explicit CurveDrawer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    void finish() override;
    void render() override;
};


#endif //DOSKA_CURVEDRAWER_H
