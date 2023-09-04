#include "GameSetup.h"
#include <stdio.h>
#include "GameUtils.h"
#include "ThemidaSDK.h"
#include "LicenseFeaturesStatus.h"

GameSetup::GameSetup(int targetDllASLR) : targetDllASLR(targetDllASLR) {}

void GameSetup::UpdateDllASLR(int aslrOffset) {
    targetDllASLR = aslrOffset;
}

void GameSetup::AddBundleItems() {
    VM_TIGER_BLACK_START
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
    my_rog_debug1("Start adding bundle of items...\n");

    if (licensedAddingBundleItemsCode == LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
        for (index = 0; index < totalItems; index++) {
            int quantity = itemIds[index];
#ifdef LICENSE_BUILD
            quantity = 44444444 + 22222222 + 11111111 + 11111111;
#endif // LICENSE_BUILD

            // we only add if license is still valid
            my_rog_debug1(" index = %d licensedAddingBundleItemsCode = %d LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE = %d\n", index, licensedAddingBundleItemsCode, LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE);
        
            
            // before add items, we use Themida macro to check again if tampered
            int mylicensedAddingBundleItemsCode = -1;
            CHECK_PROTECTION(mylicensedAddingBundleItemsCode, LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE);
            if (mylicensedAddingBundleItemsCode != LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
                my_rog_debug1("failed themida CHECK_PROTECTION\n");
                break;
            }

            mylicensedAddingBundleItemsCode = -2;
            CHECK_CODE_INTEGRITY(mylicensedAddingBundleItemsCode, LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE);
            if (mylicensedAddingBundleItemsCode != LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
                my_rog_debug1("failed themida CHECK_CODE_INTEGRITY\n");
                break;
            }

            // only add item if passed all protections
            int result = AddItem(itemIds[index], 0, 0, quantity);
            if (result > 0) {
                successfulAddedItemCount++;
            }
        }
        
    }

    my_rog_debug1("Added %d/%d items successfully!\n", successfulAddedItemCount, totalItems);
    VM_TIGER_BLACK_END
}

int GameSetup::AddItem(DWORD itemID, DWORD firstArg, DWORD fourthArg, DWORD quantity) {
    /*my_rog_debug1("Start adding item... for itemID = %d", itemID);
    my_rog_debug1("hihi");*/
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
        // we only add if license still valid
        if (licensedAddingBundleItemsCode == LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
            // before add items, we use Themida macro to check again if tampered
            int mylicensedAddingBundleItemsCode = -1;
            CHECK_PROTECTION(mylicensedAddingBundleItemsCode, LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE);
            if (mylicensedAddingBundleItemsCode != LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
                my_rog_debug1("failed themida CHECK_PROTECTION\n");                
            }

            mylicensedAddingBundleItemsCode = -2;
            CHECK_CODE_INTEGRITY(mylicensedAddingBundleItemsCode, LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE);
            if (mylicensedAddingBundleItemsCode != LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
                my_rog_debug1("failed themida CHECK_CODE_INTEGRITY\n");                
            }

            if (mylicensedAddingBundleItemsCode == LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
                result = ((int (*)(DWORD, DWORD, DWORD, DWORD))bnbAddItemFunctionAddress)(firstArg, itemID, quantity, fourthArg);
            }
            
        }
        else {
            result = 0;
        }
        
        //                      ==========     --> addr of the function to call
        //        =============                --> type of the function to call
        //       =========================     --> ... we get a ptr to that fct
        //      =============================  --> ... and we call the function
        my_rog_debug1("Added item with result: %d\n", result);
    }
    catch (...) {
        my_rog_debug1("Added item failed with exception!!!\n");
    }

    //my_rog_debug1("========================================\n\n");
    return result;
}