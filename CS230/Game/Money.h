/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.h
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class GameObjectManager;
enum class GameObjectType;

class Money : public CS230::GameObject {
public:
    Money(math::vec2 pos, math::vec2 ballrobotVelocity);
    void Update(double dt) override;
    std::string GetObjectTypeName() { return "Money"; }
    virtual GameObjectType GetObjectType() override { return GameObjectType::Money; }
    virtual bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;
private:
};