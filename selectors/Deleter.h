//
// Created by Matvey on 26.03.2022.
//

#ifndef DOSKA_DELETER_H
#define DOSKA_DELETER_H
#include "Selector.h"

class Deleter:public Selector {
public:
    Position first, last;
    explicit Deleter(Camera& _cam);

    void begin(const Position& start) override;
    void update(const Position& curr) override;
    bool finish() override;
    void render() override;
};


#endif //DOSKA_DELETER_H
