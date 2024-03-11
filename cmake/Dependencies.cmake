include(FetchContent)

FetchContent_Declare(
        Corrosion
        GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
        GIT_TAG master
)
FetchContent_MakeAvailable(Corrosion)

message(STATUS "Tinyxml2 NOT FOUND, fetching from source!")
FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/TinyXML2
        GIT_TAG 9.0.0
)
FetchContent_MakeAvailable(tinyxml2)

message(STATUS "PTSD NOT FOUND, fetching from source!")
FetchContent_Declare(
        PTSD
        GIT_REPOSITORY https://github.com/NTUT-FUCK-PTSD/practical-tools-for-simple-design
        GIT_TAG submodule-ized
)
FetchContent_MakeAvailable(PTSD)

message(STATUS "PTSD: ${PTSD_SOURCE_DIR}")

#FetchContent_GetProperties(PTSD)
#if(NOT PTSD_POPULATED)
#    FetchContent_Populate(PTSD)
#    add_subdirectory(${PTSD_SOURCE_DIR} ${PTSD_BINARY_DIR})
#endif()

#include_directories(${PTSD_SOURCE_DIR}/include)

#add_library(PTSD INTERFACE)

#target_include_directories(PTSD INTERFACE ${asio_SOURCE_DIR}/PTSD/include)

