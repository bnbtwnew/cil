#pragma warning( disable : 6031 )
#include "DLLMain.h"
//#include "Common.h"
//#include "InGameCollectItem.h"
//#include <detours.h>
#include <tchar.h>
//#include <iostream>
//#include <fstream>
//#include <io.h>
//#include <fcntl.h>
using namespace std;

//VOID myPrintf(const char* const Format, Args ... args)
//VOID myPrintf(const char* formattedString);
int AddItem(DWORD itemID, DWORD firstArg, DWORD fourthArg, DWORD quantity);
VOID AddBundleItems();
VOID TriggerAnFull();
VOID TriggerStartGame();
VOID TriggerButton1Click();
VOID ToggleCheckbox(int tabOrder, byte value);
VOID ToggleOnOffCheckbox(ChucNangCheckboxTabOrder tabOrder);

std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while (1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

VOID myPrintf(string formattedString) {
    //va_list _ArgList;
    //printf(formattedString);
     // string_format(Format, string_format);
    ofstream logFile("my_log.txt", std::ios_base::app);
    logFile << formattedString;
    logFile.close();
    
}

int escapeKeyPressCounter = 0;
BOOL escapseKeyReleased = false;
VOID InitialiseKeyShortcuts(PVOID lpParameter) {
    // Sleep 3 seconds to wait for target module dll loaded
    Sleep(3000);

    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    
    printf("InitialiseKeyShortcuts %s base = %x\n", TARGET_MODULE_DLL, dllBase);
    myPrintf(string_format("InitialiseKeyShortcuts %s base = %x\n", TARGET_MODULE_DLL, dllBase));

    int aslrOffset = dllBase - 0x400000;

    while (true)
    {
        // if we use (GetAsyncKeyState(VK_ESCAPE) & 0x8000) alone, it will trigger many times during key pressing that 
        // might cause app crashing, hence we handle like this to only call once when key release
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            escapseKeyReleased = true;            
        }
        else {
            if (escapseKeyReleased) {
                escapeKeyPressCounter++;
                myPrintf(string_format("InitialiseKeyShortcuts Escape key press counter %d\n", escapeKeyPressCounter));
                CollectFavouriteInGameItems(aslrOffset);
                escapseKeyReleased = false;
            }            
        }
        
        if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(0x31) & 0x8000) { // Shift 1
            AddBundleItems();
        }
        else if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(0x32) & 0x8000) { // Shift 2
            TriggerStartGame();
        }
        else if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState('A') & 0x8000) { // Left Ctrl A
            ToggleOnOffCheckbox(CHECKBOX_THAU_KINH);
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

VOID InitialiseConsoleForDebugging(PVOID lpParameter)
{
    // Sleep 3 seconds to wait for target module dll loaded
    Sleep(3000);

    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("%s base = %x\n", TARGET_MODULE_DLL, dllBase);
    int aslrOffset = dllBase - 0x400000;

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
        cout << "\t7. An Full TOP_RIGHT\n";
        cout << "\t8. An Full BOTTOM_LEFT\n";
        cout << "\t9. An Full BOTTOM_RIGHT\n";
        cout << "\t0. Exit\n";
        cout << "\n";
        cout << "Enter option: ";
        cin.clear();
        cin >> selection;

        switch (selection)
        {
        case 1: 
            AddBundleItems();
            break;
        case 2:
            TriggerAnFull();
            break;
        case 3:
            TriggerStartGame();
            break;
        case 4:
            /*int tabOrder = 8;
            int value = 1;*/
            ToggleOnOffCheckbox(CHECKBOX_RADAR);
            break;
        case 5:
        {
            int tabOrder = 0;
            int isOn = 0;
            cout << "Enter tab order: ";
            cin.clear();
            cin >> tabOrder;
            cout << "Toggling On/Off (1/0): ";
            cin.clear();
            cin >> isOn;
            ToggleCheckbox(tabOrder, isOn);
            break;
        }
        case 6:
        {
            AnFullAtDirection(aslrOffset, TOP_LEFT);
            break;
        }
        case 7:
        {
            AnFullAtDirection(aslrOffset, TOP_RIGHT);
            break;
        }
        case 8:
        {
            AnFullAtDirection(aslrOffset, BOTTOM_LEFT);
            break;
        }
        case 9:
        {
            AnFullAtDirection(aslrOffset, BOTTOM_RIGHT);
            break;
        }
        default:
            printf("Invalid option!\n");
            break;
        }

        cout << "\n";
    } while (selection != 0);

    printf("Exiting...");
    return;
}

