#pragma once

#include "DualityEngine/Scene/Behaviour.h"

using namespace Duality;

class TestCube : public Behaviour {
public:
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;

private:
    float m_Elapsed = 0.0f;
};
