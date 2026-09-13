#include "Fruit.h"

#include "ScriptRegistration.h"
#include "DualityEngine\Scripting\Debug.h"
void Fruit::OnCreate() {
}

void Fruit::OnUpdate(float deltaTime) {

}
void Fruit::OnPointerDown(PointerEventData& eventData) {
    Duality::Debug::Log("Clicked");
}
void Fruit::Init() {

}
REGISTER_BEHAVIOUR(Fruit)
