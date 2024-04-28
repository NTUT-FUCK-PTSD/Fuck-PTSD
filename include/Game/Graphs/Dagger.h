#ifndef DAGGER_H
#define DAGGER_H

#include "Game/Graphs/Base.h"
#include "Settings/Helper.hpp"

#include "Util/Logger.hpp"

namespace Game {
namespace Graphs {
class DaggerGameObj final : public Game::Graphs::IBase {
public:
    explicit DaggerGameObj() { m_Transform.scale = {3, 3}; };

    ~DaggerGameObj() override = default;

    void Update(Dungeon::Map* dungeonMap) override {
        auto value = Settings::Helper::GamePosToMapIdx(static_cast<glm::ivec2>(
            dungeonMap->GetMapData()->GetPlayerPosition()
        ));
        if (value == MI) {
            m_Vis = false;
        }

        SetVisible(m_Vis);
    };

private:
    bool m_Vis = true;
};
}  // namespace Graphs
}  // namespace Game

#endif  // DAGGER_H
