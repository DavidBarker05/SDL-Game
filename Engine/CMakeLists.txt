add_subdirectory(vendor/Cpptrace)

set(ENGINE_SOURCES
	src/Core/Events/EventSystem.cpp
	src/Core/Events/EventSystem.h
	src/Core/Files/FileSystem.cpp
	src/Core/Files/FileSystem.h
	src/Core/Input/InputSystem.cpp
	src/Core/Input/InputSystem.h
	src/Core/Logging/Log.cpp
	src/Core/Logging/Log.h
	src/Core/Math/Bounds2D.h
	src/Core/Math/Math.cpp
	src/Core/Math/Math.h
	src/Core/Math/Vector2D.h
	src/Core/Renderer/Color.h
	src/Core/Renderer/Renderer.h
	src/Core/Renderer/Renderer.cpp
	src/Core/Renderer/Renderer.h
	src/Core/Core.h
	src/Core/Functions.h
	src/Core/Types.h
	src/Engine/Component/Component.cpp
	src/Engine/Component/Component.h
	src/Engine/Object/ObjectManager/ObjectManager.cpp
	src/Engine/Object/ObjectManager/ObjectManager.h
	src/Engine/Entity/Entity.cpp
	src/Engine/Entity/Entity.h
	src/Engine/Object/Object.cpp
	src/Engine/Object/Object.h
	src/Engine/RenderComponent/FilledRectRenderComponent/FilledRectRenderComponent.cpp
	src/Engine/RenderComponent/FilledRectRenderComponent/FilledRectRenderComponent.h
	src/Engine/RenderComponent/RenderComponent.cpp
	src/Engine/RenderComponent/RenderComponent.h
	src/Engine/Tickable.h
)

add_library(Engine ${ENGINE_SOURCES})

set_target_properties(Engine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug-${CMAKE_SYSTEM_PROCESSOR}/Engine
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release-${CMAKE_SYSTEM_PROCESSOR}/Engine
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})

target_compile_definitions(Engine PRIVATE
    CPPTRACE_STATIC_DEFINE
    _ENGINE
)

target_include_directories(Engine PRIVATE
    vendor/Cpptrace/include
    ../vendor/SDL3/include
    src
    src/Core
    src/Engine
	${CMAKE_BINARY_DIR}
)

target_link_libraries(Engine PRIVATE cpptrace::cpptrace SDL3::SDL3)