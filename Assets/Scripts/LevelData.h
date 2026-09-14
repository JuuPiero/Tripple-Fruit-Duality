#pragma once

#include <vector>

// Lightweight runtime data for one match-3 level. The indices deliberately
// point into the shared config assets: TreeIndex -> TreesConfigSO::TreeSprites,
// and each FruitTypeIndices entry -> FruitConfigSO's normal/outline pair.

struct TreeData {
    int TreeType;
    int Width;
    int Height;
};
struct FruitData {
    int FruitType;
    float PositionX;
    float PositionY;
};

struct LevelData {
    TreeData Tree;
    std::vector<FruitData> Fruits;
};
