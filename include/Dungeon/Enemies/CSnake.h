#ifndef SNAKE_H
#define SNAKE_H

#include "glm/vec2.hpp"

class CSnake {
public:
    bool      Head = false;
    bool      Dead = false;
    glm::vec2 Position = {0, 0};
};

#endif  // SNAKE_H