VOID AddBundleItems() {    
    int itemIds [] = {
        // these items has the clock icon
        89997, // khien tu dong
        89998, // sieu khien nuoc
        89999, // sieu nhan sam
        100003, // nhay?

        // these items has the smiley face icon
        150654, // kim
        150655, // khien
        150658, // nhan sam
        150659, // phi tieu
        150660, // ca' hop.
        150661, // co` le
        150662, // thau' kinh'
        150663, // giai doc
    };

    // add above items to game (only take effect after logic)
    int totalItems = sizeof(itemIds) / sizeof(itemIds[0]);
    int index = 0;
    int successfulAddedItemCount = 0;
    printf("Start adding bundle of items...\n");

    for (index = 0; index < totalItems; index++) {
        int quantity = itemIds[index];
        int result = AddItem(itemIds[index], 0, 0, quantity);
        if (result > 0) {
            successfulAddedItemCount++;
        }
    }

    printf("Added %d/%d items successfully!\n", successfulAddedItemCount, totalItems);
}

VOID TriggerAnFull() {
    int dllBase = (int) GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("%s base = %x", TARGET_MODULE_DLL, dllBase);
    int eax = dllBase + 0x699390;
    int* ptr1 = (int*)(eax + 0x4BC);
    int* ptr2 = (int*)(*ptr1 + 0xC);
    printf("Current An Full Value before setting = %d\n", *ptr2);
    *ptr2 = 1;

    /*int result = *(DWORD*)(eax + 0x4BC)
    result = *(DWORD*)(result + 0xC);*/
    printf("Current An Full Value fater setting = %d\n", *ptr2);
}

/*
This method we support to eat all items either in section TOP_LEFT/TOP_RIGHT/BOTTOM_LEFT/BOTTOM_RIGHT
*/
VOID AnFullAtDirection(int targetDllASLR, Direction direction) {
    /*int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("AnFullAtDirection %s base = %x\n", TARGET_MODULE_DLL, dllBase);
    int aslrOffset = dllBase - 0x400000;
    targetDllASLR = aslrOffset;*/

    int fromColumn = 0;
    int toColumn = 0;
    int fromRow = 0;
    int toRow = 0;
    switch (direction)
    {
    case TOP_LEFT:
    {
        fromColumn = 0;
        toColumn = MAX_GAME_MAP_COLUMN / 2 + 1;

        fromRow = 0;
        toRow = MAX_GAME_MAP_ROW / 2 + 1;
        break;
    }
    case TOP_RIGHT:
    {
        fromColumn = MAX_GAME_MAP_COLUMN / 2;
        toColumn = MAX_GAME_MAP_COLUMN;

        fromRow = 0;
        toRow = MAX_GAME_MAP_ROW / 2;
        break;
    }
    case BOTTOM_LEFT:
    {
        fromColumn = 0;
        toColumn = MAX_GAME_MAP_COLUMN / 2 + 1;

        fromRow = MAX_GAME_MAP_ROW / 2;
        toRow = MAX_GAME_MAP_ROW;
        break;
    }
    case BOTTOM_RIGHT:
    {
        fromColumn = MAX_GAME_MAP_COLUMN / 2;
        toColumn = MAX_GAME_MAP_COLUMN;

        fromRow = MAX_GAME_MAP_ROW / 2;
        toRow = MAX_GAME_MAP_ROW;
        break;
    }
    default:
        break;
    }

    printf("AnFullAtDirection fromColumn = %d toColumn = %d fromRow = %d toRow = %d\n", fromColumn, toColumn, fromRow, toRow);
    myPrintf(string_format("AnFullAtDirection fromColumn = %d toColumn = %d fromRow = %d toRow = %d\n", fromColumn, toColumn, fromRow, toRow));
    //AnFullToSection(fromColumn, toColumn, fromRow, toRow);
    CollectAllItemsFromRange(targetDllASLR, fromColumn, toColumn, fromRow, toRow);
}

BOOL HasItemAtTile(int targetDllASLR, int column, int row) {
    int hasItem = 0;
    int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;

    //printf("Before HasItemAtTile invoke function pointer with base %x\n", targetDllASLR);
    //hasItem = ((int (*)(int, int, int))_0x00658D38WithASLR)(column, row, 0x1C);

    __asm
    {
    LBL_006ED887:
        mov ecx, 0x1C; 006ED887        mov         ecx, 1C
            mov edx, row; 006ED88C        mov         edx, dword ptr[ebp - 10]
            mov eax, column; 006ED88F        mov         eax, dword ptr[ebp - 0C]
            call _0x00658D38WithASLR; 006ED892        call        00658D38

            ; this line is for debugging purpose.After running the possible output is 1 or 0
            ; 1 means this tile has item, 0 otherwise :D
            mov hasItem, eax
    }

    //printf("After HasItemAtTile invoke function pointer\n");

    return hasItem == 1;
}

