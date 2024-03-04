//
// Created by 陳世昂 on 2024/3/4.
//

#ifndef FUCK_PTSD_GLOBALTYPE_H
#define FUCK_PTSD_GLOBALTYPE_H

#include <iostream>

namespace GlobalType {
struct Background {
  std::shared_ptr<Background> m_MainMenu;
  std::shared_ptr<Background> m_Continue;
};

// struct Protagonist {
//   std::shared_ptr<Chara>
// };
};     // namespace GlobalType
#endif // FUCK_PTSD_GLOBALTYPE_H
