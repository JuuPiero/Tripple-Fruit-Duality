#pragma once

#include "DualityEngine/Scene/Behaviour.h"

class GameManager : public Duality::Behaviour {
public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
};