int GetItemID(int targetDllASLR, int column, int row) {
    int mapItemID = 0;
    int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;
    __asm {
        mov ecx, 0xA4; 006ED89A        mov         ecx, 0A4
        mov edx, row; 006ED89F        mov         edx, dword ptr[ebp - 10]
        mov eax, column; 006ED8A2        mov         eax, dword ptr[ebp - 0C]
        call _0x00658D38WithASLR; 006ED8A5        call        00658D38
        push eax; 006ED8AA        push        eax
        ; this line is for debugging purpose
        mov mapItemID, eax
    }

    return mapItemID;
}

int GetMysteriousNumber(int targetDllASLR, int column, int row, int itemID) {
    int mysteriousNumber = 0;
    int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;
    __asm {
        mov eax, itemID
        push eax; 006ED8AA        push        eax
        mov ecx, 0x98; 006ED8AB        mov         ecx, 98
        mov edx, row; 006ED8B0        mov         edx, dword ptr[ebp - 10]
        mov eax, column; 006ED8B3        mov         eax, dword ptr[ebp - 0C]
        call _0x00658D38WithASLR; 006ED8B6        call        00658D38
        ; this line is for debugging purpose
        mov mysteriousNumber, eax
    }

    return mysteriousNumber;
}

VOID CollectItemAtTile(int targetDllASLR, int column, int row) {
    int _0x0065ADD0WithASLR = targetDllASLR + 0x0065ADD0;

    try {
        BOOL hasItem = HasItemAtTile(targetDllASLR, column, row);
        //printf("HasItemAtTile (%d, %d) = %d\n", column, row, hasItem);
        if (!hasItem) {
            return;
        }

        int itemID = GetItemID(targetDllASLR, column, row);
        //printf("GetItemID (%d, %d) = %d\n", column, row, itemID);
        int mysteriousNumber = GetMysteriousNumber(targetDllASLR, column, row, itemID);
        //printf("GetMysteriousNumber (%d, %d) = %d\n", column, row, mysteriousNumber);

        // this asm block  will collect the item
        __asm {
            mov eax, itemID
            push eax
            mov eax, mysteriousNumber
            mov ecx, eax; 006ED8BB        mov         ecx, eax
            mov edx, row; 006ED8BD        mov         edx, dword ptr[ebp - 10]
            mov eax, column; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
            call _0x0065ADD0WithASLR; 006ED8C3        call        0065ADD0
        }
        printf("(%d, %d) Found ItemID %d with mysteriousNumber %d\n", column, row, itemID, mysteriousNumber);
    }
    catch (...) {
        printf("CollectItemAtTile (%d, %d) failed with exception!!!\n", column, row);
    }
}

VOID CollectItemAtTile(int targetDllASLR, int column, int row, int itemID, int mysteriousNumber) {
    int _0x0065ADD0WithASLR = targetDllASLR + 0x0065ADD0;

    try {       
        // this asm block  will collect the item
        __asm {
            mov eax, itemID
            push eax
            mov eax, mysteriousNumber
            mov ecx, eax; 006ED8BB        mov         ecx, eax
            mov edx, row; 006ED8BD        mov         edx, dword ptr[ebp - 10]
            mov eax, column; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
            call _0x0065ADD0WithASLR; 006ED8C3        call        0065ADD0
        }
        printf("CollectItemAtTile (%d, %d) Found ItemID %d with mysteriousNumber %d\n", column, row, itemID, mysteriousNumber);
        myPrintf(string_format("CollectItemAtTile (%d, %d) Found ItemID %d with mysteriousNumber %d\n", column, row, itemID, mysteriousNumber));
    }
    catch (...) {
        printf("CollectItemAtTile (%d, %d) failed with exception!!!\n", column, row);
        myPrintf(string_format("CollectItemAtTile (%d, %d) failed with exception!!!\n", column, row));
    }
}

VOID CollectAllItemsFromRange(int targetDllASLR, int fromColumn, int toColumn, int fromRow, int toRow) {
    int validFromColumn = fromColumn < MAX_GAME_MAP_COLUMN ? fromColumn : 0;
    int validToColumn = toColumn <= MAX_GAME_MAP_COLUMN ? toColumn : 0;

    // validate input 0 < fromRow, toRow < MAX_GAME_MAP_ROW
    int validFromRow = fromRow < MAX_GAME_MAP_ROW ? fromRow : 0;
    int validToRow = toRow <= MAX_GAME_MAP_ROW ? toRow : 0;

    int rowCounter = validFromRow; // Local variable for [ebp - 10]   
    for (; rowCounter < validToRow; rowCounter++)
    {
        for (int counter = validFromColumn; counter < validToColumn; counter++)
        {
            int columnCounter = counter; // Local variable for [ebp - 0C]
            CollectItemAtTile(targetDllASLR, columnCounter, rowCounter);
        }
    }
    printf("\n\n");
}

