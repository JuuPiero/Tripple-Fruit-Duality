#pragma once

#include "DualityEngine/Scene/Behaviour.h"
#include "LevelData.h"

using namespace Duality;
class Tree : public Behaviour {
public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void Init(int treeIndex);
};
