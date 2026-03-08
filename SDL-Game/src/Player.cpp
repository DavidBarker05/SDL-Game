#include "Player.h"
#include "Game.h"
#include "EventManager.h"
#include "GameRenderer.h"
#include "InputManager.h"

Player::Player(Game* pGame) : m_pGame(pGame), m_Position(), m_Velocity()
{
}

void Player::Start()
{
}

void Player::Tick(FLOAT32 deltaTime)
{
	m_pGame->GetGameRenderer()->SetPlayer(this);
	m_Velocity = m_pGame->GetEventManager()->GetInputManager()->GetMoveInput() * 50.0f;
	m_Position += m_Velocity * deltaTime;
}

void Player::Render(SDL_Renderer* pRenderer)
{
	SDL_Rect r = { m_Position.x, m_Position.y, 50, 50 };
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(pRenderer, &r);
}