BOOL isCollectFavouriteInGameItemsDone = true;
VOID CollectFavouriteInGameItems(int targetDllASLR) {
    if (!isCollectFavouriteInGameItemsDone) {
        myPrintf("!!!!!CollectFavouriteInGameItems is still in progress, no more proceeding until it's done!!!");
        return;
    }
    isCollectFavouriteInGameItemsDone = false;
    int REMOVED_ITEM_ID = -1;
    int favoriteItems[] = { IN_GAME_ITEM_MAX_WATER, IN_GAME_ITEM_NEEDLE };
    int totalItems = sizeof(favoriteItems) / sizeof(favoriteItems[0]);
    int counter = 0;    

    try {
        for (int row = 0; row < MAX_GAME_MAP_ROW; row++)
        {
            for (int column = 0; column < MAX_GAME_MAP_COLUMN; column++)
            {
                if (!HasItemAtTile(targetDllASLR, column, row)) {
                    myPrintf(string_format("CollectFavouriteInGameItems HasItemAtTile (%d, %d) is false\n", column, row));                    
                    continue;
                }
                int currentItemID = GetItemID(targetDllASLR, column, row);
                for (int i = 0; i < totalItems; i++) {
                    if (currentItemID == favoriteItems[i]) {
                        printf("CollectFavouriteInGameItems found favorite item id %d at (%d, %d)\n", currentItemID, column, row);
                        myPrintf(string_format("CollectFavouriteInGameItems found favorite item id %d at (%d, %d)\n", currentItemID, column, row));
                        //CollectItemAtTile(targetDllASLR, column, row);
                        int mysteriousNumber = GetMysteriousNumber(targetDllASLR, column, row, currentItemID);
                        myPrintf(string_format("CollectFavouriteInGameItems mysteriousNumber %d at (%d, %d)\n", mysteriousNumber, column, row));

                        CollectItemAtTile(targetDllASLR, column, row, currentItemID, mysteriousNumber);

                        // we only want to collect one, not all item of the same kind, hence set invalid item id to not collect again
                        favoriteItems[i] = REMOVED_ITEM_ID;
                        myPrintf(string_format("CollectFavouriteInGameItems removed ItemID %d from favorites!\n", favoriteItems[i]));
                    }
                }

                myPrintf(string_format("CollectFavouriteInGameItems at (%d, %d) currentItemID %d counter = %d\n", column, row, currentItemID, counter++));

            }
        }
    }
    catch (...) {
        printf("CollectFavouriteInGameItems exception!!!\n");
    }

    isCollectFavouriteInGameItemsDone = true;
    printf("\n\n");
}

const char format_string[] = "counter1=%d counter2=%d\n";

