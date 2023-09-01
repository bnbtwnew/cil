#include "HackModule.h"
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include "GameUtils.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "GameNotificationService.h"

#include "Detours/include/detours.h"
#include "MyLic.h"
#include "NTPClient.h"

#pragma comment(lib, "Detours/lib/detours.lib")
//#pragma comment(lib, "detoured.lib")
//#pragma comment(lib, "nmco3.lib")

// Remember to add Add CURL_STATICLIB to Properties -> C/C++ -> Proprocessors because we are using staic for libcurl and zlib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "curl/lib/libcurl.lib")
#pragma comment(lib, "curl/lib/zlib.lib")

using namespace std;

void DetoursExample();

HackModule::HackModule(HMODULE hModule) : hModule(hModule), _itemCollector(0), _gameSetup(0), _inGamePlaying() {}

DWORD WINAPI StaticInitialiseCheckLicense(PVOID lpParameter) {
    MyLic lic = MyLic();
    lic.CheckLicense();

    HackModule* instance = reinterpret_cast<HackModule*>(lpParameter);
    instance->InitialiseWatchdogTimerThread();
    return 0;
}


DWORD WINAPI StaticInitialiseKeyShortcuts(PVOID lpParameter) {
    HackModule* instance = reinterpret_cast<HackModule*>(lpParameter);
    instance->InitialiseKeyShortcuts();

    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    log_debug("StaticInitialiseKeyShortcuts%s base = %x\n", TARGET_MODULE_DLL, dllBase);
    printf("printf StaticInitialiseKeyShortcuts%s base = %x\n", TARGET_MODULE_DLL, dllBase);

    return 0;
}

DWORD WINAPI StaticInitialiseConsoleForDebugging(PVOID lpParameter) {
    HackModule* instance = reinterpret_cast<HackModule*>(lpParameter);
    instance->InitialiseConsoleForDebugging();

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
    /*GameNotificationService::Notification n = GameNotificationService::Notification("hihi");
    GameNotificationService::SendNotification(n);*/

    //CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(StaticInitialiseConsoleForDebugging), this, NULL, NULL);
    
    CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(StaticInitialiseKeyShortcuts), this, NULL, NULL);
    
    MyLic lic = MyLic();
    lic.PersistMachinceIdToFile();
    CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(StaticInitialiseCheckLicense), this, NULL, NULL);
}

void HackModule::Deinitialize() {
    FreeConsole();
}

DWORD WINAPI HackModule::InitialiseKeyShortcuts() {
    Sleep(3000);     
    int dllBase = GameUtils::GetTargetModuleDllBase();// (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    log_debug("HackModule::InitialiseKeyShortcuts %s base = %x\n", TARGET_MODULE_DLL, dllBase);
    targetDllASLR = dllBase - TARGET_MODULE_DLL_STATIC_BASE_ADDRESS;
    _itemCollector.UpdateDllASLR(targetDllASLR);
    _gameSetup.UpdateDllASLR(targetDllASLR);
    

    DetoursExample();

    while (true)
    {
#ifndef LICENSE_BUILD
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
#endif // !LICENSE_BUILD        

#ifdef LICENSE_BUILD
        // Add bundle items
        if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(0x31) & 0x8000) { // Shift 1            
            _gameSetup.AddBundleItems();
        }

        // toggle player moving effect
        if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(0x32) & 0x8000) { // Shift 2
            _shiftF2KeyReleased = true;
        }
        else {
            if (_shiftF2KeyReleased) {
                _inGamePlaying.TogglePlayerMovingEffectMode();
                _shiftF2KeyReleased = false;
            }
        }

        // Set current player index in the waiting room
        if (GetAsyncKeyState('P') & GetAsyncKeyState(0x31) & 0x8000) { // P 1
            _inGamePlaying.SetYourPlayerIndex(0);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x32) & 0x8000) { // P 2
            _inGamePlaying.SetYourPlayerIndex(1);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x33) & 0x8000) { // P 3
            _inGamePlaying.SetYourPlayerIndex(2);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x34) & 0x8000) { // P 4
            _inGamePlaying.SetYourPlayerIndex(3);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x35) & 0x8000) { // P 5
            _inGamePlaying.SetYourPlayerIndex(4);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x36) & 0x8000) { // P 6
            _inGamePlaying.SetYourPlayerIndex(5);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x37) & 0x8000) { // P 7
            _inGamePlaying.SetYourPlayerIndex(6);
        }
        else if (GetAsyncKeyState('P') & GetAsyncKeyState(0x38) & 0x8000) { // P 8
            _inGamePlaying.SetYourPlayerIndex(7);
        }
