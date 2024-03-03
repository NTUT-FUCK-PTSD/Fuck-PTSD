#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include "SpriteSheet.hpp"
#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetAnimation(glm::vec2 size, const std::vector<std::size_t> &frames, bool play,
                      std::size_t interval, bool looping, std::size_t cooldown) {

        std::shared_ptr<SpriteSheet> m_Animation = std::make_shared<SpriteSheet>(GetImagePath(), size, frames, play, interval, looping, cooldown);

        this->SetDrawable(m_Animation);
    }

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Character>& other) const {
        if (    m_Transform.translation.x + GetScaledSize().x/2 >= other->m_Transform.translation.x - other->GetScaledSize().x/2 &&
                m_Transform.translation.x - GetScaledSize().x/2 <= other->m_Transform.translation.x + other->GetScaledSize().x/2 &&
                m_Transform.translation.y + GetScaledSize().y/2 >= other->m_Transform.translation.y - other->GetScaledSize().y/2 &&
                m_Transform.translation.y - GetScaledSize().y/2 <= other->m_Transform.translation.y + other->GetScaledSize().y/2)
            return true;
        else
            return false;
    }

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.
private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
//    std::shared_ptr<SpriteSheet> m_Animation;
};


#endif //CHARACTER_HPP
