#include "Dungeon/MapHandler.h"

#include <random>

#include "Util/Transform.hpp"
#include "Util/TransformUtils.hpp"

namespace Dungeon {
MapHandler::MapHandler(const std::shared_ptr<Map> map)
    : m_Map(map) {
    m_Image = std::make_shared<Util::Image>(ASSETS_DIR
                                            "/gui/TEMP_overlay_red.png");
    m_EasterEgg = std::make_shared<Util::Image>(ASSETS_DIR "/EasterEgg.png");
}

void MapHandler::Draw(const Core::Matrices& data) {
    if (m_Map) {
        // Here can call m_Map functions
        m_Map->Update();
        if (!m_Map->IsAvailable()) {
            EasterEgg();
            return;
        }
        if (m_Map->IsOverlayRed()) {
            m_Image->Draw(data);
        }
    }
}

glm::vec2 MapHandler::GetSize() const {
    return m_Image->GetSize();
}

// This is definitely not Bouncing DVD Logo Screen
void MapHandler::ChangeEasterEggColor() {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 255);

    SDL_Surface& surface = m_EasterEgg->GetSDLSurface();
    auto         OriginalBlendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND;
    SDL_SetSurfaceColorMod(&surface, dis(gen), dis(gen), dis(gen));
    SDL_GetSurfaceBlendMode(&surface, &OriginalBlendMode);
    SDL_SetSurfaceBlendMode(&surface, SDL_BLENDMODE_BLEND);

    auto targetSurface =
        std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>>{
          SDL_CreateRGBSurfaceWithFormat(
              0,
              surface.w,
              surface.h,
              surface.format->BitsPerPixel,
              surface.format->format
          ),
          SDL_FreeSurface,
        };
    int isCopyWork = SDL_BlitSurface(&surface, NULL, targetSurface.get(), NULL);
    if (isCopyWork != 0) {
        LOG_ERROR("SDL_BlitSurface failed: {}", SDL_GetError());
        return;
    }

    SDL_SetSurfaceColorMod(&surface, 255, 255, 255);
    SDL_SetSurfaceBlendMode(&surface, OriginalBlendMode);

    m_EasterEgg->UpdateTextureData(*targetSurface);
}

void MapHandler::EasterEgg() {
    static glm::vec2 dir = {1, 0.5};

    auto& pos = m_Transform.translation;
    auto  HalfImgSize = m_EasterEgg->GetSize() / 2.0f;

    if (pos.y + HalfImgSize.y >= static_cast<float>(WINDOW_HEIGHT) / 2
        || pos.y - HalfImgSize.y + static_cast<float>(WINDOW_HEIGHT) / 2 <= 0) {
        ChangeEasterEggColor();
        dir.y *= -1;
    }
    if (pos.x + HalfImgSize.x >= static_cast<float>(WINDOW_WIDTH) / 2
        || pos.x - HalfImgSize.x + static_cast<float>(WINDOW_WIDTH) / 2 <= 0) {
        ChangeEasterEggColor();
        dir.x *= -1;
    }

    auto delta = static_cast<float>(Util::Time::GetDeltaTimeMs());
    pos += dir * delta * 0.5F;

    auto data = Util::ConvertToUniformBufferData(
        m_Transform,
        m_EasterEgg->GetSize(),
        100
    );
    data.m_Model = glm::translate(
        data.m_Model,
        glm::vec3{glm::vec2{0, 0} / m_EasterEgg->GetSize(), 0} * -1.0F
    );

    m_EasterEgg->Draw(data);
}

}  // namespace Dungeon
