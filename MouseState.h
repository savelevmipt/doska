//
// Created by Matvey on 19.03.2022.
//

#ifndef DOSKA_MOUSESTATE_H
#define DOSKA_MOUSESTATE_H
//структура для хранения текущего положения мыши, нажатых клавиш и состояния курсора ()
#define STATE_MOVE 0
#define STATE_DRAW 1
#define STATE_DELETE 2
struct MouseState{
    int x = 0, y = 0, st_x = 0, st_y = 0;
    int key_state = 0;

    bool has_last_state = false;
    bool left_pressed = false;
    unsigned left_down_time = 0;
    bool right_pressed = false;
};

#endif //DOSKA_MOUSESTATE_H
