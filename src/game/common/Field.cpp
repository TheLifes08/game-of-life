#include "Field.h"
#include <stdexcept>

Game::Common::Field::FieldRow::FieldRow(size_t size) {
    m_row.resize(size, {Cell::State::DEAD});
}

Game::Common::Field::Field(const Game::Common::Size& size): m_size(size) {
    m_rows.resize(size.y, FieldRow(size.x));
}

Game::Common::Cell &Game::Common::Field::get(Game::Common::Index index) {
    if (index.x < 0) index.x += m_size.x;
    if (index.y < 0) index.y += m_size.y;

    if (index.y >= m_size.y) {
        index.y %= m_size.y;
    }

    if (index.x >= m_size.x) {
        index.x %= m_size.x;
    }

    return m_rows[index.y].m_row[index.x];
}

Game::Common::Size Game::Common::Field::size() {
    return m_size;
}
