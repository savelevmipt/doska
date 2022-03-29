//
// Created by Matvey on 26.03.2022.
//
#include "MouseState.h"

MouseState::MouseState(Camera& cam):key_state(STATE_MOVE), left_pressed(false) {
    selectors[STATE_MOVE] = new CamMover(cam);
    selectors[STATE_DRAW_LINE] = new CurveDrawer(cam);
    selectors[STATE_DELETE] = new Deleter(cam);
    selectors[STATE_DRAW_RECT] = new RectDrawer(cam);
    selectors[STATE_COPY] = new Copyer(cam);
    selectors[STATE_RESIZE] = new Resizer(cam);
}
MouseState::~MouseState() {
    for(auto & selector : selectors)
        delete selector;
}