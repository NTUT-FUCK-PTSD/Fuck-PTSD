#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "SpriteSheet.hpp"
#include "Util/GameObject.hpp"
#include <string>

class Character : public Util::GameObject {
public:
    explicit Character(const std::string &ImagePath);

    Character(const Character &) = delete;

    Character(Character &&) = delete;

    Character &operator=(const Character &) = delete;

    Character &operator=(Character &&) = delete;

    // return Image Path
    [[nodiscard]] const std::string &GetImagePath() const {
        return m_ImagePath;
    }

    // return Image's Position
    [[nodiscard]] const glm::vec2 &GetPosition() const {
        return m_Transform.translation;
    }

    // Is visible
    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position) {
        m_Transform.translation = Position;
    }

    void SetScale(const glm::vec2 &Ratio) { m_Transform.scale = Ratio; }

    // if animateion, then it will run.
    void SetAnimation(glm::vec2 size, const std::vector<std::size_t> &frames,
                      bool play, std::size_t interval, bool looping,
                      std::size_t cooldown);

    void SetPlay();

    void SetPause();

    [[nodiscard]] bool
    IfCollides(const std::shared_ptr<Character> &other) const {
        if (m_Transform.translation.x + GetScaledSize().x / 2 >=
                other->m_Transform.translation.x -
                    other->GetScaledSize().x / 2 &&
            m_Transform.translation.x - GetScaledSize().x / 2 <=
                other->m_Transform.translation.x +
                    other->GetScaledSize().x / 2 &&
            m_Transform.translation.y + GetScaledSize().y / 2 >=
                other->m_Transform.translation.y -
                    other->GetScaledSize().y / 2 &&
            m_Transform.translation.y - GetScaledSize().y / 2 <=
                other->m_Transform.translation.y + other->GetScaledSize().y / 2)
            return true;
        else
            return false;
    }

    // Giraffe Adventure.
private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
    std::shared_ptr<SpriteSheet> m_Animation;

    //    uint8_t ImageWidthNumber = 0;
    //    uint8_t ImageHeightNumber = 0;
};

#endif // CHARACTER_HPP
