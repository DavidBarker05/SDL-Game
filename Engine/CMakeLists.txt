add_subdirectory(vendor/Cpptrace)

set(ENGINE_SOURCES
    src/Engine/Core/Events/EventSystem.cpp
	src/Engine/Core/Events/EventSystem.h
	src/Engine/Core/Input/InputSystem.cpp
	src/Engine/Core/Input/InputSystem.h
	src/Engine/Core/Logging/Log.cpp
	src/Engine/Core/Logging/Log.h
	src/Engine/Core/Math/Math.cpp
	src/Engine/Core/Math/Math.h
	src/Engine/Core/Math/Vector2D.h
	src/Engine/Core/Renderer/Renderer.cpp
	src/Engine/Core/Renderer/Renderer.h
	src/Engine/Core/Core.h
	src/Engine/Core/Functions.h
	src/Engine/Core/Types.h
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
    src/Engine
    src/Engine/Core
)

target_link_libraries(Engine PRIVATE cpptrace::cpptrace SDL3::SDL3)