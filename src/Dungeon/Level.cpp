#include "Dungeon/Level.h"
namespace Dungeon {

Level::Level(const std::string &path, const int levelNum) {
    LoadFile(path);
    LoadLevel(levelNum);
}

Level::Level(const std::string &path) {
    LoadFile(path);
}

void Level::LoadFile(const std::string &path) {
    if (m_doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
        LOG_ERROR("Failed to load level file: " + path);
        // throw std::runtime_error("Failed to load level file: " + path);
        return;
    }
    m_XMLdungeon = m_doc.FirstChildElement("dungeon");
    m_NumLevels = m_XMLdungeon->FindAttribute("numLevels")->IntValue();
}

void Level::LoadLevel(const int levelNum) {
    if (levelNum > m_NumLevels) {
        LOG_ERROR("Level number out of range: " + std::to_string(levelNum));
        // throw std::runtime_error("Level number out of range: " +
        //                          std::to_string(levelNum));
        return;
    }

    m_LevelIndexMin = glm::ivec2(1e9, 1e9);
    m_LevelIndexMax = glm::ivec2(-1e9, -1e9);

    for (auto child = m_XMLdungeon->FirstChildElement("level");
         child != nullptr; child = child->NextSiblingElement("level")) {
        if (child->FindAttribute("num")->IntValue() == levelNum) {
            m_BossNum = child->FindAttribute("bossNum")->IntValue();
            m_Music = child->FindAttribute("music")->IntValue();
            m_CurrentLevel = levelNum;
            m_XMLlevel = child;
        }
    }

    // load tiles
    s_Tile t;
    m_Tiles.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("tiles")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        t.x = child->FindAttribute("x")->IntValue();
        t.y = child->FindAttribute("y")->IntValue();
        t.type = child->FindAttribute("type")->IntValue();
        t.zone = child->FindAttribute("zone")->IntValue();
        t.torch = child->FindAttribute("torch")->IntValue();
        t.cracked = child->FindAttribute("cracked")->IntValue();
        m_Tiles.push_back(t);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{t.x, t.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{t.x, t.y});
    }
    // load traps
    s_Trap tr;
    m_Traps.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("traps")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        tr.x = child->FindAttribute("x")->IntValue();
        tr.y = child->FindAttribute("y")->IntValue();
        tr.type = child->FindAttribute("type")->IntValue();
        tr.subtype = child->FindAttribute("subtype")->IntValue();
        m_Traps.push_back(tr);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{tr.x, tr.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{tr.x, tr.y});
    }
    // load enemies
    s_Enemy e;
    m_Enemies.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("enemies")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        e.x = child->FindAttribute("x")->IntValue();
        e.y = child->FindAttribute("y")->IntValue();
        e.type = child->FindAttribute("type")->IntValue();
        e.beatDelay = child->FindAttribute("beatDelay")->IntValue();
        e.lord = child->FindAttribute("lord")->IntValue();
        m_Enemies.push_back(e);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{e.x, e.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{e.x, e.y});
    }
    // load items
    s_Item i;
    m_Items.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("items")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        i.x = child->FindAttribute("x")->IntValue();
        i.y = child->FindAttribute("y")->IntValue();
        i.type = child->FindAttribute("type")->Value();
        i.bloodCost = child->FindAttribute("bloodCost")->IntValue();
        i.saleCost = child->FindAttribute("saleCost")->IntValue();
        i.singleChoice = child->FindAttribute("singleChoice")->IntValue();
        m_Items.push_back(i);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{i.x, i.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{i.x, i.y});
    }
    // load chests
    s_Chest c;
    m_Chests.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("chests")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        c.x = child->FindAttribute("x")->IntValue();
        c.y = child->FindAttribute("y")->IntValue();
        c.saleCost = child->FindAttribute("saleCost")->IntValue();
        c.singleChoice = child->FindAttribute("singleChoice")->IntValue();
        c.color = child->FindAttribute("color")->IntValue();
        c.hidden = child->FindAttribute("hidden")->IntValue();
        c.contents = child->FindAttribute("contents")->Value();
        m_Chests.push_back(c);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{c.x, c.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{c.x, c.y});
    }
    // load crates
    s_Crate cr;
    m_Crates.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("crates")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        cr.x = child->FindAttribute("x")->IntValue();
        cr.y = child->FindAttribute("y")->IntValue();
        cr.type = child->FindAttribute("type")->IntValue();
        cr.contents = child->FindAttribute("contents")->Value();
        m_Crates.push_back(cr);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{cr.x, cr.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{cr.x, cr.y});
    }
    // load shrines
    s_Shrine s;
    m_Shrines.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("shrines")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        s.x = child->FindAttribute("x")->IntValue();
        s.y = child->FindAttribute("y")->IntValue();
        s.type = child->FindAttribute("type")->IntValue();
        m_Shrines.push_back(s);
        m_LevelIndexMin = glm::min(m_LevelIndexMin, glm::ivec2{s.x, s.y});
        m_LevelIndexMax = glm::max(m_LevelIndexMax, glm::ivec2{s.x, s.y});
    }
}
} // namespace Dungeon
