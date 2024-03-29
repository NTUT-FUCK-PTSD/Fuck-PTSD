//
// Created by adven on 2024/3/4.
//

#include "MainCharacter.h"

MainCharacter::MainCharacter(const std::string &headImagePath,
                             const std::string &bodyImagePath)
    : Animation({0, 0}),
      m_HeadImagePath(headImagePath),
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
    m_Body->SetPosition(m_Position);
    m_Body->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});

    m_Head->SetDrawable(HeadImage);
    m_Head->SetPosition(m_Position);
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

void MainCharacter::Update() {
    UpdateAnimation(true);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_GamePosition = ToolBoxs::PosToGamePos(m_AnimationDestination);
        m_Position = m_AnimationPosition;
    }
    SetZIndex(m_AnimationZIndex);
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
