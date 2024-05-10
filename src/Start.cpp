//
// Created by adven on 2024/5/10.
//

#include "App.hpp"

#include "Util/Logger.hpp"
#include "eventpp/utilities/argumentadapter.h"
#include "eventpp/utilities/conditionalfunctor.h"

#include <Util/Input.hpp>
#include "Display/BeatHeart.h"
#include "Display/BeatIndicator.h"
#include "Dungeon/Enemy.h"
#include "Dungeon/MapHandler.h"
#include "Event/Event.h"
#include "HPIS.h"
#include "Helper.hpp"
#include "Music/Player.h"
#include "Music/Tempo.h"
#include "System.h"
#include "Systems/HEIS.h"

void App::Start() {
    LOG_TRACE("Start");
    if (m_FirstTime) {
        m_FirstTime = false;
        // create background
        m_Background = std::make_shared<Background>();
        m_Camera->AddChild(m_Background->GetGameElement());

        // play main background music
        // m_MusicSystem->playMusic(ASSETS_DIR "/music/intro_onlyMusic.ogg",
        // true);
        Music::Player::Init();
        Music::Player::PlayMusic(
            ASSETS_DIR "/music/intro_onlyMusic.ogg",
            true,
            0.5f,
            1.0f
        );

        //    m_MusicSystem->skipToTargetTime(118.2f);
    }

    // Wait any key click
    if (ToolBoxs::IsAnyKeyPress()) {
        m_IsMainMenu = false;
    }

    // m_MusicSystem->Update();
    m_Camera->Update();

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_IsMainMenu) {
        return;
    }
    // play lobby music
    Music::Player::StopMusic();
    Music::Player::PlayMusic(ASSETS_DIR "/music/lobby.ogg", true);
    Music::Player::SetVolume(0.1f);

    Music::Tempo::ReadTempoFile(ASSETS_DIR "/music/lobby.txt");

    // play zone1 leve1
    // m_MusicSystem->playMusic(ASSETS_DIR "/music/zone1_1.ogg", true);
    // m_MusicSystem->readTempoFile(ASSETS_DIR "/music/zone1_1.txt");

    // remove background
    m_Camera->RemoveChild(m_Background->GetGameElement());
    m_Background.reset();

    // create Player
    m_MainCharacter = std::make_shared<Player>();
    m_MainCharacter->SetHeadImage(ASSETS_DIR "/entities/player1_heads.png");
    m_MainCharacter->SetBodyImage(ASSETS_DIR "/entities/player1_armor_body.png"
    );
    Event::EventQueue.appendListener(
        EventType::AttackPlayer,
        eventpp::conditionalFunctor(
            eventpp::argumentAdapter<
                void(const Object*, const AttackPlayerEventArgs&)>(
                [this](const Object*, const AttackPlayerEventArgs& e) {
                    if (Event::GetAttackPlayer()) {
                        m_MainCharacter->lostHP(e.GetDamage());
                    }
                }
            ),
            // This lambda is the condition. We use dynamic_cast to check if
            // the event is desired. This is for demonstration purpose, in
            // production you may use a better way than dynamic_cast.
            [](const Object*, const EventArgs& e) {
                return dynamic_cast<const AttackPlayerEventArgs*>(&e)
                       != nullptr;
            }
        )
    );
    Event::EventQueue.appendListener(
        EventType::ResetMap,
        [this](const Object*, const EventArgs&) {
            m_MainCharacter->SetGamePosition({0, 0});
        }
    );
    m_Camera->AddChild(m_MainCharacter->GetGameElement());
    m_Camera->AddUIChild(m_MainCharacter->GetWindowElement());

    // Test the Dungeon::Map
    m_DungeonMap = std::make_shared<Dungeon::Map>(
        m_Camera,
        ASSETS_DIR "/dungeon/MY DUNGEON.xml",
        1
    );

    m_DungeonMap->SetDrawable(std::make_shared<Dungeon::MapHandler>(m_DungeonMap
    ));
    m_Camera->AddChild(m_DungeonMap);

    Display::BeatHeart::Init();
    m_Camera->AddUIChild(Display::BeatHeart::GetGameElement());

    Display::BeatIndicator::Init();
    m_Camera->AddUIChild(Display::BeatIndicator::GetGameElement());

    // helper
    Settings::Helper::Init(m_DungeonMap.get());

    // add tools throw system
    Game::System::Init(m_DungeonMap.get());
    Game::Systems::HPIS::Init(m_MainCharacter.get());
    Game::Systems::HEIS::Init(m_DungeonMap.get());

    // Music::Player::PauseMusic(true);
    // Music::Player::PauseMusic(false);
    // Music::Tempo::Pause(false);
    // Display::BeatIndicator::Pause(false);
    // Display::BeatHeart::Pause(false);

    BeforeUpdate();

    m_CurrentState = State::UPDATE;
}

std::map<Util::Keycode, Player::Direction> App::m_MapTableCodeDire = {
  {Util::Keycode::W, Player::Direction::UP},
  {Util::Keycode::D, Player::Direction::RIGHT},
  {Util::Keycode::S, Player::Direction::DOWN},
  {Util::Keycode::A, Player::Direction::LEFT}};

std::shared_ptr<Player> App::m_MainCharacter = nullptr;
bool                    App::m_ThrowMode = false;

glm::vec2 App::m_AniPlayerDestination = {0, 0};
glm::vec2 App::m_AniCameraDestination = {0, 0};

Player::Direction       App::m_PlayerMoveDirect = Player::Direction::NONE;
std::shared_ptr<Camera> App::m_Camera = std::make_shared<Camera>();
