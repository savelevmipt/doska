//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_RECTDRAWER_H
#define DOSKA_RECTDRAWER_H

#include "Selector.h"

class RectDrawer:public Selector {
public:
    Position first, last;
    explicit RectDrawer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    void finish() override;
    void render() override;
};


#endif //DOSKA_RECTDRAWER_H
