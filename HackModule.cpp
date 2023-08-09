#include "HackModule.h"
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include "GameUtils.h"

HackModule::HackModule(HMODULE hModule) : hModule(hModule), _itemCollector(0), _gameSetup(0) {}

DWORD WINAPI StaticInitialiseKeyShortcuts(PVOID lpParameter) {
    HackModule* instance = reinterpret_cast<HackModule*>(lpParameter);
    instance->InitialiseKeyShortcuts();

    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    log_debug("StaticInitialiseKeyShortcuts%s base = %x\n", TARGET_MODULE_DLL, dllBase);
    printf("printf StaticInitialiseKeyShortcuts%s base = %x\n", TARGET_MODULE_DLL, dllBase);

    return 0;
}

void HackModule::Initialize() {
    DisableThreadLibraryCalls(hModule);
    AllocConsole();

    SetConsoleTitleW(L"NEW BNB Hack Experiment ^_^");
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

    printf("New BNB TW Hack Experiement Loaded! \n");

    // Sleep 3 second to wait for modded dll to load so we can get the base
    //Sleep(3000);
    /*int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    log_debug("HackModule::Initialize %s base = %x\n", TARGET_MODULE_DLL, dllBase);
     targetDllASLR = dllBase - TARGET_MODULE_DLL_STATIC_BASE_ADDRESS;
     _itemCollector.UpdateDllASLR(targetDllASLR);
    _gameSetup.UpdateDllASLR(targetDllASLR);*/
    //CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(InitialiseConsoleForDebugging), (PVOID)hModule, NULL, NULL);
    
    CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(StaticInitialiseKeyShortcuts), this, NULL, NULL);
}

void HackModule::Deinitialize() {
    FreeConsole();
}

DWORD WINAPI HackModule::InitialiseKeyShortcuts() {
    Sleep(3000);     
    int dllBase = GameUtils::GetTargetModuleDllBase();// (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    log_debug("HackModule::InitialiseKeyShortcuts %s kk base = %x\n", TARGET_MODULE_DLL, dllBase);
    targetDllASLR = dllBase - TARGET_MODULE_DLL_STATIC_BASE_ADDRESS;
    _itemCollector.UpdateDllASLR(targetDllASLR);
    _gameSetup.UpdateDllASLR(targetDllASLR);

    while (true)
    {
        // if we use (GetAsyncKeyState(VK_ESCAPE) & 0x8000) alone, it will trigger many times during key pressing that 
        // might cause app crashing, hence we handle like this to only call once when key release
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            _escapseKeyReleased = true;
        }
        else {
            if (_escapseKeyReleased) {   
                _itemCollector.CollectFavouriteItemsAssemblyVersion();
                //_itemCollector.CollectFavouriteItems();
                _escapseKeyReleased = false;
            }
        }

        if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(0x31) & 0x8000) { // Shift 1
            _gameSetup.AddBundleItems();
        }
        else if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(0x32) & 0x8000) { // Shift 2
            //TriggerStartGame();
        }
        else if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState('A') & 0x8000) { // Left Ctrl A
            //ToggleOnOffCheckbox(CHECKBOX_THAU_KINH);
        }
        /*
        else if (GetAsyncKeyState(VK_INSERT) & 0x8000) { // INSERT
            AnFullAtDirection(aslrOffset, TOP_LEFT);
        }
        else if (GetAsyncKeyState(VK_HOME) & 0x8000) { // HOME
            AnFullAtDirection(aslrOffset, TOP_RIGHT);
        }
        else if (GetAsyncKeyState(VK_DELETE) & 0x8000) { // DELETE
            AnFullAtDirection(aslrOffset, BOTTOM_LEFT);
        }
        else if (GetAsyncKeyState(VK_END) & 0x8000) { // END
            AnFullAtDirection(aslrOffset, BOTTOM_RIGHT);
        }
        */

        // might adjust this sleep milliseconds lower or higher and observe the situation
        Sleep(50);
    }

}