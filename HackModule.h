#pragma once
#include <Windows.h>
#include "GameSetup.h"
#include "InGameItemCollector.h"
#include "exports.h"

class HackModule {
public:
    HackModule(HMODULE hModule);
    void Initialize();
    void Deinitialize();
    DWORD WINAPI InitialiseKeyShortcuts();
    DWORD WINAPI InitialiseConsoleForDebugging();

private:
    HMODULE hModule;
    int targetDllASLR;    
    BOOL _escapseKeyReleased = false;
    //GameMap gameMap;
    InGameItemCollector _itemCollector;
    GameSetup _gameSetup;
};