#pragma once

#include "DualityEngine/Scene/Behaviour.h"
#include "DualityEngine/Scene/PointerEventHandlers.h"
using namespace Duality;

class Fruit : public Duality::Behaviour, public IPointerDownHandler {
public:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void OnPointerDown(PointerEventData& eventData) override;
    void Init();
};
