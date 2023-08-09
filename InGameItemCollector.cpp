#include "InGameItemCollector.h"
#include "GameNotificationService.h"
#include "exports.h"

//using namespace GameUtils;

InGameItemCollector::InGameItemCollector(int targetDllASLR) : targetDllASLR(targetDllASLR) {}

void InGameItemCollector::UpdateDllASLR(int aslrOffset) {
    targetDllASLR = aslrOffset;
}

void InGameItemCollector::CollectFavouriteItems() {
    int REMOVED_ITEM_ID = -1;
    int favoriteItems[] = { IN_GAME_ITEM_MAX_WATER, IN_GAME_ITEM_NEEDLE };
    int totalItems = sizeof(favoriteItems) / sizeof(favoriteItems[0]);
    int counter = 0;
    int totalTurtles = 0;

    int fastTurtleColumn = -1;
    int fastTurtleRow = -1;
    GameNotificationService::Notification foundFastTurtleNotification;

    try {
        for (int row = 0; row < MAX_GAME_MAP_ROW; row++)
        {
            for (int column = 0; column < MAX_GAME_MAP_COLUMN; column++)
            {
                GameUtils::MapPoint point(column, row);
                if (!GameUtils::HasItemAtTile(targetDllASLR, point)) {
                    log_debug("CollectFavouriteInGameItems HasItemAtTile (%d, %d) is false\n", point.column, point.row);
                    //myPrintf(string_format("CollectFavouriteInGameItems HasItemAtTile (%d, %d) is false\n", column, row));
                    continue;
                }
                int currentItemID = GetItemID(targetDllASLR, point);
                for (int i = 0; i < totalItems; i++) {
                    if (currentItemID == IN_GAME_ITEM_FAST_TURTLE) {
                        totalTurtles++;
                        fastTurtleColumn = column;
                        fastTurtleRow = row;
                    }

                    if (currentItemID == IN_GAME_ITEM_SLOW_TURTLE) {
                        totalTurtles++;
                    }

                    if (currentItemID == favoriteItems[i]) {
                        log_debug("CollectFavouriteInGameItems found favorite item id %d at (%d, %d)\n", currentItemID, column, row);                                                
                        int mysteriousNumber = GetMysteriousNumber(targetDllASLR, point, currentItemID);
                        log_debug("CollectFavouriteInGameItems mysteriousNumber %d at (%d, %d)\n", mysteriousNumber, column, row);

                        CollectItemAtTile(point, currentItemID, mysteriousNumber);

                        // we only want to collect one, not all item of the same kind, hence set invalid item id to not collect again
                        favoriteItems[i] = REMOVED_ITEM_ID;
                        log_debug("CollectFavouriteInGameItems removed ItemID %d from favorites!\n", favoriteItems[i]);
                    }
                }                

            }
        }
    }
    catch (...) {
        log_debug("CollectFavouriteInGameItems exception!!!\n");
    }

    // logic to send telegram notification if found fast turtle
    if (totalTurtles > 0) {

        std::string message = "";
        if (fastTurtleColumn >= 0) { // has fast turtle
            if (totalTurtles == 1) { // only one turtle and it's fast one
                message = "Found fast turtle!!!";
            }
            else {
                message = FormatString("Found fast turtle at (%d, %d)", fastTurtleColumn, fastTurtleRow);
            }

            foundFastTurtleNotification.content = message;
            
            GameNotificationService::Speak(foundFastTurtleNotification);
            GameNotificationService::SendNotification(foundFastTurtleNotification);
            log_debug("CollectFavouriteInGameItems Found fast turtle and sent notification with messagge %s\n", message);
        }
    }

    printf("\n\n");
}

