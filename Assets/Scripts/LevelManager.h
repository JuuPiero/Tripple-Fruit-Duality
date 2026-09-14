#pragma once
#include "DualityEngine/Scene/Behaviour.h"
using namespace Duality;
class LevelManager : public Behaviour {
public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
};