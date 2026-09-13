#pragma once

#include <vector>

#include "DualityEngine/Reflection/Field.h"
#include "DualityEngine/Scripting/ScriptableObject.h"

// Shared catalogue for every fruit type in the match-3 board. Entries at the
// same index form one pair: NormalSprites[i] is the idle fruit and
// OutlineSprites[i] is its selected/outlined visual.
class FruitConfigSO : public Duality::ScriptableObject {
public:
    std::vector<Duality::AssetRef> NormalSprites;
    std::vector<Duality::AssetRef> OutlineSprites;

    static std::vector<Duality::FieldHandle> Fields() {
        return {
            Duality::MakeField("Normal Sprites", &FruitConfigSO::NormalSprites),
            Duality::MakeField("Outline Sprites", &FruitConfigSO::OutlineSprites),
        };
    }
};
