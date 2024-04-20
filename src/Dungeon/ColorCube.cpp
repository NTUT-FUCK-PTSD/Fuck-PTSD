#include "Dungeon/ColorCube.h"

namespace Dungeon {
ColorCube::ColorCube(CubeColor color)
    : m_Color(color) {
    SetColor(color);
    m_Available = true;
}

void ColorCube::Draw(const Core::Matrices &data) {
    if (m_Available == true) {
        m_Image->Draw(data);
    }
}

glm::vec2 ColorCube::GetSize() const {
    return (m_Available == true) ? m_Image->GetSize() : glm::vec2(0.0f);
}

bool ColorCube::GetAvailable() const {
    return m_Available;
}

void ColorCube::SetColor(CubeColor color) {
    m_Image.reset();
    m_Color = color;
    switch (color) {
    case CubeColor::black:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_black.png");
        break;
    case CubeColor::blood:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_blood.png");
        break;
    case CubeColor::blue:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_blue.png");
        break;
    case CubeColor::confuse:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_confuse.png");
        break;
    case CubeColor::crystal:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_crystal.png");
        break;
    case CubeColor::darkpurple:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_darkpurple.png");
        break;
    case CubeColor::dirt:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_dirt.png");
        break;
    case CubeColor::gray:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_gray.png");
        break;
    case CubeColor::green:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_green.png");
        break;
    case CubeColor::heal:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_heal.png");
        break;
    case CubeColor::metrognome:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_metrognome.png");
        break;
    case CubeColor::orange:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_orange.png");
        break;
    case CubeColor::purple:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_purple.png");
        break;
    case CubeColor::red:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_red.png");
        break;
    case CubeColor::spore:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_spore.png");
        break;
    case CubeColor::stone:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_stone.png");
        break;
    case CubeColor::wall:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_wall.png");
        break;
    case CubeColor::water:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_water.png");
        break;
    case CubeColor::white:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_white.png");
        break;
    case CubeColor::yellow:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_yellow.png");
        break;
    case CubeColor::yellowgreen:
        m_Image = std::make_shared<Util::Image>(
            ASSETS_DIR "/particles/TEMP_particle_yellow.png");
        break;
    }
    m_Available = true;
}
} // namespace Dungeon
