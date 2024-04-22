//
// Created by adven on 2024/3/1.
//

#ifndef FUCK_PTSD_BACKGROUND_HPP
#define FUCK_PTSD_BACKGROUND_HPP

#include <string>
#include "GameElement.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Background final {
public:
    Background();

    [[nodiscard]]
    std::shared_ptr<GameElement> GetGameElement();

private:
    std::string m_ContinueImagePath = ASSETS_DIR "/mainmenu/continue.png";
    std::string m_MainMenuImagePath = ASSETS_DIR "/mainmenu/mainmenu.png";

    std::shared_ptr<GameElement> m_Continue = std::make_shared<GameElement>();
    std::shared_ptr<GameElement> m_MainMenu = std::make_shared<GameElement>();

    std::shared_ptr<GameElement> m_Background = std::make_shared<GameElement>();

    std::string m_ImagePath;
};

#endif  // FUCK_PTSD_BACKGROUND_HPP
