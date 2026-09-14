#include "Tree.h"

#include "ScriptRegistration.h"

void Tree::OnCreate() {
    ClearChildren();
    // GetTransform().GetWorldPosition()
}

void Tree::OnUpdate(float deltaTime) {
}
void Tree::Init(int treeIndex) {
    (void)treeIndex;
}

REGISTER_BEHAVIOUR(Tree)
