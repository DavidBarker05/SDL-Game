add_executable(SDL-Game
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