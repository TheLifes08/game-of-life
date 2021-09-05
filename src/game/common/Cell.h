#ifndef GAME_COMMON_CELL_H
#define GAME_COMMON_CELL_H


namespace Game {
    namespace Common {
        struct Cell {
            enum State {
                ALIVE,
                DEAD
            };

            State state;
        };
    }
}


#endif // GAME_COMMON_CELL_H
