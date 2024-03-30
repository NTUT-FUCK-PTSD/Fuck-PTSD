//
// Created by adven on 2024/3/4.
//

#include "Player.h"

Player::Player()
    : Animation({0, 0}) {}

Player::Player(const std::string &headImagePath,
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

void Player::SetBodyImage(const std::string &path) {
    BodySize = ToolBoxs::CountImagePixel(path, 4, 10);
    BodyImage = std::make_shared<SpriteSheet>(
        path, BodySize, std::vector<std::size_t>{0, 1, 2, 3}, true, 100, true,
        100);
    m_Body->SetDrawable(BodyImage);
    m_Body->SetPosition(m_Position);
    m_Body->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
}

void Player::SetHeadImage(const std::string &path) {
    HeadSize = ToolBoxs::CountImagePixel(path, 4, 2);
    HeadImage = std::make_shared<SpriteSheet>(
        path, HeadSize, std::vector<std::size_t>{0, 1, 2, 3}, true, 100, true,
        100);
    m_Head->SetDrawable(HeadImage);
    m_Head->SetPosition(m_Position);
    m_Head->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
}

void Player::SetHeadImage(std::shared_ptr<SpriteSheet> image) {
    m_Head->SetDrawable(image);
    m_Head->SetPosition(m_Position);
    m_Head->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
}

void Player::SetBodyImage(std::shared_ptr<SpriteSheet> image) {
    m_Body->SetDrawable(image);
    m_Body->SetPosition(m_Position);
    m_Body->SetScale({Dungeon::DUNGEON_SCALE, Dungeon::DUNGEON_SCALE});
}

std::shared_ptr<GameElement> Player::GetGameElement() {
    m_Player->AddChild(m_Body);
    m_Player->AddChild(m_Head);

    m_Player->SetVisible(false);
    return m_Player;
}

glm::vec2 Player::GetGamePosition() {
    return m_GamePosition;
}

void Player::SetGamePosition(const glm::vec2 &gamePosition) {
    m_GamePosition = gamePosition;
    m_Position = ToolBoxs::GamePostoPos(gamePosition);
    m_Body->SetPosition(m_Position);
    m_Head->SetPosition(m_Position);
}

void Player::SetFaceTo(Direction direction) {
    if (direction != RIGHT && direction != LEFT) {
        LOG_WARN("Player::SetFaceTo: Invalid direction");
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

void Player::Update() {
    UpdateAnimation(true);
    if (m_IsAnimating || m_AnimationPosition == m_AnimationDestination) {
        m_GamePosition = ToolBoxs::PosToGamePos(m_AnimationDestination);
        m_Position = m_AnimationPosition;
    }
    SetZIndex(m_AnimationZIndex);
    SetPosition(m_Position);
}

void Player::SetPosition(const glm::vec2 &position) {
    m_Position = position;
    m_Body->SetPosition(m_Position);
    m_Head->SetPosition(m_Position);
}

void Player::SetZIndex(float index) {
    m_ZIndex = index;
    m_Body->SetZIndex(index);
    m_Head->SetZIndex(index + float(0.25));
}
