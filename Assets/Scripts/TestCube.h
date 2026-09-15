#pragma once

#include <string>

#include "DualityEngine/Asset/Material.h"
#include "DualityEngine/Scene/Behaviour.h"
#include "DualityEngine/Scripting/MeshRenderer.h"

using namespace Duality;

class TestCube : public Behaviour {
public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;

private:
    std::string m_MaterialPath;
    Material m_OriginalMaterial;
    float m_Elapsed = 0.0f;
};
