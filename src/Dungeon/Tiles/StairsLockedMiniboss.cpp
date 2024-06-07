#include "Dungeon/Tiles/StairsLockedMiniboss.h"

#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include "Tiles/GeneralFloor.h"
#include "ToolBoxs.h"

namespace Dungeon {
namespace Tiles {
StairsLockedMiniboss::StairsLockedMiniboss(
    const s_Tile& _Tile,
    const bool    generalFloor
)
    : GeneralFloor(_Tile, generalFloor) {
    m_Event.appendListener(
        EventType::UnlockStairs,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const UnlockStairsEventArgs&)>(
                [this](const Object*, const UnlockStairsEventArgs& e) {
                    if (e.GetUnlockType() == 0) {
                        m_Tile.type = 2;
                        m_Filepath = ASSETS_DIR "/level/stairs.png";
                        m_SpriteSheet = std::make_shared<Util::SpriteSheet>(
                            m_Filepath
                        );
                        m_TileSize = DUNGEON_TILESIZES.at(m_Tile.type);
                        m_ImgSize = ToolBoxs::CountImagePixel(
                            m_Filepath,
                            m_TileSize.x,
                            m_TileSize.y
                        );
                        m_SpriteSheet->SetColorMod(m_Color);
                        m_Drawable = m_SpriteSheet;
                        UpdateDrawable();
                    }
                }
            ),
            [](const Object*, const EventArgs& e) {
                return dynamic_cast<const UnlockStairsEventArgs*>(&e)
                       != nullptr;
            }
        )
    );
}
}  // namespace Tiles
}  // namespace Dungeon
