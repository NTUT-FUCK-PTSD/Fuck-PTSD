//
// Created by adven on 2024/3/4.
//

#include "MainCharacter.h"

MainCharacter::MainCharacter(const std::string &headImagePath,
                             const std::string &bodyImagePath)
    : m_HeadImagePath(headImagePath),
      m_BodyImagePath(bodyImagePath) {
    HeadSize = ToolBoxs::CountImagePixel(headImagePath, 4, 2);
    BodySize = ToolBoxs::CountImagePixel(bodyImagePath, 4, 10);

    HeadImage = std::make_shared<SpriteSheet>(
        headImagePath, HeadSize, std::vector<std::size_t>{0, 1, 2, 3}, true,
        100, true, 100);

    BodyImage = std::make_shared<SpriteSheet>(
        bodyImagePath, BodySize, std::vector<std::size_t>{0, 1, 2, 3}, true,
        100, true, 100);

    m_Body->SetDrawable(BodyImage);
    m_Body->SetPosition(InitPosition);
    m_Body->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});

    m_Head->SetDrawable(HeadImage);
    m_Head->SetPosition(InitPosition);
    m_Head->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
    Update();
}

std::vector<std::shared_ptr<Util::GameObject>> const
MainCharacter::GetGameElement() const {
    std::shared_ptr<Util::GameObject> test01 = m_Body;
    std::shared_ptr<Util::GameObject> test02 = m_Head;

    std::vector<std::shared_ptr<Util::GameObject>> test03 = {m_Body, m_Head};

    return test03;
};

glm::vec2 MainCharacter::GetGamePosition() {
    return m_GamePosition;
}

void MainCharacter::SetGamePosition(const glm::vec2 &gamePosition) {
    m_GamePosition = gamePosition;
    m_Position = ToolBoxs::GamePostoPos(gamePosition);
    m_Body->SetPosition(m_Position);
    m_Head->SetPosition(m_Position);
}

void MainCharacter::SetFaceTo(Direction direction) {
    if (direction != RIGHT && direction != LEFT) {
        LOG_WARN("MainCharacter::SetFaceTo: Invalid direction");
        return;
    }
    if (direction == RIGHT) {
        m_Body->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
        m_Head->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
        return;
    }
    m_Body->SetScale({-Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
    m_Head->SetScale({-Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
}

void MainCharacter::MoveByTime(const unsigned long &duringTimeMs,
                               const glm::vec2 &destGamePosition,
                               Direction direction) {
    if (m_IsAnimating) {
        m_Position = m_AnimationDestination;
        Update();
    }
    m_AnimationStartMs = Util::Time::GetElapsedTimeMs();
    m_AnimationDuringTimeMs = duringTimeMs;
    m_AnimationDestination = ToolBoxs::GamePostoPos(destGamePosition);
    m_IsAnimating = true;
    m_AnimationDirection = direction;
}

void MainCharacter::Update() {
    if (m_IsAnimating) {
        unsigned long passTimeMs =
            Util::Time::GetElapsedTimeMs() - m_AnimationStartMs;
        if (passTimeMs > m_AnimationDuringTimeMs ||
            m_Position == m_AnimationDestination) {
            m_Position = m_AnimationDestination;
            m_GamePosition = ToolBoxs::PosToGamePos(m_Position);
            m_IsAnimating = false;
        }
        else {
            if (passTimeMs <= m_AnimationDuringTimeMs / 2.0f) {
                float ratio = (float)passTimeMs / (m_AnimationDuringTimeMs / 2);
                m_Position += m_MoveAnimation[m_AnimationDirection] * ratio;
            }
            else {
                float ratio =
                    (float)(passTimeMs + (m_AnimationDuringTimeMs / 2)) /
                    (m_AnimationDuringTimeMs / 2);
                m_Position -=
                    m_MoveAnimation[m_AnimationDirection] * (1.0f - ratio);
            }
            float ratio = (float)passTimeMs / m_AnimationDuringTimeMs;
            glm::vec2 move = m_AnimationDestination - m_Position;
            m_Position += move * ratio;
        }
    }
    SetZIndex(ToolBoxs::PosToGamePos(m_Position).y + float(0.5));
    SetPosition(m_Position);
}

void MainCharacter::SetPosition(const glm::vec2 &position) {
    m_Position = position;
    m_Body->SetPosition(m_Position);
    m_Head->SetPosition(m_Position);
}

void MainCharacter::SetZIndex(float index) {
    m_ZIndex = index;
    m_Body->SetZIndex(index);
    m_Head->SetZIndex(index + float(0.25));
}
