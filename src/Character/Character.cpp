
#include "Character/Character.hpp"
#include "SpriteSheet.hpp"
#include "Util/Image.hpp"


Character::Character(const std::string& ImagePath) {
    SetImage(ImagePath);
    this->SetScale({3, 3});

    ResetPosition();
}

void Character::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Character::SetAnimation(glm::vec2 size, const std::vector<std::size_t> &frames, bool play,
                             std::size_t interval, bool looping, std::size_t cooldown) {

    m_Animation = std::make_shared<SpriteSheet>(GetImagePath(), size, frames, play, interval, looping, cooldown);

    this->SetDrawable(m_Animation);
}

void Character::SetPlay() {
    m_Animation->Play();
}

void Character::SetPause() {
    m_Animation->Pause();
}