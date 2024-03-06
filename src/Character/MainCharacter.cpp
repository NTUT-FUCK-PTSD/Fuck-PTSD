//
// Created by adven on 2024/3/4.
//

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
    m_Body->SetZIndex(ZIndex);
    m_Body->SetScale({3, 3});

    m_Head->SetDrawable(HeadImage);
    m_Head->SetPosition(InitPosition);
    m_Head->SetZIndex(ZIndex);
    m_Head->SetScale({3, 3});
}

std::vector<std::shared_ptr<Util::GameObject>> const
MainCharacter::Render() const {
    std::shared_ptr<Util::GameObject> test01 = m_Body;
    std::shared_ptr<Util::GameObject> test02 = m_Head;

    std::vector<std::shared_ptr<Util::GameObject>> test03 = {m_Body, m_Head};

    return test03;
};

void MainCharacter::move_player(const glm::vec2 distance) {

    const glm::vec2 body_position = m_Body->GetPosition();
    const glm::vec2 head_position = m_Head->GetPosition();

    auto new_body_position = ToolBoxs::AddVec2(body_position, distance);
    auto new_head_position = ToolBoxs::AddVec2(head_position, distance);

    m_Body->SetPosition(new_body_position);
    m_Head->SetPosition(new_head_position);
}

void MainCharacter::player_move_animation(const int current_frames,
                                          MainCharacter::Direction direction) {
    if (direction == MainCharacter::Direction::NONE) {
        return;
    }

    const int total_frame = 15;

    const int first_action_frame = 4;
    const int second_action_frame = 10;
    const int third_action_frame = 14;

    const int X_axis_move_position = 12;
    const int Y_axis_move_position = 24;

    if (m_start_move_animation_frame == 0) {
        m_start_move_animation_frame = current_frames;
    }
    else if (current_frames >= m_start_move_animation_frame + total_frame ||
             current_frames ==
                 m_start_move_animation_frame + total_frame - 60) {
        m_start_move_animation_frame = 0;
        return;
    }

    const int count_start_frame = current_frames - m_start_move_animation_frame;

    // 4
    if (count_start_frame <= first_action_frame) {
        const glm::vec2 move_distance = {-3, 0};

        move_player(move_distance);
    }

    // 6
    else if (count_start_frame <= second_action_frame) {
        const glm::vec2 move_distance = {1, 4};

        move_player(move_distance);
    }
    // 4
    else if (count_start_frame <= third_action_frame) {
        const glm::vec2 move_distance = {1, -6};

        move_player(move_distance);
    }
}
