# DLLProxyProject
A skeleton Windows C++ DLL project for proxying
                             
- Mysterious CA.exe pointers from DWK.dll                             
    - 0070557c: 00FF9734 => 15 XREFs                                     
    - 00705640:  0080A44Dh => 1 XREF:  ->  FUN_00658d38_CheckTileHasItemToEat DAT_00705640. This 0080A44Dh is a sub routine, need to dive in
    - 00705544: 0044F0F1h => 8 XREFs (include FUN_00658d38_CheckTileHasItemToEat), another sub routine. This sub routine will return 0/1, in FUN_00658d38_CheckTileHasItemToEat() method it's to tell if has item at (column, row)


New BNB TW Hack Experiement Loaded!
AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (4, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 2

<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 0 toRow = 7
<==== Collected item AnFullToSection at (column x row) = (2, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 8

<==== Collected item AnFullToSection at (column x row) = (2, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 11

<==== Collected item AnFullToSection at (column x row) = (7, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 124 call_0x658D38_ResultWithInput_ecx_0x98 = 13

<==== Collected item AnFullToSection at (column x row) = (4, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 55 call_0x658D38_ResultWithInput_ecx_0x98 = 16

<==== Collected item AnFullToSection at (column x row) = (2, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 54 call_0x658D38_ResultWithInput_ecx_0x98 = 20

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (10, 0) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 5

<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 0 toRow = 6
<==== Collected item AnFullToSection at (column x row) = (12, 1) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 10

<==== Collected item AnFullToSection at (column x row) = (12, 2) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 14

<==== Collected item AnFullToSection at (column x row) = (10, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 17

<==== Collected item AnFullToSection at (column x row) = (13, 3) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 18

<==== Collected item AnFullToSection at (column x row) = (12, 4) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 1 call_0x658D38_ResultWithInput_ecx_0x98 = 21

<==== Collected item AnFullToSection at (column x row) = (11, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 36 call_0x658D38_ResultWithInput_ecx_0x98 = 24

<==== Collected item AnFullToSection at (column x row) = (12, 5) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 25

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 0 toColumn = 8 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (0, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 212 call_0x658D38_ResultWithInput_ecx_0x98 = 37

<==== Collected item AnFullToSection at (column x row) = (2, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 119 call_0x658D38_ResultWithInput_ecx_0x98 = 38

<==== Collected item AnFullToSection at (column x row) = (3, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 39

<==== Collected item AnFullToSection at (column x row) = (6, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 43

<==== Collected item AnFullToSection at (column x row) = (4, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 34 call_0x658D38_ResultWithInput_ecx_0x98 = 46

<==== Collected item AnFullToSection at (column x row) = (6, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 48

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (11, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 29

<==== Collected item AnFullToSection at (column x row) = (12, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 30

<==== Collected item AnFullToSection at (column x row) = (9, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 34

<==== Collected item AnFullToSection at (column x row) = (10, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 35

<==== Collected item AnFullToSection at (column x row) = (12, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 36

<==== Collected item AnFullToSection at (column x row) = (10, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 42

<==== Collected item AnFullToSection at (column x row) = (8, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 44

<==== Collected item AnFullToSection at (column x row) = (12, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 45

<==== Collected item AnFullToSection at (column x row) = (8, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 49

<==== Collected item AnFullToSection at (column x row) = (10, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 4 call_0x658D38_ResultWithInput_ecx_0x98 = 51

<==== Collected item AnFullToSection at (column x row) = (12, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 52

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (11, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 29

<==== Collected item AnFullToSection at (column x row) = (12, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 30

<==== Collected item AnFullToSection at (column x row) = (9, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 34

<==== Collected item AnFullToSection at (column x row) = (10, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 35

<==== Collected item AnFullToSection at (column x row) = (12, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 36

<==== Collected item AnFullToSection at (column x row) = (10, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 42

<==== Collected item AnFullToSection at (column x row) = (8, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 44

<==== Collected item AnFullToSection at (column x row) = (12, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 45

<==== Collected item AnFullToSection at (column x row) = (8, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 49

<==== Collected item AnFullToSection at (column x row) = (10, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 4 call_0x658D38_ResultWithInput_ecx_0x98 = 51

<==== Collected item AnFullToSection at (column x row) = (12, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 52

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (11, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 29

<==== Collected item AnFullToSection at (column x row) = (12, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 30

<==== Collected item AnFullToSection at (column x row) = (9, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 34

<==== Collected item AnFullToSection at (column x row) = (10, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 35

<==== Collected item AnFullToSection at (column x row) = (12, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 36

<==== Collected item AnFullToSection at (column x row) = (10, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 42

<==== Collected item AnFullToSection at (column x row) = (8, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 44

<==== Collected item AnFullToSection at (column x row) = (12, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 45

<==== Collected item AnFullToSection at (column x row) = (8, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 49

<==== Collected item AnFullToSection at (column x row) = (10, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 4 call_0x658D38_ResultWithInput_ecx_0x98 = 51

<==== Collected item AnFullToSection at (column x row) = (12, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 52

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (11, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 29

<==== Collected item AnFullToSection at (column x row) = (12, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 30

<==== Collected item AnFullToSection at (column x row) = (9, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 34

<==== Collected item AnFullToSection at (column x row) = (10, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 35

<==== Collected item AnFullToSection at (column x row) = (12, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 36

<==== Collected item AnFullToSection at (column x row) = (10, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 42

<==== Collected item AnFullToSection at (column x row) = (8, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 44

<==== Collected item AnFullToSection at (column x row) = (12, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 45

<==== Collected item AnFullToSection at (column x row) = (8, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 49

<==== Collected item AnFullToSection at (column x row) = (10, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 4 call_0x658D38_ResultWithInput_ecx_0x98 = 51

<==== Collected item AnFullToSection at (column x row) = (12, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 52

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (11, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 29

<==== Collected item AnFullToSection at (column x row) = (12, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 30

<==== Collected item AnFullToSection at (column x row) = (9, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 34

<==== Collected item AnFullToSection at (column x row) = (10, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 35

<==== Collected item AnFullToSection at (column x row) = (12, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 36

<==== Collected item AnFullToSection at (column x row) = (10, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 42

<==== Collected item AnFullToSection at (column x row) = (8, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 44

<==== Collected item AnFullToSection at (column x row) = (12, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 45

<==== Collected item AnFullToSection at (column x row) = (8, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 49

<==== Collected item AnFullToSection at (column x row) = (10, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 4 call_0x658D38_ResultWithInput_ecx_0x98 = 51

<==== Collected item AnFullToSection at (column x row) = (12, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 52

AnFullAtDirection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
d3dx9_help.dll base = 6980000
AnFullToSection fromColumn = 7 toColumn = 15 fromRow = 6 toRow = 13
<==== Collected item AnFullToSection at (column x row) = (11, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 35 call_0x658D38_ResultWithInput_ecx_0x98 = 29

<==== Collected item AnFullToSection at (column x row) = (12, 6) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 30

<==== Collected item AnFullToSection at (column x row) = (9, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 15 call_0x658D38_ResultWithInput_ecx_0x98 = 34

<==== Collected item AnFullToSection at (column x row) = (10, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 35

<==== Collected item AnFullToSection at (column x row) = (12, 8) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 2 call_0x658D38_ResultWithInput_ecx_0x98 = 36

<==== Collected item AnFullToSection at (column x row) = (10, 9) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 42

<==== Collected item AnFullToSection at (column x row) = (8, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 44

<==== Collected item AnFullToSection at (column x row) = (12, 10) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 45

<==== Collected item AnFullToSection at (column x row) = (8, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 0 call_0x658D38_ResultWithInput_ecx_0x98 = 49

<==== Collected item AnFullToSection at (column x row) = (10, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 4 call_0x658D38_ResultWithInput_ecx_0x98 = 51

<==== Collected item AnFullToSection at (column x row) = (12, 11) call_0x658D38_ResultBeforeDecrease = 1 call_0x658D38_ResultWithInput_ecx_0xA4 = 5 call_0x658D38_ResultWithInput_ecx_0x98 = 52

d3dx9_help.dll base = 6980000Checkbox ptr: 703b840 setSelected ptr: 703bc70
