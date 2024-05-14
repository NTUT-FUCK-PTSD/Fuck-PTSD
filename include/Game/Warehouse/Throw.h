#ifndef FUCK_PTSD_2024_04_30_THROW_H
#define FUCK_PTSD_2024_04_30_THROW_H

#include <memory>
#include <stdexcept>
#include "Game/Game_config.h"
#include "IEquip.h"
#include "Player_config.h"
#include "Util/Image.hpp"
#include "glm/fwd.hpp"

namespace Game::Warehouse {
class Throw : public IEquip {
public:
    explicit Throw(std::string filePath, const std::string& type);
    virtual ~Throw() = default;

    void SpecialFunction(Config::SF sf);

    void SetPosition(const glm::vec2& Position) override;

    [[nodiscard]]
    Pos GetWinPos() const override {
        return Pos::COL;
    }

    [[nodiscard]]
    std::string GetName() const override {
        return "THROW";
    }

    [[nodiscard]]
    std::string GetType() const override {
        return m_typeName;
    }

    [[nodiscard]]
    std::string GetImagePath() const override {
        return m_ItemImg;
    }

private:
    std::string m_ItemImg;
    std::string m_typeName;
    void        InitSlot();
    void        ToggleSlot();

    void GenSlot();
    void GenSlot2();
    void GenItem();
    void GenFirstTxt();
    void GenSecondTxt();

    static constexpr std::string_view m_FistTxt = "UP+";
    static constexpr std::string_view m_SecondTxt = "DOWN";

    static constexpr glm::vec2 m_SlotOffset = {0, 0};
    static constexpr glm::vec2 m_ItemOffset = {0, 5};

private:
#ifdef _WIN32
    static constexpr glm::vec2 m_FirstTxtOffset = {25, -40};
    static constexpr glm::vec2 m_SecondTxtOffset = {25, -60};
#elif __APPLE__
    static constexpr glm::vec2 m_FirstTxtOffset = {15, -40};
    static constexpr glm::vec2 m_SecondTxtOffset = {15, -60};
#else
    static constexpr glm::vec2 m_FirstTxtOffset = {25, -40};
    static constexpr glm::vec2 m_SecondTxtOffset = {25, -60};
#endif
};
}  // namespace Game::Warehouse

#endif  // FUCK_PTSD_2024_04_30_THROW_H