void InGameItemCollector::CollectFavouriteItemsAssemblyVersion() {
    // TODO: This version is using assembly to double check and compare with other version if no crashing on this    
    int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;
    int _0x0065ADD0WithASLR = targetDllASLR + 0x0065ADD0;
   /* int targetDllBase = TARGET_MODULE_DLL_STATIC_BASE_ADDRESS + targetDllASLR;

    int eaxValue = targetDllBase + 0x699390;
    int* ptr1 = (int*)(eaxValue + 0x4BC);
    int* ptr2 = (int*)(*ptr1 + 0xC);

    int triggerAnFullBtnAddress = *ptr1;
    int currentHoldingValue = *ptr2;*/
    int favouritItem = IN_GAME_ITEM_NEEDLE;
    

    for (int row = 0; row < MAX_GAME_MAP_ROW; row++)
    {
        for (int column = 0; column < MAX_GAME_MAP_COLUMN; column++)
        {
            int currentCheckingItemId = -1;
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
                ; This call to check has item at tile
                mov ecx, 0x1C; 006ED887        mov         ecx, 1C
                mov edx, row; 006ED88C        mov         edx, dword ptr[ebp - 10]
                mov eax, column; 006ED88F        mov         eax, dword ptr[ebp - 0C]
                call _0x00658D38WithASLR; 006ED892        call        00658D38

                ; this line is for debugging purpose.After running the possible output is 1 or 0
                ; 1 means this tile has item, 0 otherwise :D
                ;mov call_0x658D38_ResultBeforeDecrease, eax

                dec eax; 006ED897        dec         eax
                ; if has no item at this tile, then jump to the end of asm block to continue for next tile
                jne LBL_006ED8DA; 006ED898 > jne         006ED8C8

                ; This call to get ItemID at tile
                mov ecx, 0xA4; 006ED89A        mov         ecx, 0A4
                mov edx, row; 006ED89F        mov         edx, dword ptr[ebp - 10]
                mov eax, column; 006ED8A2        mov         eax, dword ptr[ebp - 0C]
                call _0x00658D38WithASLR; 006ED8A5        call        00658D38
                push eax; 006ED8AA        push        eax
                ; this line is for debugging purpose
                ; mov call_0x658D38_ResultWithInput_ecx_0xA4, eax

                ; Now we will check if this is our favourite item then proceed to collect, otherwise move to next item
                mov currentCheckingItemId, eax
                mov eax, favouritItem
                cmp eax, currentCheckingItemId
                jne LBL_006ED8DA

                ; This call to get mysterious number at tile
                mov ecx, 0x98; 006ED8AB        mov         ecx, 98
                mov edx, row; 006ED8B0        mov         edx, dword ptr[ebp - 10]
                mov eax, column; 006ED8B3        mov         eax, dword ptr[ebp - 0C]
                call _0x00658D38WithASLR; 006ED8B6        call        00658D38
                ; this line is for debugging purpose
                ; mov call_0x658D38_ResultWithInput_ecx_0x98, eax

                mov ecx, eax; 006ED8BB        mov         ecx, eax
                mov edx, row; 006ED8BD        mov         edx, dword ptr[ebp - 10]
                mov eax, column; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
                call _0x0065ADD0WithASLR; 006ED8C3        call        0065ADD0
            LBL_006ED8DA :
                mov eax, eax; 006ED8DA        mov         eax, dword ptr[ebp - 8]
            }
        }
    }
    
}

void InGameItemCollector::CollectItemAtTile(MapPoint point) {
    int _0x0065ADD0WithASLR = targetDllASLR + 0x0065ADD0;

    try {
        bool hasItem = HasItemAtTile(targetDllASLR, point);
        //printf("HasItemAtTile (%d, %d) = %d\n", column, row, hasItem);
        if (!hasItem) {
            return;
        }

        int itemID = GetItemID(targetDllASLR, point);
        //printf("GetItemID (%d, %d) = %d\n", column, row, itemID);
        int mysteriousNumber = GetMysteriousNumber(targetDllASLR, point, itemID);
        //printf("GetMysteriousNumber (%d, %d) = %d\n", column, row, mysteriousNumber);

        // this asm block  will collect the item
        __asm {
            mov eax, itemID
            push eax
            mov eax, mysteriousNumber
            mov ecx, eax; 006ED8BB        mov         ecx, eax
            mov edx, point.row; 006ED8BD        mov         edx, dword ptr[ebp - 10]
            mov eax, point.column; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
            call _0x0065ADD0WithASLR; 006ED8C3        call        0065ADD0
        }
        log_debug("(%d, %d) Found ItemID %d with mysteriousNumber %d\n", point.column, point.row, itemID, mysteriousNumber);
    }
    catch (...) {
        log_debug("CollectItemAtTile (%d, %d) failed with exception!!!\n", point.column, point.row);
    }
}

void InGameItemCollector::CollectItemAtTile(MapPoint point, int itemID, int mysteriousNumber) {
    int _0x0065ADD0WithASLR = targetDllASLR + 0x0065ADD0;

    try {
        // this asm block  will collect the item
        __asm {
            mov eax, itemID
            push eax
            mov eax, mysteriousNumber
            mov ecx, eax; 006ED8BB        mov         ecx, eax
            mov edx, point.row; 006ED8BD        mov         edx, dword ptr[ebp - 10]
            mov eax, point.column; 006ED8C0        mov         eax, dword ptr[ebp - 0C]
            call _0x0065ADD0WithASLR; 006ED8C3        call        0065ADD0
        }
        log_debug("CollectItemAtTile (%d, %d) Found ItemID %d with mysteriousNumber %d\n", point.column, point.row, itemID, mysteriousNumber);        
    }
    catch (...) {
        log_debug("CollectItemAtTile (%d, %d) failed with exception!!!\n", point.column, point.row);        
    }
}