add_executable(App)

target_sources(App
    PRIVATE
        Source/App.cpp
)

target_link_libraries(App
    PRIVATE
        Core
)

target_include_directories(App
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_compile_features(App PUBLIC cxx_std_20)

target_compile_definitions(App
    PRIVATE
        $<$<PLATFORM_ID:Windows>:WINDOWS>
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:RELEASE>
        $<$<CONFIG:Dist>:DIST>
)

if(MSVC)
    target_compile_options(App PRIVATE /EHsc /Zc:preprocessor /Zc:__cplusplus /W4)
else()
    target_compile_options(App PRIVATE -Wall -Wextra)
endif()
