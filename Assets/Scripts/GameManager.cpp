#include "GameManager.h"

#include "ScriptRegistration.h"
#include "DualityEngine\Scripting\ScriptScene.h"
void GameManager::OnCreate()
{
    FruitConfigSO *config = ScriptScene::LoadScriptableObject<FruitConfigSO>(FruitConfig.Guid);
}

void GameManager::OnUpdate(float deltaTime)
{
}

REGISTER_BEHAVIOUR(GameManager)
