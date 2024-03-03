cmake_minimum_required(VERSION 3.16)
project(FUCK_PTSD)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(PTSD)
add_library(Framework ${PTSD_SRC_FILES} $<TARGET_OBJECTS:PracticalToolsForSimpleDesign>)

# include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)
#list(TRANSFORM LIB_FILES PREPEND ${LIB_DIR}/)

file(GLOB_RECURSE SRC_FILES src/*)
file(GLOB_RECURSE LIB_FILES libs/*)
file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_FILES}
    ${HEADER_FILES}
    ${LIB_FILES}
)

# download some plugin
include("${CMAKE_DIR}/Dependencies.cmake")

# include rust settings
include("${CMAKE_DIR}/Rust.cmake")


if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PTSD_DIR="${CMAKE_CURRENT_SOURCE_DIR}/PTSD")
    target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
else()
    message(FATAL_ERROR "relative RESOURCE_DIR is WIP, Please use `-DCMAKE_BUILD_TYPE=Debug` build for now.")
    # target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_INSTALL_PREFIX}/Resources")
endif()


target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Game)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Settings)


target_link_libraries(Framework
    ${DEPENDENCY_LINK_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    Framework
    rusty_bridge
)

#target_link_libraries(${PROJECT_NAME} PRIVATE rusty_bridge)