VOID AnFullToSection(int fromColumn, int toColumn, int fromRow, int toRow) {
    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("%s base = %x\n", TARGET_MODULE_DLL, dllBase);

    int aslrOffset = dllBase - 0x400000;
    int _0x00658D38WithASLR = aslrOffset + 0x00658D38;
    int _0x0065ADD0WithASLR = aslrOffset + 0x0065ADD0;

    int eaxValue = dllBase + 0x699390;
    int* ptr1 = (int*)(eaxValue + 0x4BC);
    int* ptr2 = (int*)(*ptr1 + 0xC);

    int triggerAnFullBtnAddress = *ptr1;
    int currentHoldingValue = *ptr2;



    // validate input 0 < fromColumn, toColumn < MAX_GAME_MAP_COLUMN
    int validFromColumn = fromColumn < MAX_GAME_MAP_COLUMN ? fromColumn : 0;
    int validToColumn = toColumn <= MAX_GAME_MAP_COLUMN ? toColumn : 0;

    // validate input 0 < fromRow, toRow < MAX_GAME_MAP_ROW
    int validFromRow = fromRow < MAX_GAME_MAP_ROW ? fromRow : 0;
    int validToRow = toRow <= MAX_GAME_MAP_ROW ? toRow : 0;

    printf("AnFullToSection fromColumn = %d toColumn = %d fromRow = %d toRow = %d\n", validFromColumn, validToColumn, validFromRow, validToRow);


    int rowCounter = validFromRow; // Local variable for [ebp - 10]    

    // set current holding value to 1 to trigger An Full logic
    //*ptr2 = 2;

    // TODO: below inline __asm seems not correct, suppose to have 2 for loops but due to my mistake, it somehow
    // only contain 1 for loop, need to fix this by doing manualy 2 for loop in c++ and manually call
    // the inline asm in the inner for loop
    for (; rowCounter < validToRow; rowCounter++)
    {
        for (int counter = validFromColumn; counter < validToColumn; counter++)
        {
            int columnCounter = counter; // Local variable for [ebp - 0C]
            // printf("====> Starting AnFullToSection at (column x row) = (%d, %d)\n", columnCounter, rowCounter);
            int call_0x658D38_ResultBeforeDecrease = 0;
            int call_0x658D38_ResultWithInput_ecx_0xA4 = 0;
            int call_0x658D38_ResultWithInput_ecx_0x98 = 0;
            __asm
            {
                ; mov eax, dword ptr[ebp - 8]; 006ED85E        mov         eax, dword ptr[ebp - 8]
                ; mov eax, dword ptr[eax + 0x4BC]; 006ED861        mov         eax, dword ptr[eax + 4BC]; TForm1.btn1:TAdvGlowButton
                ; cmp currentHoldingValue, 1; 006ED867        cmp         dword ptr[eax + 0C], 1; TAdvGlowButton.FTag:NativeInt
                ; jne LBL_006ED8DA; 006ED86B > jne         006ED8DA

                ; mov eax, dword ptr[ebp - 8]; 006ED86D        mov         eax, dword ptr[ebp - 8]
                ; mov eax, dword ptr[eax + 0x4BC]; 006ED870        mov         eax, dword ptr[eax + 4BC]; TForm1.btn1:TAdvGlowButton
                ; mov dword ptr[triggerAnFullBtnAddress + 0x0C], 2; 006ED876        mov         dword ptr[eax + 0C], 2; TAdvGlowButton.FTag:NativeInt

                ; xor eax, eax; 006ED87D xor eax, eax
                ; mov eax, rowCounter
                ; mov rowCounter, eax; 006ED87F        mov         dword ptr[ebp - 10], eax

                ; LBL_006ED882:
                ; xor eax, eax; 006ED882 xor eax, eax
                    ; mov eax, columnCounter
                    ; mov columnCounter, eax; 006ED884        mov         dword ptr[ebp - 0C], eax

                    LBL_006ED887 :
                mov ecx, 0x1C; 006ED887        mov         ecx, 1C
                    mov edx, rowCounter; 006ED88C        mov         edx, dword ptr[ebp - 10]
                    mov eax, columnCounter; 006ED88F        mov         eax, dword ptr[ebp - 0C]
                    call _0x00658D38WithASLR; 006ED892        call        00658D38

                    ; this line is for debugging purpose.After running the possible output is 1 or 0
                    ; 1 means this tile has item, 0 otherwise :D
                    mov call_0x658D38_ResultBeforeDecrease, eax

                    dec eax; 006ED897        dec         eax
                    jne LBL_006ED8DA; 006ED898 > jne         006ED8C8

                    mov ecx, 0xA4; 006ED89A        mov         ecx, 0A4
                    mov edx, rowCounter; 006ED89F        mov         edx, dword ptr[ebp - 10]
                    mov eax, columnCounter; 006ED8A2        mov         eax, dword ptr[ebp - 0C]
                    call _0x00658D38WithASLR; 006ED8A5        call        00658D38
                    push eax; 006ED8AA        push        eax
                    ; this line is for debugging purpose
                    mov call_0x658D38_ResultWithInput_ecx_0xA4, eax

                    mov ecx, 0x98; 006ED8AB        mov         ecx, 98
                    mov edx, rowCounter; 006ED8B0        mov         edx, dword ptr[ebp - 10]
                    mov eax, columnCounter; 006ED8B3        mov         eax, dword ptr[ebp - 0C]
                    call _0x00658D38WithASLR; 006ED8B6        call        00658D38
                    ; this line is for debugging purpose
                    mov call_0x658D38_ResultWithInput_ecx_0x98, eax

                    mov ecx, eax; 006ED8BB        mov         ecx, eax
                    mov edx, rowCounter; 006ED8BD        mov         edx, dword ptr[ebp - 10]
                    mov eax, columnCounter; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
                    call _0x0065ADD0WithASLR; 006ED8C3        call        0065ADD0
                    LBL_006ED8DA :
                mov eax, eax; 006ED8DA        mov         eax, dword ptr[ebp - 8]
            }

            //printf("<==== Done AnFullToSection at (column x row) = (%d, %d) call_0x658D38_ResultBeforeDecrease = %d call_0x658D38_ResultWithInput_ecx_0xA4 = %d call_0x658D38_ResultWithInput_ecx_0x98 = %d\n\n", columnCounter, rowCounter, call_0x658D38_ResultBeforeDecrease, call_0x658D38_ResultWithInput_ecx_0xA4, call_0x658D38_ResultWithInput_ecx_0x98);
            if (call_0x658D38_ResultBeforeDecrease == 1) { // has item  at this tile
                // this log to print out items collected on the map, based on the result and compare with items displaying on the map
                // we can deduce call_0x658D38_ResultWithInput_ecx_0xA4 is the ITEM_ID
                // 0: Balloon, 124: Needle, 54: Broze coins bag, 55: Silver coin bag, 5: Max water, 12: Water, 2: Shoe, 37: Fast Turtle, 36: Slow Turtle, 35: Owl, 34: UFO, 119: Red face, 212: Eggs basket, 4: Glove
                printf("<==== Collected item AnFullToSection at (column x row) = (%d, %d) call_0x658D38_ResultBeforeDecrease = %d call_0x658D38_ResultWithInput_ecx_0xA4 = %d call_0x658D38_ResultWithInput_ecx_0x98 = %d\n\n", columnCounter, rowCounter, call_0x658D38_ResultBeforeDecrease, call_0x658D38_ResultWithInput_ecx_0xA4, call_0x658D38_ResultWithInput_ecx_0x98);
            }
        }
    }

    // call inline assembly that mimic the code for An Full we disassembled from Interactive Delphi Reconstructor (IDR)
    // We modified a few instructions and keep original instructions in the inline comments for reference
    // The idea of original logic for these instructions is to do 2 for loops (loop through 15 columns and 13 rows) to scan through 
    // all the tiles of the map (15x13) and then for each tile trigger call 0x0065ADD0 to trigger AnFull logic
    /*__asm
    {
        ; mov eax, dword ptr[ebp - 8]           ; 006ED85E        mov         eax, dword ptr[ebp - 8]
        ; mov eax, dword ptr[eax + 0x4BC]       ; 006ED861        mov         eax, dword ptr[eax + 4BC]; TForm1.btn1:TAdvGlowButton
        cmp currentHoldingValue, 1              ; 006ED867        cmp         dword ptr[eax + 0C], 1; TAdvGlowButton.FTag:NativeInt
        jne LBL_006ED8DA                        ; 006ED86B > jne         006ED8DA

        ; mov eax, dword ptr[ebp - 8]           ; 006ED86D        mov         eax, dword ptr[ebp - 8]
        ; mov eax, dword ptr[eax + 0x4BC]       ; 006ED870        mov         eax, dword ptr[eax + 4BC]; TForm1.btn1:TAdvGlowButton
        mov dword ptr[triggerAnFullBtnAddress + 0x0C], 2    ; 006ED876        mov         dword ptr[eax + 0C], 2; TAdvGlowButton.FTag:NativeInt

        xor eax, eax                            ; 006ED87D        xor eax, eax
        mov eax, rowCounter
        ; mov rowCounter, eax                     ; 006ED87F        mov         dword ptr[ebp - 10], eax

    LBL_006ED882:
        xor eax, eax                            ; 006ED882 xor eax, eax
        mov eax, columnCounter
        mov columnCounter, eax                  ; 006ED884        mov         dword ptr[ebp - 0C], eax

    LBL_006ED887:
        mov ecx, 0x1C                           ; 006ED887        mov         ecx, 1C
        mov edx, rowCounter                     ; 006ED88C        mov         edx, dword ptr[ebp - 10]
        mov eax, columnCounter                  ; 006ED88F        mov         eax, dword ptr[ebp - 0C]
        call _0x00658D38WithASLR                ; 006ED892        call        00658D38

        dec eax                                 ; 006ED897        dec         eax
        jne LBL_006ED8C8                        ; 006ED898 > jne         006ED8C8

        mov ecx, 0xA4                           ; 006ED89A        mov         ecx, 0A4
        mov edx, rowCounter                     ; 006ED89F        mov         edx, dword ptr[ebp - 10]
        mov eax, columnCounter                  ; 006ED8A2        mov         eax, dword ptr[ebp - 0C]
        call _0x00658D38WithASLR                ; 006ED8A5        call        00658D38
        push eax                                ; 006ED8AA        push        eax

        mov ecx, 0x98                           ; 006ED8AB        mov         ecx, 98
        mov edx, rowCounter                     ; 006ED8B0        mov         edx, dword ptr[ebp - 10]
        mov eax, columnCounter                  ; 006ED8B3        mov         eax, dword ptr[ebp - 0C]
        call _0x00658D38WithASLR                ; 006ED8B6        call        00658D38

        mov ecx, eax                            ; 006ED8BB        mov         ecx, eax
        mov edx, rowCounter                     ; 006ED8BD        mov         edx, dword ptr[ebp - 10]
        mov eax, columnCounter                  ; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
        call _0x0065ADD0WithASLR                ; 006ED8C3        call        0065ADD0

    LBL_006ED8C8:
        ; We add extra instructions to print counter1 and counter2 for debugging purpose, but somehow it does not appear on console log
        ; mov eax, rowCounter
        ; push columnCounter
        ; push eax
        ; lea eax, format_string
        ; push eax
        ; call printf ; Print the values of counter1 and counter2 for each loop iteration
        ; add esp, 12 ; We are passing 3 arguments to printf, so adjust the stack pointer accordingly

        inc columnCounter                       ; 006ED8C8        inc         dword ptr[ebp - 0C]
        mov eax, columnCounter
        ; this is the inner loop (iterate each column index)
        cmp eax, validToColumn             ; 006ED8CB        cmp         dword ptr[ebp - 0C], 0F
        jne LBL_006ED887                        ; 006ED8CF > jne         006ED887

        inc rowCounter                          ; 006ED8D1        inc         dword ptr[ebp - 10]
        mov eax, rowCounter
        ; this is the outter loop (iterate each row index)
        cmp eax, validToRow                     ; 006ED8D4        cmp         dword ptr[ebp - 10], 0D
        jne LBL_006ED882                        ; 006ED8D8 > jne         006ED882

    LBL_006ED8DA:
        mov eax, eax                            ; 006ED8DA        mov         eax, dword ptr[ebp - 8]
    }*/

}

