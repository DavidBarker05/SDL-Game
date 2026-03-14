#include "Player.h"
#include "InputManager.h"

Player::Player() : Super(nullptr, Vec2D(0.0f, 0.0f), Vec2D(25.0f, 25.0f)), m_Velocity()
{
}

void Player::HandleInput(InputManager* pInputManager)
{
	m_Velocity = pInputManager->GetMoveInput() * 50.0f;
}

void Player::Tick(FLOAT32 deltaTime)
{
	Super::Tick(deltaTime);
	m_Position += m_Velocity * deltaTime;
}

void Player::Render(SDL_Renderer* pRenderer)
{
	Super::Render(pRenderer);
}
