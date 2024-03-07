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
    std::vector<s_Tile> GetTiles() { return m_Tiles; }
    std::vector<s_Trap> GetTraps() { return m_Traps; }
    std::vector<s_Enemy> GetEnemies() { return m_Enemies; }
    std::vector<s_Item> GetItems() { return m_Items; }
    std::vector<s_Chest> GetChests() { return m_Chests; }
    std::vector<s_Crate> GetCrates() { return m_Crates; }
    std::vector<s_Shrine> GetShrines() { return m_Shrines; }

private:
    int m_NumLevels;
    int m_BossNum;
    int m_Music;
    int m_CurrentLevel;

    tinyxml2::XMLDocument m_doc;
    tinyxml2::XMLElement *m_XMLdungeon;
    tinyxml2::XMLElement *m_XMLlevel;

    std::vector<s_Tile> m_Tiles;
    std::vector<s_Trap> m_Traps;
    std::vector<s_Enemy> m_Enemies;
    std::vector<s_Item> m_Items;
    std::vector<s_Chest> m_Chests;
    std::vector<s_Crate> m_Crates;
    std::vector<s_Shrine> m_Shrines;
}; // class Level
} // namespace Dungeon

#endif // LEVEL_H
