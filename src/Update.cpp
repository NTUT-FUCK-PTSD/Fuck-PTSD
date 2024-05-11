//
// Created by adven on 2024/5/10.
//

#include <future>
#include <thread>
#include "App.hpp"

#include "Util/Logger.hpp"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include <Util/Input.hpp>
#include "Display/BeatHeart.h"
#include "Display/BeatIndicator.h"
#include "Dungeon/Enemy.h"
#include "Event/Event.h"
#include "Music/Player.h"
#include "Music/Tempo.h"
#include "System.h"

auto musicTime = []() {
    return static_cast<std::size_t>(Music::Player::GetMusicTime() * 1000)
           % static_cast<std::size_t>(Music::Player::GetMusicLength() * 1000);
};

void App::Update() {
    m_EventHandler.Update();

    if (Music::Tempo::IsSwitch()) {
        m_DungeonMap->TempoTrigger(Music::Tempo::GetBeatIdx());
        Display::BeatHeart::SwitchHeart(100);
        Event::SetAttackPlayer(true);
    }
    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    Game::System::Update();
    Display::BeatHeart::Update();
    Display::BeatIndicator::Update();
    Music::Tempo::Update(musicTime(), 0u, Music::Player::LoopCounter());

    m_MainCharacter->Update();
    m_Camera->Update();
}

std::shared_ptr<Dungeon::Map> App::m_DungeonMap = nullptr;
