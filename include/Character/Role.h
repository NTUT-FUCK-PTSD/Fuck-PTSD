//
// Created by 陳世昂 on 2024/3/4.
//

#ifndef FUCK_PTSD_ROLE_H
#define FUCK_PTSD_ROLE_H

#include "Core/Drawable.hpp"
#include "Util/GameObject.hpp"

class Role final : public Util::GameObject {
  private:
  std::string &m_ImagePath;

  void ResetPosition();

  public:
  explicit Role();

  /* ----- Setter ----- */
  public:
  void SetShow(std::shared_ptr<Core::Drawable> &Display);

  /* ----- Getter ----- */
  public:
  [[nodiscard]] const std::string &GetImagePath() {
    return m_ImagePath;
  };

  [[nodiscard]] const glm::vec2 &GetPosition() {
    return m_Transform.translation;
  };

  [[nodiscard]] const glm::vec2 GetScale() {
    return m_Transform.scale;
  };

  [[nodiscard]] bool GetVisibility() {
    return m_Visible;
  };
};

#endif // FUCK_PTSD_ROLE_H
