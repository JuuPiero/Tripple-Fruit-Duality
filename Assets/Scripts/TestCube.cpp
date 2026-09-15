#include "TestCube.h"

#include <cmath>

#include "DualityEngine/Asset/AssetDatabase.h"
#include "DualityEngine/Asset/MaterialLoader.h"
#include "ScriptRegistration.h"

void TestCube::OnCreate() {
    MeshRenderer renderer(GetEntity());
    if (!renderer || renderer.GetMaterials().empty())
        return;

    m_MaterialPath = AssetDatabase::ResolvePath(renderer.GetMaterials().front().Guid);
    if (!m_MaterialPath.empty())
        m_OriginalMaterial = MaterialLoader::Load(m_MaterialPath);
}

void TestCube::OnUpdate(float deltaTime) {
    if (m_MaterialPath.empty())
        return;

    m_Elapsed += deltaTime;
    // Phase-shifted sine waves sweep smoothly through RGB. Start from the original material so
    // Texture and VertexLit/Unlit mode remain unchanged; only its albedo Color is animated.
    Material animated = m_OriginalMaterial;
    animated.Color = {
        0.5f + 0.5f * std::sin(m_Elapsed * 1.2f),
        0.5f + 0.5f * std::sin(m_Elapsed * 1.2f + 2.0943951f),
        0.5f + 0.5f * std::sin(m_Elapsed * 1.2f + 4.1887902f),
        m_OriginalMaterial.Color.a
    };
    MaterialLoader::SetRuntime(m_MaterialPath, animated);
}

void TestCube::OnDestroy() {
    // Play->Stop must not leave a temporary animation tint in the process-wide shared cache.
    MaterialLoader::SetRuntime(m_MaterialPath, m_OriginalMaterial);
}

REGISTER_BEHAVIOUR(TestCube)
