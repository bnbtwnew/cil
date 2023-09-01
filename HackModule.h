#pragma once
#include <Windows.h>
#include "GameSetup.h"
#include "InGameItemCollector.h"
#include "InGamePlaying.h"
#include "exports.h"

class HackModule {
public:
    HackModule(HMODULE hModule);
    void Initialize();
    void Deinitialize();
    DWORD WINAPI InitialiseKeyShortcuts();
    DWORD WINAPI InitialiseConsoleForDebugging();
    DWORD WINAPI InitialiseWatchdogTimerThread();

private:
    HMODULE hModule;
    int targetDllASLR;    
    BOOL _escapseKeyReleased = false;
    BOOL _shiftF2KeyReleased = false;
    //GameMap gameMap;
    InGameItemCollector _itemCollector;
    InGamePlaying _inGamePlaying;
    GameSetup _gameSetup;
};