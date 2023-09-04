#pragma once
#include "GameUtils.h"
#include <chrono>
using namespace GameUtils;

class InGameItemCollector {
public:
    // 0: Balloon, 124: Needle, 54: Broze coins bag, 55: Silver coin bag, 5: Max water, 12: Water, 2: Shoe, 37: Fast Turtle, 36: Slow Turtle, 35: Owl, 34: UFO, 119: Red face, 212: Eggs basket, 4: Glove
    enum IN_GAME_MAP_ITEM {
        IN_GAME_ITEM_BALLOON = 0,
        IN_GAME_ITEM_SHOE = 2,
        IN_GAME_ITEM_GLOVE = 4,
        IN_GAME_ITEM_MAX_WATER = 5,
        IN_GAME_ITEM_SLOW_TURTLE = 36,
        IN_GAME_ITEM_FAST_TURTLE = 37,
        IN_GAME_ITEM_RED_FACE = 119,
        IN_GAME_ITEM_DART = 122,
        IN_GAME_ITEM_NEEDLE = 124,
    };

    const int MAX_GAME_MAP_COLUMN = 15; // 0xF
    const int MAX_GAME_MAP_ROW = 13; // 0xD    
    InGameItemCollector(int targetDllASLR);
    void UpdateDllASLR(int aslrOffset);
    void CollectFavouriteItems();
    void CollectFavouriteItemsAssemblyVersion();
    void CheckFastTurtles();

private:
    int targetDllASLR;    
    std::chrono::steady_clock::time_point _lastCollectedFavoriteItemsTimePoint = std::chrono::steady_clock::now();
    void CollectItemAtTile(MapPoint point);
    void CollectItemAtTile(MapPoint point, int itemID, int mysteriousNumber);
    bool _checkingFastTurtlesDone = true;
    //void AnFullToSection(int fromColumn, int toColumn, int fromRow, int toRow);
    //void AnFullAtDirection(int targetDllASLR, Direction direction);
};