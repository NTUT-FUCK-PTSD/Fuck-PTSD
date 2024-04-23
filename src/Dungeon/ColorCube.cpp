#include "Dungeon/ColorCube.h"

#include "Util/Logger.hpp"

namespace Dungeon {
ColorCube::ColorCube(CubeColor color)
    : m_Color(color) {
    if (m_ColorMapInitialized == false) {
        InitColorMap();
    }
    SetColor(color);
    m_Available = true;
}

ColorCube::ColorCube() {
    if (m_ColorMapInitialized == false) {
        InitColorMap();
    }
}

void ColorCube::Draw(const Core::Matrices& data) {
    if (m_ColorMap.find(m_Color) != m_ColorMap.end()) {
        m_Image->Draw(data);
    }
}

glm::vec2 ColorCube::GetSize() const {
    if (m_ColorMap.find(m_Color) != m_ColorMap.end()) {
        return m_Image->GetSize();
    }
    return glm::vec2(0.0f);
}

bool ColorCube::GetAvailable() const {
    return m_Available;
}

void ColorCube::SetColor(CubeColor color) {
    m_Color = color;
    m_Image = m_ColorMap[m_Color];
    m_Available = true;
}
Dungeon::CubeColor ColorCube::GetColor() const {
    return m_Color;
}

void ColorCube::InitColorMap() {
    m_ColorMap[CubeColor::black] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_black.png"
    );
    m_ColorMap[CubeColor::blood] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_blood.png"
    );
    m_ColorMap[CubeColor::blue] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_blue.png"
    );
    m_ColorMap[CubeColor::confuse] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_confuse.png"
    );
    m_ColorMap[CubeColor::crystal] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_crystal.png"
    );
    m_ColorMap[CubeColor::darkpurple] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_darkpurple.png"
    );
    m_ColorMap[CubeColor::dirt] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_dirt.png"
    );
    m_ColorMap[CubeColor::gray] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_gray.png"
    );
    m_ColorMap[CubeColor::green] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_green.png"
    );
    m_ColorMap[CubeColor::heal] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_heal.png"
    );
    m_ColorMap[CubeColor::metrognome] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_metrognome.png"
    );
    m_ColorMap[CubeColor::orange] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_orange.png"
    );
    m_ColorMap[CubeColor::purple] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_purple.png"
    );
    m_ColorMap[CubeColor::red] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_red.png"
    );
    m_ColorMap[CubeColor::spore] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_spore.png"
    );
    m_ColorMap[CubeColor::stone] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_stone.png"
    );
    m_ColorMap[CubeColor::wall] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_wall.png"
    );
    m_ColorMap[CubeColor::water] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_water.png"
    );
    m_ColorMap[CubeColor::white] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_white.png"
    );
    m_ColorMap[CubeColor::yellow] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_yellow.png"
    );
    m_ColorMap[CubeColor::yellowgreen] = std::make_shared<Util::Image>(
        ASSETS_DIR "/particles/TEMP_particle_yellowgreen.png"
    );
    m_ColorMapInitialized = true;
}

std::map<Dungeon::CubeColor, std::shared_ptr<Util::Image>>
     ColorCube::m_ColorMap;
bool ColorCube::m_ColorMapInitialized = false;

}  // namespace Dungeon
