set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)


list(APPEND CUSTOMIZE_PATH

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Settings
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Dungeon
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Tools
    ${CMAKE_CURRENT_BINARY_DIR}/include/Music
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Dungeon/Enemies
    ${CMAKE_CURRENT_BINARY_DIR}/include/SubWindow
    ${CMAKE_CURRENT_BINARY_DIR}/include/SubWindow/Component
    ${CMAKE_CURRENT_BINARY_DIR}/include/SubWindow/Entity
)