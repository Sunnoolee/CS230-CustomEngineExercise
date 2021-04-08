/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/23/2021
-----------------------------------------------------------------*/
#include "Ball.h"
#include "Level1.h"				// gravity, floor
#include "..\Engine\Camera.h"	// GetPosition()
#include "..\Engine\Engine.h"

Ball::Ball(math::vec2 startPos)
	:initPosition(startPos), position(startPos)
{}

void Ball::Load()
{
	sprite.Load("assets/Ball.png", math::ivec2{ 44,0 });
	position = initPosition;
	velocity = 0;

	currState = &stateLand;
	currState->Enter(this);
}

void Ball::Update(double dt)
{
	currState->Update(this, dt);
	position.y += velocity.y * dt;
	currState->TestForExit(this);

	if (position.y < Level1::floor)
	{
		position.y = Level1::floor;
		velocity.y = bounceVelocity;
	}

	objectMatrix = math::TranslateMatrix::TranslateMatrix(position);
}

void Ball::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(cameraMatrix* objectMatrix);
}

void Ball::ChangeState(State* newState)
{
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

void Ball::State_Bounce::Enter(Ball* ball)
{
	ball->velocity = ball->bounceVelocity;
}
void Ball::State_Bounce::Update(Ball* ball, double dt)
{
	ball->velocity.y -= Level1::gravity * dt;
}
void Ball::State_Bounce::TestForExit(Ball* ball)
{
	if (ball->position.y <= Level1::floor)
	{
		ball->ChangeState(&ball->stateLand);
	}
}

void Ball::State_Land::Enter(Ball* ball)
{
	ball->velocity.y = 0;
	ball->position.y = Level1::floor;
}
void Ball::State_Land::Update([[maybe_unused]] Ball* ball, [[maybe_unused]] double dt)
{
}
void Ball::State_Land::TestForExit(Ball* ball)
{
	ball->ChangeState(&ball->stateBounce);
}
