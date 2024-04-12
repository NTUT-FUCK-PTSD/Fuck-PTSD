cmake_minimum_required(VERSION 3.16)
project(FUCK_PTSD)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # see https://github.com/ntut-open-source-club/practical-tools-for-simple-design/issues/22
    set(CMAKE_RC_FLAGS="-C 1252")
endif()

#add_subdirectory(${CMAKE_BINARY_DIR}/_deps/ptsd-src/)
add_library(Framework ${PTSD_SRC_FILES} $<TARGET_OBJECTS:PracticalToolsForSimpleDesign>)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

file(GLOB_RECURSE SRC_FILES src/*)
file(GLOB_RECURSE HEADER_FILES include/*)


# import folder customize path
include("${CMAKE_SOURCE_DIR}/files.cmake")

add_executable(${PROJECT_NAME}
        ${SRC_DIR}/main.cpp
        ${SRC_FILES}
        ${HEADER_FILES}
        ${LIB_FILES}
)


# download some plugin
include("${CMAKE_DIR}/Dependencies.cmake")

# include rust settings
# include("${CMAKE_DIR}/Rust.cmake")


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
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PTSD_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${soloud_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/PTSD/3rdparty/sdl2/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CUSTOMIZE_PATH})

target_link_libraries(Framework
        ${DEPENDENCY_LINK_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2main
        tinyxml2::tinyxml2
        Framework
        #rusty_bridge
        soloud
)
