#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
//#include <stdio.h>
//#include <stdint.h>
//#include <intrin.h>

#include "exports.h"
#include "Utils.h"

#pragma intrinsic(_ReturnAddress)


BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
enum ChucNangCheckboxTabOrder
{
    CHECKBOX_CHUOT_BONG = 0,
    CHECKBOX_GIET_LEO = 1,
    CHECKBOX_DA_BONG = 2,
    CHECKBOX_HOI_SINH = 3,
    CHECKBOX_GIET_TRUM = 4, // chk7
    CHECKBOX_BONG_NUOC = 5,
    CHECKBOX_KHOA_TOC_DO = 6,
    CHECKBOX_AN_BUI_CAY = 7,
    CHECKBOX_RADAR = 8,
    CHECKBOX_CHUOT_NHAN_VAT = 9,
    CHECKBOX_GIAI_DOC = 10,
    CHECKBOX_MAT_NA = 12, // chk3
    CHECKBOX_BOOM_FULL_MAP = 13,
    CHECKBOX_THAU_KINH = 14, // chk5
    CHECKBOX_FULL_BONG = 15,
    CHECKBOX_XUYEN_TUONG = 16
};

enum Direction {
    TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

// 0: Balloon, 124: Needle, 54: Broze coins bag, 55: Silver coin bag, 5: Max water, 12: Water, 2: Shoe, 37: Fast Turtle, 36: Slow Turtle, 35: Owl, 34: UFO, 119: Red face, 212: Eggs basket, 4: Glove
enum IN_GAME_MAP_ITEM {
    IN_GAME_ITEM_BALLOON = 0,
    IN_GAME_ITEM_SHOE = 2,
    IN_GAME_ITEM_GLOVE = 4,
    IN_GAME_ITEM_MAX_WATER = 5,
    IN_GAME_ITEM_FAST_TURTLE = 37,
    IN_GAME_ITEM_RED_FACE = 119,
    IN_GAME_ITEM_DART = 122,
    IN_GAME_ITEM_NEEDLE = 124,
};

int MAX_GAME_MAP_COLUMN = 15; // 0xF
int MAX_GAME_MAP_ROW = 13; // 0xD

VOID AnFullToSection(int fromColumn, int toColumn, int fromRow, int toRow);
VOID AnFullAtDirection(int targetDllASLR, Direction direction);

BOOL HasItemAtTile(int targetDllASLR, int column, int row);
int GetItemID(int targetDllASLR, int column, int row);
int GetMysteriousNumber(int targetDllASLR, int column, int row, int itemID);
VOID CollectAllItemsFromRange(int targetDllASLR, int fromColumn, int toColumn, int fromRow, int toRow);
VOID CollectFavouriteInGameItems(int targetDllASLR);