//
// Created by 陳世昂 on 2024/4/29.
//

#ifndef FUCK_PTSD_2024_4_29_UGAMEELEMENT_H
#define FUCK_PTSD_2024_4_29_UGAMEELEMENT_H

#include "Core/Drawable.hpp"
#include "Util/GameObject.hpp"

namespace Util {

class GameElement : public Util::GameObject {
public:
    virtual ~GameElement() = default;

private:
    void ResetPosition();

    std::string m_ImagePath;

    /* ----- Setter and Getter ----- */
public:
    std::shared_ptr<Core::Drawable> GetDrawable() { return m_Drawable; }

    virtual void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
    }

    void SetScale(const glm::vec2& Ratio) { m_Transform.scale = Ratio; }

    // return Image's Position
    [[nodiscard]]
    const glm::vec2& GetPosition() const {
        return m_Transform.translation;
    }

    // Is visible
    [[nodiscard]]
    bool GetVisibility() const {
        return m_Visible;
    }

    void ClearChildren() { m_Children.clear(); }
};

}  // namespace Util

#endif  // FUCK_PTSD_2024_4_29_UGAMEELEMENT_H
