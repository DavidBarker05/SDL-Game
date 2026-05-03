set(GAME_SOURCES
	src/Core/Events/EventListener.h
	src/Core/Rendering/Renderable.h
	src/Game/Entity.cpp
	src/Game/Entity.h
	src/Game/Game.cpp
	src/Game/Game.h
	src/Game/Scene.cpp
	src/Game/Scene.h
	src/Main.cpp
	src/Player.cpp
	src/Player.h
)

add_executable(SDL-Game ${GAME_SOURCES})

set_target_properties(SDL-Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug-${CMAKE_SYSTEM_PROCESSOR}/SDL-Game
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release-${CMAKE_SYSTEM_PROCESSOR}/SDL-Game
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${GAME_SOURCES})

target_include_directories(SDL-Game PRIVATE
    ../Engine/src
	../Engine/src/Engine/Core
	../vendor/SDL3/include
	src
)

target_link_libraries(SDL-Game PRIVATE Engine SDL3::SDL3)

add_custom_command(TARGET SDL-Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:SDL-Game>
)