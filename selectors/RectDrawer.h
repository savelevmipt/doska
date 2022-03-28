//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_RECTDRAWER_H
#define DOSKA_RECTDRAWER_H

#include "Selector.h"
#include "../model/Square.h"

class RectDrawer:public Selector {
public:
    Position first, last;
    Square* square;
    explicit RectDrawer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    bool finish() override;
    void render() override;
};


#endif //DOSKA_RECTDRAWER_H
