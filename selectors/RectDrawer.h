//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_RECTDRAWER_H
#define DOSKA_RECTDRAWER_H

#include "Selector.h"
#include "../model/objects/Square.h"


class RectDrawer:public Selector {
public:
    Position first, last;
    Vector2 def_angle;
    Square* square;
    explicit RectDrawer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    bool finish() override;
    void render() override;
    std::string to_string() const;

};


#endif //DOSKA_RECTDRAWER_H
