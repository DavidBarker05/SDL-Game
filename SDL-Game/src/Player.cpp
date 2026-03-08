#include "Player.h"
#include "InputManager.h"
#include "SDL2/SDL_log.h"

Player::Player() : m_Velocity()
{
	Super();
}

void Player::HandleInput(InputManager* pInputManager)
{
	m_Velocity = pInputManager->GetMoveInput() * 50.0f;
}

void Player::Tick(FLOAT32 deltaTime)
{
	Super::Tick(deltaTime);
	SDL_Log("%f", deltaTime); // lol this messes with the performance which stabalises to around 4000fps so it actually fixes the jitter issue
	m_Position += m_Velocity * deltaTime;
}

void Player::Render(SDL_Renderer* pRenderer)
{
	Super::Render(pRenderer);
}
