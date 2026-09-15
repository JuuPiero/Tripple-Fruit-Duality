#include "TestCube.h"

#include <cmath>

#include "DualityEngine/Scripting/MeshRenderer.h"
#include "ScriptRegistration.h"

void TestCube::OnUpdate(float deltaTime) {
    MeshRenderer renderer(GetEntity());
    if (!renderer)
        return;

    m_Elapsed += deltaTime;
    // The phase-shifted waves sweep RGB smoothly. This changes this renderer's runtime
    // material Color only; the assigned .mat retains its Texture and VertexLit/Unlit mode.
    renderer.SetMaterialColor({
        0.5f + 0.5f * std::sin(m_Elapsed * 1.2f),
        0.5f + 0.5f * std::sin(m_Elapsed * 1.2f + 2.0943951f),
        0.5f + 0.5f * std::sin(m_Elapsed * 1.2f + 4.1887902f),
        1.0f
    });
}

void TestCube::OnDestroy() {
    // Defensive cleanup for an entity destroyed while Play mode remains active.
    MeshRenderer(GetEntity()).ClearMaterialColor();
}

REGISTER_BEHAVIOUR(TestCube)
