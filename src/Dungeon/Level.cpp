#include "Dungeon/Level.h"
namespace Dungeon {

Level::Level(const std::string path, const int levelNum) {
    if (m_doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
        LOG_ERROR("Failed to load level file: " + path);
        throw std::runtime_error("Failed to load level file: " + path);
    }
    LoadLevel(levelNum);
    m_NumLevels = m_XMLdungeon->FindAttribute("numLevels")->IntValue();
}
void Level::LoadLevel(const int levelNum) {
    m_XMLdungeon = m_doc.FirstChildElement("dungeon");
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
    tile t;
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
    }
    // load traps
    trap tr;
    m_Traps.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("traps")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        tr.x = child->FindAttribute("x")->IntValue();
        tr.y = child->FindAttribute("y")->IntValue();
        tr.type = child->FindAttribute("type")->IntValue();
        tr.subtype = child->FindAttribute("subtype")->IntValue();
        m_Traps.push_back(tr);
    }
    // load enemies
    enemy e;
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
    }
    // load items
    item i;
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
    }
    // load chests
    chest c;
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
    }
    // load crates
    crate cr;
    m_Crates.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("crates")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        cr.x = child->FindAttribute("x")->IntValue();
        cr.y = child->FindAttribute("y")->IntValue();
        cr.type = child->FindAttribute("type")->IntValue();
        cr.contents = child->FindAttribute("contents")->Value();
        m_Crates.push_back(cr);
    }
    // load shrines
    shrine s;
    m_Shrines.clear();
    for (auto child =
             m_XMLlevel->FirstChildElement("shrines")->FirstChildElement();
         child != nullptr; child = child->NextSiblingElement()) {
        s.x = child->FindAttribute("x")->IntValue();
        s.y = child->FindAttribute("y")->IntValue();
        s.type = child->FindAttribute("type")->IntValue();
        m_Shrines.push_back(s);
    }
}
} // namespace Dungeon
