#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include "Dungeon/Elements.h"
#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"

namespace Dungeon {

class Tile : public Util::GameObject {
public:
    explicit Tile(const s_Tile &u_Tile);
    virtual ~Tile() override = default;

    void SetIndex(std::size_t index);
    void SetCloseDisplayB24(bool closeDisplayb24);
    void SetRotation(float rotation);
    std::size_t GetIndex();
    s_Tile GetTile();
    virtual bool IsWall();
    virtual bool IsDoor();

    void UpdateDrawable();

protected:
    glm::vec2 m_TileSize;
    glm::vec2 m_ImgSize;
    int8_t m_MagicNumber = 0;

private:
    s_Tile m_Tile;
    std::string m_Filepath;
    std::shared_ptr<Util::SpriteSheet> m_SpriteSheet;
    std::size_t m_Index = 0;
    bool m_CloseDisplayb24 = false;
};
} // namespace Dungeon

#endif // TILE_HPP
