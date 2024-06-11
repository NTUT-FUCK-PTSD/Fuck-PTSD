//
// Created by adven on 2024/5/12.
//

#ifndef FUCK_PTSD_DEADSCREEN_H
#define FUCK_PTSD_DEADSCREEN_H

#include "UGameElement.h"

#include <string_view>

namespace Settings {
class DeadScreen final : public Util::GameElement {
public:
    explicit DeadScreen();
    ~DeadScreen() = default;

    void SetPosition(const glm::vec2& Position) override;

    void SetVisibleRecursive(const bool visible);

private:
    void GenText();

    static constexpr std::string_view m_Context =
        "YOU DIED! PRESS R TO CONTINUE";
    // "YOU DIED! PRESS UP+DOWN TO CONTINUE";
};
}  // namespace Settings

#endif  // FUCK_PTSD_DEADSCREEN_H
