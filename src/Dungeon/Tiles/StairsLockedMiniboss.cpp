#include "Dungeon/Tiles/StairsLockedMiniboss.h"

#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include "Tiles/GeneralFloor.h"

namespace Dungeon {
namespace Tiles {
StairsLockedMiniboss::StairsLockedMiniboss(
    const s_Tile& u_Tile,
    const bool    generalFloor
)
    : GeneralFloor(u_Tile, generalFloor) {
    m_Event.appendListener(
        EventType::FloorUpdate,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const UnlockStairsEventArgs&)>(
                [this](const Object*, const UnlockStairsEventArgs& e) {
                    if (e.GetUnlockType() == 0) {
                        m_Filepath = ASSETS_DIR "/level/stairs.png";
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
