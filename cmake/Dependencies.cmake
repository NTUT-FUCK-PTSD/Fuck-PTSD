include(FetchContent)

FetchContent_Declare(
        Corrosion
        GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
        GIT_TAG master
)
FetchContent_MakeAvailable(Corrosion)

message(STATUS "Tinyxml2 NOT FOUND, fetching from source!")
FetchContent_Declare(tinyxml2
        GIT_REPOSITORY     https://github.com/leethomason/TinyXML2
        GIT_TAG            9.0.0
)
FetchContent_MakeAvailable(tinyxml2)
