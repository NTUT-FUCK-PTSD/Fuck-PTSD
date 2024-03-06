#ifndef LEVEL_H
#define LEVEL_H

#include "Dungeon/Elements.h"
#include "Util/Logger.hpp"

#include "tinyxml2.h"
#include <vector>

namespace Dungeon {

class Level {
public:
    Level(const std::string path, const int levelNum = 1);
    void LoadLevel(const int levelNum);

    int GetNumLevels() { return m_NumLevels; }
    int GetBossNum() { return m_BossNum; }
    int GetMusic() { return m_Music; }
    int GetCurrentLevel() { return m_CurrentLevel; }
    std::vector<tile> GetTiles() { return m_Tiles; }
    std::vector<trap> GetTraps() { return m_Traps; }
    std::vector<enemy> GetEnemies() { return m_Enemies; }
    std::vector<item> GetItems() { return m_Items; }
    std::vector<chest> GetChests() { return m_Chests; }
    std::vector<crate> GetCrates() { return m_Crates; }
    std::vector<shrine> GetShrines() { return m_Shrines; }

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
