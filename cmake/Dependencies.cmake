include(FetchContent)

cmake_policy(SET CMP0135 NEW)


# FetchContent_Declare(
#         Corrosion
#         GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
#         GIT_TAG master
# )
# FetchContent_MakeAvailable(Corrosion)

message(STATUS "Tinyxml2 NOT FOUND, fetching from source!")
FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/TinyXML2
        GIT_TAG 9.0.0

        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/tinyxml2
)
FetchContent_MakeAvailable(tinyxml2)

message(STATUS "PTSD NOT FOUND, fetching from source!")
set(PTSD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/PTSD")
FetchContent_Declare(
        PTSD
        GIT_REPOSITORY https://github.com/NTUT-FUCK-PTSD/practical-tools-for-simple-design
        GIT_TAG pivot

        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/PTSD
)
FetchContent_MakeAvailable(PTSD)

message(STATUS "PTSD: ${PTSD_SOURCE_DIR}")

message(STATUS "soloud NOT FOUND, fetching from source!")
FetchContent_Declare(
        soloud
        GIT_REPOSITORY https://github.com/onon1101/soloud.git
        # GIT_TAG noinst
        GIT_TAG onon1101-patch-2

        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/soloud
)

FetchContent_GetProperties(soloud)
if (NOT soloud_POPULATED)
    FetchContent_Populate(soloud)
    add_subdirectory(${soloud_SOURCE_DIR}/contrib)
endif()

message(STATUS "soloud: ${soloud_SOURCE_DIR}")


