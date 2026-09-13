#pragma once

#include "DualityEngine/Scene/Behaviour.h"

// Add once to a long-lived entity, normally GameManager.
class DuTweenRunner final : public Duality::Behaviour {
public:
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;
};
