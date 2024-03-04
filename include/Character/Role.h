//
// Created by adven on 2024/3/4.
//

#ifndef I_LOVE_PTSD_ROLE_H
#define I_LOVE_PTSD_ROLE_H

#include "Util/GameObject.hpp"
#include "Core/Drawable.hpp"

class Role final : public Util::GameObject {
public:
    explicit Role();


private:
    void ResetPosition();

    std::string m_ImagePath;

public:
    void SetDisplay(std::shared_ptr<Core::Drawable> &m_Drawable);

    // return Image Path
    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    // return Image's Position
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    // Is visible
    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetPosition(const glm::vec2 &Position) {
        m_Transform.translation = Position;
    }

    void SetScale(const glm::vec2& Ratio) { m_Transform.scale = Ratio; }

};

#endif // I_LOVE_PTSD_ROLE_H
