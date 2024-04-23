#ifndef TILE_H
#define TILE_H

#include <string>

#include "Dungeon/Elements.h"

#include "Util/GameObject.hpp"
#include "Util/SpriteSheet.hpp"

namespace Dungeon {

class Tile : public Util::GameObject {
public:
    Tile(const s_Tile& u_Tile);
    Tile(const s_Tile& u_Tile, const std::string& filepath);
    void Initialize();
    virtual ~Tile() override = default;

    void         SetIndex(std::size_t index);
    void         SetCloseDisplayB24(bool closeDisplayb24);
    void         SetRotation(float rotation);
    void         SetOverlay(bool visible);
    std::size_t  GetIndex();
    s_Tile       GetTile();
    bool         GetVisible();
    virtual bool IsWall() = 0;
    virtual bool IsDoor() = 0;

    virtual void UpdateDrawable();

    bool GetSeen() const;

protected:
    void         UpdateScale();
    virtual void UpdateTranslation();

    s_Tile      m_Tile;
    std::string m_Filepath;

    glm::vec2                          m_TileSize;
    glm::vec2                          m_ImgSize;
    int8_t                             m_MagicNumber = 0;
    std::size_t                        m_Index = 0;
    bool                               m_CloseDisplayb24 = false;
    std::size_t                        m_OffSetY = 0;
    std::shared_ptr<Util::SpriteSheet> m_SpriteSheet;

    bool m_Seen = false;
    bool m_IsOverlay = false;
};
}  // namespace Dungeon

#endif  // TILE_HPP