#endif // LICENSE_BUILD

        
        
        if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState('A') & 0x8000) { // Left Ctrl A
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


int (*dNMCOGetMyStatus)();
int My_NMCOGetMyStatus();

int (*dNMCOGetFriendList)(int, int, int);
int My_NMCOGetFriendList(int a1, int a2, int a3);

int (*dNMCOLogin)(char*, char*, char*, int, int, int);
int My_NMCOLogin(char* Source, char* a2, char* a3, int a4, int a5, int a6);

int (*dAddItem)(DWORD, DWORD, DWORD, DWORD);
int My_AddItem(DWORD, DWORD, DWORD, DWORD);

// lua api
int (*dluaL_LoadBuffer)(int*, const char*, size_t, const char*);
int My_luaL_LoadBuffer(int*, const char*, size_t, const char*);

// it seems this one not being called
int (*dluaB_dofile)(int*, const char*);
int My_luaB_dofile(int*, const char*);

// #STR: "CItemSkillInfo::IsUserItemSkill"
char (*dxrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill)(int, int, int*);
char My_xrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill(int, int, int*);

void (*dlua_pushstring)(int*, char*);
void My_lua_pushstring(int*, char*);

int My_AddItem(DWORD arg0, DWORD itemID, DWORD quantity, DWORD arg3) {
    printf("My_AddItem reached!!!\n");
    int status = My_AddItem(arg0, itemID, quantity, arg3);
    printf("My_AddItem AddItem = %d\n", status);
    return status;
}

int My_NMCOGetMyStatus() {
    printf("My_NMCOGetMyStatus reached!!!\n");
    int status = dNMCOGetMyStatus();
    printf("My_NMCOGetMyStatus NMCOGetMyStatus = %d\n", status);
    return status;
}

int My_NMCOGetFriendList(int a1, int a2, int a3) {
    printf("My_NMCOGetFriendList reached!!!\n");
    int result = dNMCOGetFriendList(a1, a2, a3);
    printf("My_NMCOGetFriendList NMCOGetFriendList result = %d\n", result);
    return result;
}

int My_NMCOLogin(char* Source, char* a2, char* a3, int a4, int a5, int a6) {
    printf("My_NMCOLogin reached!!!\n");
    int result = dNMCOLogin(Source, a2, a3, a4, a5, a6);
    printf("My_NMCOLogin NMCOLogin result = %d\n", result);
    return result;
}

int __cdecl My_luaL_loadbuffer(int* lua_State, const char* buff, size_t sz, const char* description) {
    printf("My_luaL_loadbuffer reached with description: %s!!!\n", description);
    /*if (strlen(buff) == 5 && strcmp(buff, "LuaQ") == 0) {
        printf("\tThis buffer is lua bytes, not file name");
    }
    else {*/
        printf("\t==> lua file name: %s\n", description);
        
    //}

    std::ofstream outfile(".\\lua_dumped\\" + GameUtils::FormatString("%s", description), std::ofstream::binary);
    outfile.write(buff, sz);
    outfile.close();

    int result = dluaL_LoadBuffer(lua_State, buff, sz, description);
    printf("My_luaL_loadbuffer result = %d!!!\n", result);
    return result;
}

int __cdecl  My_luaB_dofile(int* lua_State, const char* fileName) {
    printf("My_luaB_dofile reached file name: %s!!!\n", fileName);
    int result = dluaB_dofile(lua_State, fileName);
    printf("My_luaB_dofile result = %d!!!\n", result);
    return result;
}

char My_xrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill(int arg1, int arg2, int* arg3) {
    printf("My_xrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill reached: %d %d!!!\n", arg1, arg2);
    char result = dxrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill(arg1, arg2, arg3);    
    printf("My_xrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill result = %c!!!\n", result);
    return result;
}

// this working fine, something it's crashing the app, for debugging purpose to see what function Lua is using in our app
void __cdecl My_lua_pushstring(int* lua_state, char* name) {
    printf("My_lua_pushstring reached with name: %s\n", name);
    //lua_pushstring_logfile(lua_state, name);
    std::ofstream logfile(".\\lua_dumped\\pushstring.txt", std::ios_base::app);
    logfile << name << "\n";
    logfile.close();
}

//typedef BOOL (WINAPI* ShowWindowType)(CWnd*, int);
//ShowWindowType OriginalShowWindow = nullptr;
//BOOL WINAPI HookedShowWindow(CWnd* pWnd, int nCmdShow) {
//    WINAPI result = OriginalShowWindow(pWnd, nCmdShow);
//    printf("HookedShowWindow nCmdShow = %d result = %d\n", nCmdShow, result);
//
//    // Call the original ShowWindow function
//    return result;
//}

VOID DetoursExample() {
    int dllBase = (int)GetModuleHandle(_T("nmco3.dll"));
    log_debug("HackModule::InitialiseConsoleForDebugging %s base = %x\n", "nmco3.dll", dllBase);
    int nmco3ASLR = dllBase - 0x10001000;//TARGET_MODULE_DLL_STATIC_BASE_ADDRESS;
    int NMCOGetMyStatusAddress = nmco3ASLR + 0x10010B10;
    dNMCOGetMyStatus = (int(*)())NMCOGetMyStatusAddress;

    int NMCOGetFriendListStatusAddress = nmco3ASLR + 0x100109C0;
    dNMCOGetFriendList = (int(*)(int, int, int))NMCOGetFriendListStatusAddress;

    int NMCOLoginAddress = nmco3ASLR + 0x10010730;
    dNMCOLogin = (int(*)(char*, char*, char*, int, int, int))NMCOLoginAddress;

    dAddItem = (int (*)(DWORD, DWORD, DWORD, DWORD))0x79275a;

    //dluaL_LoadBuffer = (int (*)(int*, const char*, size_t, const char*))0xAD8750;
    // dxrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill = (char(*)(int, int, int*))0x0044D4BE;

    // after testing, this seems not being called
    // dluaB_dofile = (int (*)(int*, const char*))0x00ADA090;
    //dlua_pushstring = (void (*)(int*, char*))0xAD7400;
    

   /* DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)dNMCOGetMyStatus, My_NMCOGetMyStatus);
    if (DetourTransactionCommit() == NO_ERROR)
        printf("DetoursExample NMCOGetMyStatus() detoured successfully\n");
    else 
        printf("DetoursExample NMCOGetMyStatus() detoured failed\n");

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)dNMCOGetFriendList, My_NMCOGetFriendList);
    if (DetourTransactionCommit() == NO_ERROR)
        printf("DetoursExample NMCOGetFriendList() detoured successfully\n");
    else 
        printf("DetoursExample NMCOGetFriendList() detoured failed\n");*/

    // this one workingn fine, able to dump lua file plain text, not compiled one
    /*DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)dluaL_LoadBuffer, My_luaL_loadbuffer);
    if (DetourTransactionCommit() == NO_ERROR)
        printf("DetoursExample dluaL_LoadBuffer() detoured successfully\n");
    else
        printf("DetoursExample dluaL_LoadBuffer() detoured failed\n");*/

    //DetourTransactionBegin();
    //DetourUpdateThread(GetCurrentThread());
    //DetourAttach(&(PVOID&)dxrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill, My_xrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill);
    //if (DetourTransactionCommit() == NO_ERROR)
    //    printf("DetoursExample dxrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill() detoured successfully\n");
    //else
    //    printf("DetoursExample dxrefs_5_sub_44D4BE_CItemSkillInfo_IsUserItemSkill() detoured failed\n");

   /* DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)dluaB_dofile, My_luaB_dofile);
    if (DetourTransactionCommit() == NO_ERROR)
        printf("DetoursExample dluaB_dofile() detoured successfully\n");
    else
        printf("DetoursExample dluaB_dofile() detoured failed\n");*/

    // working fine
    //DetourTransactionBegin();
    //DetourUpdateThread(GetCurrentThread());
    //DetourAttach(&(PVOID&)dlua_pushstring, My_lua_pushstring);
    //if (DetourTransactionCommit() == NO_ERROR)
    //    printf("DetoursExample dlua_pushstring() detoured successfully\n");
    //else
    //    printf("DetoursExample dlua_pushstring() detoured failed\n");

    // Working fine, but this method is called so many times hence it might crash
    // DetourTransactionBegin();
    // DetourUpdateThread(GetCurrentThread());
    // DetourAttach(&(PVOID&)dAddItem, My_AddItem);
    // if (DetourTransactionCommit() == NO_ERROR)
    //     printf("DetoursExample AddItem() detoured successfully\n");
    // else
    //     printf("DetoursExample AddItem() detoured failed\n");

    /*OriginalShowWindow = (ShowWindowType)GetVTableFunctionAddress(&CWnd::ShowWindow);
    if (OriginalShowWindow) {
        LONG result = DetourTransactionBegin();
        result |= DetourUpdateThread(GetCurrentThread());
        result |= DetourAttach(&(PVOID&)OriginalShowWindow, HookedShowWindow);
        result |= DetourTransactionCommit();

        if (result == NO_ERROR) {
            printf("DetoursExample CWnd::ShowWindow() detoured successfully\n");
        } else {
            printf("DetoursExample CWnd::ShowWindow() detoured failed\n");
        }
    }*/
    
}

DWORD WINAPI HackModule::InitialiseWatchdogTimerThread() {
    Sleep(3000);
    log_debug("HackModule::InitialiseWatchdogTimerThread... \n");
    while (true)
    {
#ifdef LICENSE_BUILD
        _inGamePlaying.UpdateMovingEffectAndPlusEffect();
#endif // LICENSE_BUILD

        Sleep(1000);
    }
}

DWORD WINAPI HackModule::InitialiseConsoleForDebugging()
{
    // Sleep 3 seconds to wait for target module dll loaded
    Sleep(3000);

    //DetoursExample();

    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    log_debug("HackModule::InitialiseConsoleForDebugging %s base = %x\n", TARGET_MODULE_DLL, dllBase);
    targetDllASLR = dllBase - TARGET_MODULE_DLL_STATIC_BASE_ADDRESS;
    _itemCollector.UpdateDllASLR(targetDllASLR);
    _gameSetup.UpdateDllASLR(targetDllASLR);    

    // Working fine
    //DWORD itemID = 0;
    //DWORD firstArg = 0;
    //DWORD fourthArg = 0;
    //DWORD quantity = 0;
    //do {
    //    cout << "Enter Item ID to add: ";
    //    cin.clear();
    //    //cin.ignore(99999999, '\n');
    //    cin >> itemID;

    //    cout << "Enter first arg: ";
    //    cin.clear();
    //    //cin.ignore(99999999, '\n');
    //    cin >> firstArg;

    //    cout << "Enter fourth arg: ";
    //    cin.clear();
    //    //cin.ignore(99999999, '\n');
    //    cin >> fourthArg;

    //    cout << "Enter quantity: ";
    //    cin.clear();
    //    //cin.ignore(99999999, '\n');
    //    cin >> quantity;

    //    //cin.clear();
    //    AddItem(itemID, firstArg, fourthArg, quantity);
    //    
    //    //printf("Sleeping for 4secs.. \n");
    //    //Sleep(4000);
    //    //printf("Slept for 4secs. \n");
    //} while (itemID != 0);


    int selection = -1;
    do {
        cout << "New BnB Hack Experiment: \n";
        cout << "\t1. Add a whole bundle of items\n";
        cout << "\t2. Trigger An Full\n";
        cout << "\t3. Trigger Start Game\n";
        cout << "\t4. Toggle Radar\n";
        cout << "\t5. Toggle Checkbox\n";
        cout << "\t6. An Full TOP_LEFT\n";
        cout << "\t7. Check Game State\n";
        cout << "\t8. Collect favorite items\n";
        cout << "\t9. Find item by ID\n";
        cout << "\t10. Add Item by ID\n";
        cout << "\t11. Find all valid Items ID\n";
        cout << "\t12. Experiment Mua Nhanh \n";
        cout << "\t13. Bong mo den \n";
        cout << "\t14. Retrieve username \n";        
        cout << "\t15. Enumerate pointers for Object at address\n";
        cout << "\t0. Exit\n";
        cout << "\n";
        cout << "Enter option: ";
        cin.clear();
        cin >> selection;

        switch (selection)
        {
        case 1:
            _gameSetup.AddBundleItems();
            break;
        case 2:
            //TriggerAnFull();
            break;
        case 3:
            //TriggerStartGame();
            break;
        case 4:
            /*int tabOrder = 8;
            int value = 1;*/
            //ToggleOnOffCheckbox(CHECKBOX_RADAR);
            break;
        case 5:
        {
            /*int tabOrder = 0;
            int isOn = 0;
            cout << "Enter tab order: ";
            cin.clear();
            cin >> tabOrder;
            cout << "Toggling On/Off (1/0): ";
            cin.clear();
            cin >> isOn;
            ToggleCheckbox(tabOrder, isOn);*/
            break;
        }
        case 6:
        {
            //AnFullAtDirection(aslrOffset, TOP_LEFT);
            break;
        }
        case 7:
        {
            int gameState = GameUtils::GetGameState();
            log_debug("HackModule::InitialiseConsoleForDebugging gameState = %x\n", gameState);
            // for debugging purpose
            GameUtils::sub_658a2c_Retrieve_Object_Address_When_GameIsPlaying();
            break;
        }
        case 8:
        {            
            _itemCollector.CollectFavouriteItemsAssemblyVersion();
            break;
        }
        case 9:
        {
            // CA.exe int sub_9a723b(int itemID, int inoutArg1, int inoutArg2, int inoutArg3)
            int itemID = 0;
            cout << "Enter ItemID to looking for: ";
            cin.clear();
            cin >> itemID;

            DWORD* inoutArg1 = 0;
            DWORD* inoutArg2 = 0;
            DWORD* inoutArg3 = 0;
            int* FF9498 = (int*)0xFF9498;
            int FF9498_Value = *FF9498;
            printf("0xFF9498 = %x\n", FF9498_Value);
            printf("Entered ItemID: %d\n", itemID);
            int result = -1;
            /*
            Hook called from:
                0x9a45b0
                0x9a7334
                0x98683f
                0x986472
                0x992171
                0x99208e
                0x988707
                0x77c861
                0x76535a
                0x54e652
                0x9dd67c
                0x9da6bf
                0x9c8175
                0x9d8697
                0xad6046
                0x21113ae8 CA.exe!AIL_close_digital_driver
            */
            __asm {
                mov eax, itemID
                push eax
                mov ecx, FF9498_Value; find Xref of sub_9A459C we find the before enter this routine it set ecx to 0xFF9498
                add     ecx, 0xC                
                mov eax, 0x9a7334
                call eax
                mov result, eax
            };

            /*typedef int (*TargetFunctionType)();
            TargetFunctionType targetFunction = reinterpret_cast<TargetFunctionType>(0x9a7334);
            __asm {
                mov eax, itemID
                push eax
                mov ecx, 0xFF9498; find Xref of sub_9A459C we find the before enter this routine it set ecx to 0xFF9498
                add     ecx, 0xC                
                ;mov eax, 0x9a7334
                call targetFunction
                mov result, eax
            };*/

            //int result = ((int (*)(int))0x9a7334)(itemID);
            printf("Result: %d\n", result);
            break;
        }
        case 10:
        {
            DWORD itemID = 0;
            DWORD firstArg = 0;
            DWORD fourthArg = 0;
            DWORD quantity = 0;
            do {
                cout << "Enter Item ID to add: ";
                cin.clear();
                //cin.ignore(99999999, '\n');
                cin >> itemID;
                quantity = itemID;
                
                //cin.clear();
                _gameSetup.AddItem(itemID, firstArg, fourthArg, quantity);
        
                //printf("Sleeping for 4secs.. \n");
                //Sleep(4000);
                //printf("Slept for 4secs. \n");
            } while (itemID != 0);
            break;
        }
        case 11:
        {
            /*int* FF9498 = (int*)0xFF9498;
            int FF9498_Value = *FF9498;
            printf("0xFF9498 = %x\n", FF9498_Value);                        */
            /*
            Hook called from:
                0x9a45b0
                0x9a7334
                0x98683f
                0x986472
                0x992171
                0x99208e
                0x988707
                0x77c861
                0x76535a
                0x54e652
                0x9dd67c
                0x9da6bf
                0x9c8175
                0x9d8697
                0xad6046
                0x21113ae8 CA.exe!AIL_close_digital_driver
            */
            int itemID = 0;

            // we want to log each valid item to a new line in this file for tracking later as the console buffer is not much to copy all
            std::ofstream logfile("valid_item_ids.txt", std::ios_base::app);
            // loop to 10 million id to ensure scan all possible item id
            for (itemID = 1; itemID < 10000000; itemID++)
            {
                int result = GameUtils::IsSkillItemIDValid(itemID);
                /*__asm {
                    mov eax, itemID
                    push eax
                    mov ecx, FF9498_Value; find Xref of sub_9A459C we find the before enter this routine it set ecx to 0xFF9498
                    add     ecx, 0xC
                    mov eax, 0x9a7334
                    call eax
                    mov result, eax
                };*/

                if (result > 0) { // valid item ID                    
                    logfile << itemID << "\n";
                    printf("Found valid item id: %d\n", itemID);
                }
            }
            printf("Done!\n");
            logfile.close();
            break;
        }
        case 12:
        {
            // This working fine
            // Purpose: When you go to shopping and want to fast buy an item without needing to click buy confirm popup, this will help
            // AdvGDIP.sub_65B524 (from IDR)
            if (GameUtils::isShopping()) {
                // int sub_658a04() {
                //     eax = *(*dword_7055b0 + **dword_70559c);
                //     return eax;
                // }
                // dword_7055b0: 0x000000d0 => *dword_7055b0 = 0x000000d0
                // dword_70559c: 0x00ff9458 => *dword_70559c = 0x00ff9458

                int eax = *(int*)(0x000000d0 + *(int*)0x00ff9458);

                int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
                //    printf("%s base = %x", TARGET_MODULE_DLL, dllBase);
                DWORD tform1Address = (dllBase + 0x699390); //0x690000;

                try {


                    /*
                    006ef49b         mov        eax, dword [ebp-4]
                    006ef49e         mov        eax, dword [eax+0x47c]
                    006ef4a4         mov        ecx, dword [eax]
                    006ef4a6         call       dword [ecx+0x10c]
                    */

                    DWORD tCheckBox_SetChecked_Address = 0x599238 + dllBase;

                    int** checkboxPtr = (int**)(tform1Address + 0x4A0);
                    int* setSelectedFunctionPointer = (int*)(*checkboxPtr + 0x10c);
                    printf("Checkbox ptr: %x setSelected ptr: %x\n", *checkboxPtr, setSelectedFunctionPointer);
                    int* eaxValue = *checkboxPtr;

                    BYTE currentCheckState = *(char*)(eaxValue + 0x29A);
                    BYTE newCheckState = 1 - currentCheckState;
                    printf("Before checkbox state: %d, After state: %d\n", currentCheckState, newCheckState);

                    BOOL toggleOn = newCheckState == 1;
        
                    // next we mimic below assembly call (inside Home.TForm1.chk21Click function) to make asm call ourselves
                    /*
                    006EF499        mov         dl,1
                    006EF49B        mov         eax,dword ptr [ebp-4]
                    006EF49E        mov         eax,dword ptr [eax+47C];TForm1.chk5:TCheckBox
                    006EF4A4        mov         ecx,dword ptr [eax]
                    006EF4A6        call        dword ptr [ecx+10C];TCheckBox.SetChecked
                    */
                    __asm
                    {
                    mov         dl, newCheckState
                    mov         eax, eaxValue
                    mov         ecx, [eax]
                    call        dword ptr[ecx + 268]; 268 = 0x10C
                    };        

                    // After the call, somehow the check state does not persist, hence we need to manually set value for it
                    char* newCheckStatePtr = (char*)(eaxValue + 0x29A); // 00599250        cmp         dl,byte ptr [ebx+29A];TCheckBox.FState:TCheckBoxState
                    *newCheckStatePtr = newCheckState;
                    printf("New check state memory read: %d\n", *newCheckStatePtr);
                }
                catch (...) {
                    printf("Toggle checkbox failed with exception!!!\n");
                }
            }
            break;
        }
        case 13:
        {                        
            _inGamePlaying.UpdateMovingEffectAndPlusEffect();
            break;
        }
        
        case 14:
        {
            // TODO: Read player username            
            // Searching in CheatEngine, for ex. phu3, beside a few places, there are 4 places in nmco3.dll that persistent fixed address no matter what
            // nmco3.dll+4C510, nmco3.dll+4C590, nmco3.dll+4C5B0, nmco3.dll+4C600
            // Checking with Process Explorer tool this dll is not enabled ASLR, hence those address are always fixed, we can read from there to retrieve username
            
            int nmco3BaseAddress = 0x10000000;
            char* username = (char*)(nmco3BaseAddress + 0x4C510);
            printf("username: %s", username);
            break;
        }        
        case 15: {
            GameUtils::EnumerateProperties();
            break;
        }
        default:
            printf("Invalid option!\n");
            break;
        }

        cout << "\n";
    } while (selection != 0);

    printf("Exiting...");
    return 0;
}

extern "C" __declspec(dllexport) void dummy(void) {
    return;
}