//
// Created by Matvey on 19.03.2022.
//

#ifndef DOSKA_MOUSESTATE_H
#define DOSKA_MOUSESTATE_H

//структура для хранения текущего положения мыши, нажатых клавиш и состояния курсора ()

#define STATE_MOVE 0
#define STATE_DRAW_LINE 1
#define STATE_DELETE 2
#define STATE_DRAW_RECT 3
#define STATE_COPY 4
#define STATE_RESIZE 5

#include "Deleter.h"
#include "CamMover.h"
#include "CurveDrawer.h"
#include "RectDrawer.h"
#include "Copyer.h"
#include "Resizer.h"

struct MouseState{
    int x = 0, y = 0;
    int key_state;
    bool left_pressed;

    Selector *selectors[6]{};
    explicit MouseState(Camera& cam);
    ~MouseState();
};

#endif //DOSKA_MOUSESTATE_H