VOID TriggerStartGame() {
    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("%s base = %x", TARGET_MODULE_DLL, dllBase);
    int eax = dllBase + 0x699390; //0x690000;
    int* ptr1 = (int*)(eax + 0x4AC);
    int* ptr2 = (int*)(*ptr1 + 0xC);
    printf("Current Invicible Value before setting = %d\n", *ptr2);
    *ptr2 = 1;

    /*int result = *(DWORD*)(eax + 0x4BC)
    result = *(DWORD*)(result + 0xC);*/
    printf("Current Invicible Value fater setting = %d\n", *ptr2);
}

/*
    - After running this function and observer the result on GUI, here is below TabOrder 
        0: Chuot bong'
        1: Giet' Leo
        2: Da' bong'
        3: Hoi` sinh
        4: Giet' Trum`
        5: Bong' nuoc'
        6: Khoa' toc' do.
        7: An? bui. cay
        8: Radar
        9: Chuot. nv
        10: Giai? doc.
        12: Mat. na.
        13: Boom full map
        14: Thau' kinh'
        15: Full bong'
        16: Xuyen tuong` (somehow this checkbox cant toggle on/off in code, need to check why!!)
*/
VOID ToggleCheckbox(int tabOrder, byte value) {
    /*
    - From Interactive Delphi Reconstructor, we can tell this method Vcl.StdCtrls.TCheckBox.SetState begin at 0x059924C
    - Attach the app with x32dbg ScyllaHide, get the ASLR for the dll and add with above address, then Ctrl + G to go to that address and set breakpoint
    This breakpoint will be address of SetState at runtime
    - Click on a checkbox on the GUI hack by Quoc Bao you will see it will hit the break point, and you can see the value of eax (this actually the address of Tform1 object)
    Debug eax value from x32dbg
    - eax = 705A9EO with _dwk.dll base = 69A0000 (this eax is inspected inside TCheckBox.SetState at 0x59924E)
    */

    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("%s base = %x", TARGET_MODULE_DLL, dllBase);
    DWORD tform1Address = (dllBase + 0x699390); //0x690000;

    // - mov         eax,dword ptr [eax+460];TForm1.chk15:TCheckBox => An? bui cay (TabOrder = 7)
    // We know that this TabOrder 7 has offset 0x460 => TabOrder 0 = 0x460 - 7 * 4
    int tabOrder0Offset = 0x460 - 7 * 4;
    int checkboxOffset = tabOrder0Offset + tabOrder * 4;
    //((VOID (*)(DWORD, DWORD, DWORD, DWORD))bnbAddItemFunctionAddress)(firstArg, itemID, quantity, fourthArg);
    
    

    try {
        

        /*
        006ef49b         mov        eax, dword [ebp-4]
        006ef49e         mov        eax, dword [eax+0x47c]
        006ef4a4         mov        ecx, dword [eax]
        006ef4a6         call       dword [ecx+0x10c]
        */

        DWORD tCheckBox_SetChecked_Address = 0x599238 + dllBase;

        int** checkboxPtr = (int**)(tform1Address + checkboxOffset);
        int* setSelectedFunctionPointer = (int*)(*checkboxPtr + 0x10c);
        printf("Checkbox ptr: %x setSelected ptr: %x\n", *checkboxPtr, setSelectedFunctionPointer);
        int* eaxValue = *checkboxPtr;

        BYTE currentCheckState = *(char*)(eaxValue + 0x29A);
        

        __asm
        {
            mov         dl, value
            mov         eax, eaxValue
            mov         ecx, [eax]
            call        dword ptr[ecx + 268]
        };

        BYTE afterCheckState = *(char*)(eaxValue + 0x29A);
        printf("Before checkbox state: %d, After state: %d\n", currentCheckState, afterCheckState);

        //void (fpr*)(int*, BYTE)();
        

        //((VOID (*)(int*, BYTE))*setSelectedFunctionPointer)(checkboxPtr, 1);
        //(*(     **(*(eax) + 0x47c)  +   0x10c)  )();
        //int** form1 = (int**)tform1Address;
        //int* checkboxAddress = (int*)(*form1 + checkboxOffset);
        //(VOID (*)(**(*(eax)+0x47c) + 0x10c))();

        //(**(code **)(   **(int **)(param_1 + 0x45c)  + 0x10c    )   )(     *(int **)(param_1 + 0x45c), 0   );
        //((VOID (*)(int*, BYTE))(**(int **)(tform1Address + checkboxOffset) + 0x10c))(*(int **)(tform1Address + checkboxOffset),0);
        
        
        //((VOID (*)(int*, BYTE))tCheckBox_SetChecked_Address)(*(int**)(tform1Address + checkboxOffset), 0);



       // printf("tform1 address value = %x\n", tform1Address);
       // //int* checkboxPtr = (int*)(tform1Address + checkboxOffset);
       // printf("checkboxPtr value = %x\n", *checkboxPtr);
       // int* ptr2 = (int*)(*checkboxPtr + 0x10C);
       // printf("TCheckBox.SetChecked address = %x\n", *ptr2);
       // ((VOID (*)(DWORD, BYTE))*ptr2)(*checkboxPtr, value);
    }
    catch (...) {
        printf("Toggle checkbox failed with exception!!!\n");
    }

    //printf("Toggled checkbox taborder %d to %d\n", tabOrder, afterCheckState);
}

