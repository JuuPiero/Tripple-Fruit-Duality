#include "Fruit.h"

#include "ScriptRegistration.h"
#include "LevelData.h"
#include "DualityEngine\Scripting\Debug.h"
#include <glm/glm.hpp>

void Fruit::OnCreate() {
    SpriteRenderer = GetComponent<SpriteRendererComponent>();
    SpriteRenderer.Color = glm::vec4{ 0.0f, 1.0f, 1.0f, 1.0f };
    Debug::Log("OnCreate");
    
}

void Fruit::OnUpdate(float deltaTime) {

}

void Fruit::OnPointerDown(PointerEventData& eventData) {
    Debug::Log("Clicked");
}
void Fruit::Init() {

}
REGISTER_BEHAVIOUR(Fruit)
