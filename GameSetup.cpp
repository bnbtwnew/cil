#include "GameSetup.h"
#include <stdio.h>

GameSetup::GameSetup(int targetDllASLR) : targetDllASLR(targetDllASLR) {}

void GameSetup::UpdateDllASLR(int aslrOffset) {
    targetDllASLR = aslrOffset;
}

void GameSetup::AddBundleItems() {
    int itemIds[] = {
        // these items has the clock icon
        89997, // khien tu dong
        89998, // sieu khien nuoc
        89999, // sieu nhan sam
        100000, // kim (kem` dong` ho`) => we use this item instead of smiley face because in game this item will auto popup suggest us to use instead of other ones
        100001, // fi tieu (kem` dong` ho`)
        100002, // rua` vip (kem` dong` ho`)
        100003, // nhay?

        // these items has the smiley face icon
        //150654, // kim
        150655, // khien
        150658, // nhan sam
        //150659, // phi tieu
        //150660, // ca' hop.
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

int GameSetup::AddItem(DWORD itemID, DWORD firstArg, DWORD fourthArg, DWORD quantity) {
    /*printf("Start adding item... for itemID = %d", itemID);
    printf("hihi");*/
    int result = 0;
    try {
        DWORD bnbAddItemFunctionAddress = 0x79275a;
        //DWORD quantity = itemID;
        /*
        // this is the logic of add item from CA.exe file
        // so basically esi is Item object where *esi is itemID, esi + 0x4 is quantity
        if (esi != *(ebp - 0x54)) {
                edi = *(ebp - 0x90);
                do {
                        sub_79275a(edi, *esi, *(esi + 0x4), *(esi + 0x8));
                        esi = esi + 0x20;
                        esp = (esp - 0x10) + 0x10;
                } while (esi != *(ebp - 0x54));
                edi = *(ebp - 0x8c);
        }
        */
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