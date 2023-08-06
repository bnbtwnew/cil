# DLLProxyProject
A skeleton Windows C++ DLL project for proxying
                             
- Mysterious CA.exe pointers from DWK.dll                             
    - 0070557c: 00FF9734 => 15 XREFs                                     
    - 00705640:  0080A44Dh => 1 XREF:  ->  FUN_00658d38_CheckTileHasItemToEat DAT_00705640. This 0080A44Dh is a sub routine, need to dive in
    - 00705544: 0044F0F1h => 8 XREFs (include FUN_00658d38_CheckTileHasItemToEat), another sub routine. This sub routine will return 0/1, in FUN_00658d38_CheckTileHasItemToEat() method it's to tell if has item at (column, row)

                             
