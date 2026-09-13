#pragma once

#include <vector>

#include "DualityEngine/Reflection/Field.h"
#include "DualityEngine/Scripting/ScriptableObject.h"

// Catalog of available tree visuals. A LevelData instance stores TreeIndex,
// which selects an item from this list; its board size and fruit layout belong
// to the level rather than to a reusable tree asset.
class TreesConfigSO : public Duality::ScriptableObject {
public:
    std::vector<Duality::AssetRef> TreeSprites;

    static std::vector<Duality::FieldHandle> Fields() {
        return {
            Duality::MakeField("Tree Sprites", &TreesConfigSO::TreeSprites),
        };
    }
};
