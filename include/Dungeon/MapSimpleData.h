#ifndef MAPSIMPLEDATA_H
#define MAPSIMPLEDATA_H

#include "glm/glm.hpp"

class MapSimpleData {
public:
    MapSimpleData();
    ~MapSimpleData();
    glm::ivec2 GetLevelIndexMax() const;
    glm::ivec2 GetLevelIndexMin() const;
    size_t GetSize() const;

    void SetLevelIndexMax(const glm::ivec2 &levelIndexMax);
    void SetLevelIndexMin(const glm::ivec2 &levelIndexMin);

private:
    glm::ivec2 m_LevelIndexMax;
    glm::ivec2 m_LevelIndexMin;
    size_t m_Size;
};

#endif // MAPSIMPLEDATA_H
