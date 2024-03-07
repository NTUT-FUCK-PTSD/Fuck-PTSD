#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include "Dungeon/Elements.h"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"

namespace Dungeon {

class Tile : public Util::GameObject {
public:
    Tile(const tile &u_Tile);

    void SetIndex(std::size_t index);
    std::size_t GetIndex();

    void Update();

private:
    tile m_Tile;
    glm::vec2 m_TileSize;
    std::string m_Filepath;
    std::shared_ptr<Util::SpriteSheet> m_SpriteSheet;
    std::size_t m_Index = 0;
};
} // namespace Dungeon

#endif // TILE_HPP
