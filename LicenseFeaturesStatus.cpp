#include "LicenseFeaturesStatus.h"
#include "GameUtils.h"

int licensedAddingBundleItemsCode = 0;
int licensedMovingEffectCode = 0;

void GenerateAddingBundleItemsLicensedCode(bool licensed) {
    int x = LICENSED_ADDING_BUNDLE_PART_1;
    int y = LICENSED_ADDING_BUNDLE_PART_2;
    if (licensed) {
        licensedAddingBundleItemsCode = x * y + 1;
    }
    else {
        licensedAddingBundleItemsCode = x + y;
    }    
    my_rog_debug1("licensedAddingBundleItemsCode updated to %d with licensed bool = %d\n", licensedAddingBundleItemsCode, licensed);
}

void GenerateMovingEffectCode(bool licensed) {
    int x = 1000;
    int y = 3000;
    if (licensed) {
        licensedMovingEffectCode = x * y + 1;
    }
    else {
        licensedMovingEffectCode = x + y;
    }
    my_rog_debug1("licensedMovingEffectCode updated to %d with licensed bool = %d\n", licensedMovingEffectCode, licensed);
}