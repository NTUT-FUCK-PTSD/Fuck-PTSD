#ifndef DAGGER_H
#define DAGGER_H

#include "Game/Graphs/Base.h"

#include "Util/Logger.hpp"

namespace Game {
namespace Graphs {
class DaggerGameObj final : public Game::Graphs::IBase {
public:
    explicit DaggerGameObj() {
      m_Transform.scale = {3, 3};
    };

    ~DaggerGameObj() override = default;

    void Update() override {
        LOG_INFO("This is Dagger weapon");
    };
};
}  // namespace Graphs
}  // namespace Game

#endif  // DAGGER_H
