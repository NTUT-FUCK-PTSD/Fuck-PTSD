#ifndef LEVEL_H
#define LEVEL_H

#include "Dungeon/Elements.h"
#include "Util/Logger.hpp"

#include "tinyxml2.h"
#include <vector>

namespace Dungeon {

class Level {
public:
    Level(std::string path, int levelNum = 1);
    void loadLevel(int levelNum);

    int getNumLevels() { return m_NumLevels; }
    int getBossNum() { return m_BossNum; }
    int getMusic() { return m_Music; }
    int getCurrentLevel() { return m_CurrentLevel; }
    std::vector<tile> getTiles() { return m_Tiles; }

private:
    int m_NumLevels;
    int m_BossNum;
    int m_Music;
    int m_CurrentLevel;

    tinyxml2::XMLDocument m_doc;
    tinyxml2::XMLElement *m_XMLdungeon;
    tinyxml2::XMLElement *m_XMLlevel;

    std::vector<tile> m_Tiles;
    std::vector<trap> m_Traps;
    std::vector<enemy> m_Enemies;
    std::vector<item> m_Items;
    std::vector<chest> m_Chests;
    std::vector<crate> m_Crates;
    std::vector<shrine> m_Shrines;
}; // class Level
} // namespace Dungeon

#endif // LEVEL_H