VOID ToggleOnOffCheckbox(ChucNangCheckboxTabOrder tabOrder) {
    int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
    printf("%s base = %x", TARGET_MODULE_DLL, dllBase);
    DWORD tform1Address = (dllBase + 0x699390);

    int tabOrder0Offset = 0x460 - 7 * 4;
    int checkboxOffset = tabOrder0Offset + tabOrder * 4;

    try {


        /*
        006ef49b         mov        eax, dword [ebp-4]
        006ef49e         mov        eax, dword [eax+0x47c]
        006ef4a4         mov        ecx, dword [eax]
        006ef4a6         call       dword [ecx+0x10c]
        */

        DWORD tCheckBox_SetChecked_Address = 0x599238 + dllBase;

        int** checkboxPtr = (int**)(tform1Address + checkboxOffset);
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

    //printf("Toggled checkbox taborder %d to %d\n", tabOrder, afterCheckState);
}

VOID TriggerButton1Click() {
    // start from 0x6EE8BC
    /*  
        sub_6EE8BC
    .text:006EE8BC                 push    ebp
    .text:006EE8BD                 mov     ebp, esp
    .text:006EE8BF                 add     esp, 0FFFFFFF8h
    .text:006EE8C2                 mov     [ebp+var_8], edx
    .text:006EE8C5                 mov     [ebp+var_4], eax
    .text:006EE8C8                 mov     eax, 3Ch ; '<'
    .text:006EE8CD                 call    sub_65AEEC
    .text:006EE8D2                 pop     ecx
    .text:006EE8D3                 pop     ecx
    .text:006EE8D4                 pop     ebp
    .text:006EE8D5                 retn
    .text:006EE8D5 sub_6EE8BC      endp
    */
    //int dllBase = (int)GetModuleHandle(_T("_DWK.dll"));
    //printf("_DWK.dll base = %x", dllBase);
    //int callAddress = dllBase + 0x65AEEC;
    //// TODO: need to hook and find value of edx too...
    //__asm
    //{

    //    mov     eax, 3Ch;
    //    mov ecx, power; Get second argument
    //    shl eax, cl; EAX = EAX * (2 to the power of CL)
    //}
}

int AddItem(DWORD itemID, DWORD firstArg, DWORD fourthArg, DWORD quantity) {
    /*printf("Start adding item... for itemID = %d", itemID);
    printf("hihi");*/
    int result = 0;
    try {
        DWORD bnbAddItemFunctionAddress = 0x79275a;
        //DWORD quantity = itemID;
        result = ((int (*)(DWORD, DWORD, DWORD, DWORD))bnbAddItemFunctionAddress)(firstArg, itemID, quantity, fourthArg);
        //                      ==========     --> addr of the function to call
        //        =============                --> type of the function to call
        //       =========================     --> ... we get a ptr to that fct
        //      =============================  --> ... and we call the function
        printf("Added item with result: %d\n", result);        
    }
    catch (...) {
        printf("Added item failed with exception!!!\n");
    }

    //printf("========================================\n\n");
    return result;
}


BOOL WINAPI DllMain(HMODULE hModule,
                    DWORD  ul_reason_for_call,
                    LPVOID lpReserved
                   )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);                       
            AllocConsole();            
            
            SetConsoleTitleW(L"NEW BNB Hack Experiment ^_^");
            freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
            freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
            freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
                     
            printf("New BNB TW Hack Experiement Loaded! \n");            
            
            //CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(InitialiseConsoleForDebugging), (PVOID)hModule, NULL, NULL);
                        
            CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(InitialiseKeyShortcuts), (PVOID)hModule, NULL, NULL);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            printf("New BNB TW Hack Experiement Unloaded! \n");
            FreeConsole();
            break;
        }
    }

    return TRUE;
}