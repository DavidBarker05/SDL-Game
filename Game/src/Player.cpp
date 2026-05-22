#include "Player.h"
#include "Input/InputSystem.h"

Player::Player() :
    Super(), m_Velocity(),
    m_RenderComponent(Bounds2D(Vector2(), Vector2(50.0f, 50.0f)), Color(255, 0, 255))
{
    m_RenderComponent.Attach(this);
}

void Player::Tick(FLOAT32 deltaTime)
{
    Super::Tick(deltaTime);
    m_Velocity = InputSystem::GetMoveInput() * 50.0f;
    m_Position += m_Velocity * deltaTime;
}
