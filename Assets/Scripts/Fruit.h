#pragma once

#include "DualityEngine/Scene/Behaviour.h"
#include "DualityEngine/Scene/PointerEventHandlers.h"
#include "DualityEngine\Scene\Components.h"
using namespace Duality;

class Fruit : public Duality::Behaviour, public IPointerDownHandler {
public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void OnPointerDown(PointerEventData& eventData) override;
    void Init();
public:
    SpriteRendererComponent SpriteRenderer;
    
};
