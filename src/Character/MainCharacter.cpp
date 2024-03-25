//
// Created by adven on 2024/3/4.
//

#include "Dungeon/Elements.h"
#include "MainCharacter.h"
#include "SpriteSheet.hpp"
#include "ToolBoxs.h"
#include "Util/Image.hpp"

MainCharacter::MainCharacter() {

    const auto HeadSize = ToolBoxs::CountImagePixel(m_HeadImagePath, 4, 2);
    const auto BodySize = ToolBoxs::CountImagePixel(m_BodyImagePath, 4, 10);

    const auto HeadImage = std::make_shared<SpriteSheet>(
        m_HeadImagePath, HeadSize, std::vector<std::size_t>{0, 1, 2, 3}, true,
        100, true, 100);

    auto BodyImage = std::make_shared<SpriteSheet>(
        m_BodyImagePath, BodySize, std::vector<std::size_t>{0, 1, 2, 3}, true,
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

void MainCharacter::SetPosition(const glm::vec2 &position) {
    m_Body->SetPosition(position);
    m_Head->SetPosition(position);
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

glm::vec2 MainCharacter::GetGamePosition() {
    return {(m_Head->GetPosition().x / (Dungeon::DUNGEON_TILE_WIDTH * 3)),
            -(m_Head->GetPosition().y / (Dungeon::DUNGEON_TILE_WIDTH * 3))};
}
