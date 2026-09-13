#pragma once

#include <vector>

// Lightweight runtime data for one match-3 level. The indices deliberately
// point into the shared config assets: TreeIndex -> TreesConfigSO::TreeSprites,
// and each FruitTypeIndices entry -> FruitConfigSO's normal/outline pair.
struct LevelData {
    int Width = 4;
    int Height = 4;
    int TreeIndex = 0;
    // Row-major initial board: index = y * Width + x. A negative value can
    // later represent an empty cell when the spawning/falling logic is added.
    std::vector<int> FruitTypeIndices;
};
