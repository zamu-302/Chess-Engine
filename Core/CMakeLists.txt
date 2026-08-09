add_library(Core STATIC)

target_sources(Core
    PRIVATE
        Source/Core/Board.cpp
        Source/Core/Evaluation.cpp
        Source/Core/lookuptabel.cpp
        Source/Core/MoveGen.cpp
        Source/Core/Preft.cpp
        Source/Core/Search.cpp
)

target_include_directories(Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_compile_features(Core PUBLIC cxx_std_20)

target_compile_definitions(Core
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:RELEASE>
        $<$<CONFIG:Dist>:DIST>
)

if(MSVC)
    target_compile_options(Core PRIVATE /EHsc /Zc:preprocessor /Zc:__cplusplus /W4)
else()
    # -Wall -Wextra: catch the kind of silent bugs (uninitialized reads,
    # signed/unsigned mismatches, etc.) that are easy to miss by eye in
    # bitboard code. Not treated as errors, just surfaced.
    target_compile_options(Core PRIVATE -Wall -Wextra)
endif()
