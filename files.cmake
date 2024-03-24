set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)


list(APPEND CUSTOMIZE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Game
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Settings
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Character
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Dungeon
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Tools
)

#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Game)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Settings)