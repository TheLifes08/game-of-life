#ifndef GAME_COMMON_FIELD_H
#define GAME_COMMON_FIELD_H

#include "Vector2D.h"
#include "Cell.h"
#include <vector>


namespace Game {
    namespace Common {
        class Field {
        public:
            explicit Field(const Size& size);

            Cell& get(Index index);
            Size size();

        private:
            struct FieldRow {
                explicit FieldRow(size_t size);
                std::vector<Cell> m_row;
            };

            Size m_size;
            std::vector<FieldRow> m_rows;
        };
    }
}


#endif //GAME_COMMON_FIELD_H
