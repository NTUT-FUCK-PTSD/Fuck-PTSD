#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

namespace Map {
struct tile {
    int x, y;
    int type, zone, torch, cracked;
};

class Level {
public:
    Level(std::string path, int levelNum = 0);
    void loadLevel(int levelNum);

    int getNumLevels() { return m_numLevels; }
    int getBossNum() { return m_bossNum; }
    int getMusic() { return m_music; }
    int getCurrentLevel() { return m_currentLevel; }
    std::vector<tile> getTiles() { return m_tiles; }

private:
    int m_numLevels;
    int m_bossNum;
    int m_music;
    int m_currentLevel;

    std::vector<tile> m_tiles;
}; // class Level
} // namespace Map

#endif // LEVEL_H
