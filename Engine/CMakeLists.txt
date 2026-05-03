add_subdirectory(vendor/Cpptrace)

add_library(Engine
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

target_include_directories(Engine PRIVATE
	vendor/Cpptrace/include
	../vendor/SDL3/include
	src
	src/Engine
	src/Engine/Core
)

target_compile_definitions(Engine PRIVATE
	CPPTRACE_STATIC_DEFINE
	_ENGINE
)

target_link_libraries(Engine PRIVATE cpptrace::cpptrace SDL3::SDL3)