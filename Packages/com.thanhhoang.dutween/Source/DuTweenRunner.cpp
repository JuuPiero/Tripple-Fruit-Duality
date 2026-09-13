#include "DuTweenRunner.h"

#include "DuTween.h"
#include "ScriptRegistration.h"

void DuTweenRunner::OnUpdate(float deltaTime) { DuTween::Tween::Update(deltaTime); }
void DuTweenRunner::OnDestroy() { DuTween::Tween::Clear(); }

REGISTER_BEHAVIOUR(DuTweenRunner)
