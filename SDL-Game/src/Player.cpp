#include "Player.h"
#include "InputManager.h"

Player::Player() : Super(NULL, VEC2D(0.0f, 0.0f), VEC2D(25.0f, 25.0f)), m_Velocity()
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

void Player::Render(P_RENDERER pRenderer)
{
	Super::Render(pRenderer);
}
