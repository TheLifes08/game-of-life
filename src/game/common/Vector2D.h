#ifndef GAME_COMMON_VECTOR_2D_H
#define GAME_COMMON_VECTOR_2D_H

#include <cstddef>

namespace Game {
    namespace Common {
        template<typename T>
        struct Vector2D {
            T x;
            T y;
        };

        using Size = Vector2D<size_t>;
        using Index = Vector2D<size_t>;
        using Position = Vector2D<long long int>;
    }
}


#endif // GAME_COMMON_VECTOR_2D_H
