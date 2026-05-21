#include "Player.h"
#include "Input/InputSystem.h"

Player::Player() :
    Super(Vec2D(0.0f, 0.0f), Vec2D(50.0f, 50.0f)), m_Velocity(),
    m_RenderComponent(&m_Position, Vector2(), m_HalfExtents, Color(255, 0, 255))
{
}

void Player::Tick(FLOAT32 deltaTime)
{
    Super::Tick(deltaTime);
    m_Velocity = InputSystem::GetMoveInput() * 50.0f;
    m_Position += m_Velocity * deltaTime;
}
