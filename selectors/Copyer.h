//
// Created by Matvey on 29.03.2022.
//

#ifndef DOSKA_COPYER_H
#define DOSKA_COPYER_H
#include "Selector.h"

class Copyer: public Selector {
public:
    Position first, last;
    explicit Copyer(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    bool finish() override;
    void render() override;
};


#endif //DOSKA_COPYER_H
