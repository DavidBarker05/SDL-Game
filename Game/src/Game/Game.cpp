#include "Game.h"
#include "Engine/Entity/Entity.h"
#include "Engine/RenderComponent/FilledRectRenderComponent/FilledRectRenderComponent.h"
#include "Events/EventSystem.h"
#include "Renderer/Renderer.h"
#include <memory>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>

#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif // _MSC_VER

bool Game::Init(CSTRING executablePath, CSTRING companyName, CSTRING productName)
{
    Logger::Init();
    FileSystem::Init(executablePath, companyName, productName);
    if (!Renderer::Init()) return false;
    if (!EventSystem::Init()) return false;
    return true;
}

bool Game::Init(CSTRING executablePath, CSTRING companyName, CSTRING productName, CSTRING title, UINT32 windowWidth,
                UINT32 windowHeight)
{
    Logger::Init();
    FileSystem::Init(executablePath, companyName, productName);
    if (!Renderer::Init(title, windowWidth, windowHeight)) return false;
    if (!EventSystem::Init()) return false;
    return true;
}

void Game::Shutdown()
{
    Renderer::Shutdown();
    EventSystem::Shutdown();
    SDL_Quit();
}

void Game::Start()
{
    m_bGameIsRunning = true;
    auto spScene = ObjectSystem::Create<Entity>();
    auto spPlayer = ObjectSystem::Create<Entity>();
    auto spRenderComponent = ObjectSystem::Create<FilledRectRenderComponent>();
    spRenderComponent->SetBounds(Bounds2D({0.0f, 0.0f}, {50.0f, 50.0f}));
    spRenderComponent->SetColor(Color(255, 255, 255));
    spRenderComponent->Attach(spPlayer);
    while (m_bGameIsRunning) Tick();
}

void Game::Tick()
{
    UpdateDeltaTime();
    UINT32 status = EventSystem::PollEvents();
    if (status == EventSystem::Quit)
    {
        m_bGameIsRunning = false;
        return;
    }
    Renderer::Render();
}

void Game::UpdateDeltaTime()
{
    m_CurrentFrameTime = SDL_GetPerformanceCounter();
    m_DeltaTime = (m_CurrentFrameTime - m_LastFrameTime) / (FLOAT64)SDL_GetPerformanceFrequency();
    m_LastFrameTime = m_CurrentFrameTime;
}
