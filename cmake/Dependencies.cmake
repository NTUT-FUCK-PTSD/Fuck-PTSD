include(FetchContent)

# FetchContent_Declare(
#         Corrosion
#         GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
#         GIT_TAG master
# )
# FetchContent_MakeAvailable(Corrosion)

message(STATUS "Tinyxml2 NOT FOUND, fetching from source!")
FetchContent_Declare(
        tinyxml2
        URL             https://github.com/leethomason/tinyxml2/archive/refs/tags/9.0.0.zip
        URL_HASH        MD5=2a3b1b8acdc1a0bd15e4010d91c505f8
        # GIT_REPOSITORY https://github.com/leethomason/TinyXML2
        # GIT_TAG 9.0.0

        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/tinyxml2
)

FetchContent_Declare(
        fmt
        URL             https://github.com/fmtlib/fmt/archive/refs/tags/10.2.1.zip
        URL_HASH        MD5=1bba4e8bdd7b0fa98f207559ffa380a3
        # GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        # GIT_TAG 10.2.1
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/fmt
)

message(STATUS "PTSD NOT FOUND, fetching from source!")
set(PTSD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/PTSD")
FetchContent_Declare(
        PTSD
        URL             https://github.com/NTUT-FUCK-PTSD/practical-tools-for-simple-design/archive/refs/tags/v1.2.7.zip
        URL_HASH        MD5=1ac18792e04dc8803b8f30089b781822
        # GIT_REPOSITORY https://github.com/NTUT-FUCK-PTSD/practical-tools-for-simple-design.git
        # GIT_TAG v1.2.7
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/PTSD
)

message(STATUS "PTSD: ${PTSD_SOURCE_DIR}")

message(STATUS "soloud NOT FOUND, fetching from source!")
FetchContent_Declare(
        soloud
        URL             https://github.com/onon1101/soloud/archive/refs/tags/0.0.1.zip
        URL_HASH        MD5=cf2fc645ac84f54c4478cea4b0fc9053
#        GIT_REPOSITORY https://github.com/onon1101/soloud.git
#        GIT_TAG onon1101-patch-2

        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/soloud
)

FetchContent_MakeAvailable(tinyxml2 fmt PTSD)

FetchContent_GetProperties(soloud)
if (NOT soloud_POPULATED)
    FetchContent_Populate(soloud)
    set(SDL2_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/PTSD/3rdparty/sdl2/include
    )
    add_subdirectory(${soloud_SOURCE_DIR}/contrib)
endif()

list(APPEND DEP_INCLUDES_FOLDERS
        ${DEPENDENCY_INCLUDE_DIRS}
        ${PTSD_SOURCE_DIR}/include
)

message(STATUS "soloud: ${soloud_SOURCE_DIR}")
