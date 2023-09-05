# DLLProxyProject
A skeleton Windows C++ DLL project for proxying

- https://abda.nl/lumen/
	- Using this to config IDA to use private Lumina server to recognize function signatures and rename the file to analysis properly, especially for CA.exe file
	- After configure as suggestion, restart IDA and load the unpacked CA.exe file into IDA then select Lumina -> Pull all metadata , wait for a while for it to apply all the changes and rename the sub_xxx found to new names
	- We can see a lot of sub_xxx renamed, such as new(uint), lua_xxx (for Lua engine...)
		- From IDA log we can see: lumina: applied metadata to 934 functions.

- Mysterious CA.exe pointers from DWK.dll                             
    - 0070557c: 00FF9734 => 15 XREFs                                     
    - 00705640:  0080A44Dh => 1 XREF:  ->  FUN_00658d38_CheckTileHasItemToEat DAT_00705640. This 0080A44Dh is a sub routine, need to dive in
    - 00705544: 0044F0F1h => 8 XREFs (include FUN_00658d38_CheckTileHasItemToEat), another sub routine. This sub routine will return 0/1, in FUN_00658d38_CheckTileHasItemToEat() method it's to tell if has item at (column, row)

- Reverse to list all game Item ID
    - We know that AddItem function is calling address 0x79275a which is CA.exe sub routine
    - This sub_79275a calling sub_9a459c(itemID) which is calling sub_9a7334(itemID), hence by using Frida we can hook sub_9a7334(itemID) method and print out the item ID when logging the app
    - Frida is able to successfully dumb thousands of valid ItemID (not all yet) after login from login screen to lobby
    - If you click into Item Bag, it only load ItemIDs of the items you have

- Using ClassInformer in  IDA, we found some interesting class:
	- CGOBomber -> this look like a player class that inherit many classes or interface such as IEatObject, IAbilityObject

	- This code is a method of CGOBomber, maybe it's using Nitro item and increase usage by one, consider to reverse and hack this not to increase?
// #STR: "Item/Nitro"
int __thiscall sub_6765E5(_DWORD *this)
{
  int result; // eax
  char v3; // al

  result = sub_673182(this - 356);
  if ( result )
  {
    v3 = sub_44F0F1(this + 2092);
    sub_44F3A4(this + 2095, v3);
    sub_44F3A4(this + 2092, 168);
    this[2103] = 0;
    this[2104] = 0;
    if ( sub_44F0F1(this + 10) >= 0 )
      sub_6755CB(aItemNitro);
    return 1;
  }
  return result;
}

- Shop Modify Dialog
	.text:00D8E3D4     aShopModifyDial db 'Shop Modify Dialog',0
	- Reverse to see how to trigger this dialog in game, it allow to modify item
- Find how to show CDialogWnd in c++ to show Shop  Modify Dialog
- Proxy nmco3.dll, there are tons of interesting method like GetFriendList...
- Reverse *(int*)0xFF9734 Object
	- [esi + 0x6750] => object, logic: *this + 4 * [esi + 0x6754] => CGameContext instance
	- [esi + 0x6754] => integer (possible 0), this value is used to calculate and set value for [esi + 0x6750] (check address 7F3530)
	- [esi + 0x6740] => integer (check address 007F8199)
	- [esi + 1DF0C0h] => integer (check address 7F8195)
	- [esi + 6744h] => integer, seems not change after play again (4294967295), big number (check address 7F8195)
	- [esi + 6758h] => integer, random value (check address 7F3543)
	- [esi + 675Ch] => integer, random value, seems always greater than [esi + 6758h] by 4
	- Try to run frida script to enumerate all possible property value with offset
		function enumeratePropertiesOfObjectFF9734() {
			const FF9734 = ptr(0xFF9734)
			const baseObjectPointer = Memory.readPointer(FF9734)
			console.log(`baseObjectPointer ${Memory.readPointer(baseObjectPointer)}`)
			for (var i = 0; i < 0x6750; i = i + 4) {
				const propertyAtAddress = ptr(baseObjectPointer.add(i));
				const propertyValue = Memory.readPointer(propertyAtAddress)
				logFile.write(`${i}\t\t${ptr(i)}\t\t${propertyValue}\n`);
				console.log(`${i}\t\t${propertyValue}`)
			}
			logFile.flush();
		}
		
		Output:
		0		0x0			0xd9ef48 => check this address this is the vftable of const CGameStage::`vftable', 0xFF9734 holding a pointer to CGameStage object (only when playing)
		4		0x4			0x3a23e220
		8		0x8			0x6e69614d
		12		0xc			0x61745320
		16		0x10		0x6567
		20		0x14		0xff00ff
		24		0x18		0xa
		28		0x1c		0xf
		32		0x20		0xfffffce0
		36		0x24		0xfffffda8
		40		0x28		0x960
		44		0x2c		0x708

- https://reverseengineering.stackexchange.com/questions/11811/how-to-organize-vtables-in-ida-pro
	- Read this to understand how C++ classes layout in memory with single inheritance and multiple inheritant

- How to reconstruct the data type of each offset of an base pointer:
	- As IDA we are able to use Class Informer plugin to show us Classes it found with the location of the vftable
		hence if our address is pointing to those vftable address, we know it belongs to that type
	- Take above as an example for 0xFF9734
		- *0xFF9734 => point to address of a pointer => **0xFF9734 => 0xd9ef48
		- Search 0xd9ef48 in IDA we found: 
			.text:00D9EF44     ; class CGameStage: CSessionStage, CChatStage, CStage, CDialogWnd, CWnd, CNamedObject, CObject, struct ICtrlEventHandler, CGameServerPacketHandler<PUserInfoResult>, CServerPacketHandler<PUserInfoResult,enGameServerPacket>, CPacketHandler<PUserInfoResult,enGameServerPacket>, CObject, CGameServerPacketHandler<PCAJJangUserInfoResult>, CServerPacketHandler<PCAJJangUserInfoResult,enGameServerPacket>, CPacketHandler<PCAJJangUserInfoResult,enGameServerPacket>, CObject, CGameServerPacketHandler<PWeeklyLadderUserInfoResult>, CServerPacketHandler<PWeeklyLadderUserInfoResult,enGameServerPacket>, CPacketHandler<PWeeklyLadderUserInfoResult,enGameServerPacket>, CObject, CSubjectBase, IUIContainer, CItemBoxOwner, CObject, TSingleton<CGameStage>, IEventListener, IEffectRegister;  [MI] (#classinformer)
			.text:00D9EF44                     dd offset ??_R4CGameStage@@6B@ ; const CGameStage::`RTTI Complete Object Locator'
			.text:00D9EF48     ; const CGameStage::`vftable'
			.text:00D9EF48     ??_7CGameStage@@6B@ dd offset sub_802D9C

		- Hence we know 0xFF9734 is a pointer of pointer to CGameStage instance
		
	- Reversed Classes
		- CGameStage
			- 0x6750: CGameContext
		- CGameContext
			- 0x10: CGOAIBattleBomber
		- CGOAIBattleBomber
			- vftable:
				- .text:00DAA324                     dd offset sub_4609B6 => it seems print out a lot of offsets of CGOAIBattleBomber
			- 0x2458: Move effect type: 1, 2, 3 (Black effect - Bong' mo` den)
			- 0x245C: Effect bigger shadow: 0xC8 (Shadow plus)
- Reconstruct CGOAIBattleBomber
	- From CGOAIBattleBomber vftable xrefs, we found xrefs_7_sub_86CB1D use this vftable
		.text:00DAA01C ; class CGOAIBattleBomber: CGOGameBomber, CGOBomber, CGOBomberBase, CGOAvatar, CGameObject, CObject, IEffectRegister, CBombOwner, CObject, IGridBaseBombUseAbleObject, IAIAbleObject, IEatObject, IAbilityObject, IUseAbleSpecialItem, IEventListener;  [MI] (#classinformer)
		.text:00DAA01C                 dd offset ??_R4CGOAIBattleBomber@@6B@ ; const CGOAIBattleBomber::`RTTI Complete Object Locator'
		.text:00DAA020 ; const CGOAIBattleBomber::`vftable'
		.text:00DAA020 ??_7CGOAIBattleBomber@@6B@ dd offset xrefs_9_sub_86E014
		.text:00DAA020                                         ; DATA XREF: xrefs_7_sub_86CB1D+2A↑o
	- Navigate to xrefs_7_sub_86CB1D, we found the memory layout of parent vftable of CGOAIBattleBomber are set at specific offets

		.text:0086CB1D xrefs_7_sub_86CB1D proc near            ; CODE XREF: xrefs_1_sub_460304	+7D↑p
		...
		.text:0086CB42                 mov     esi, ecx
		.text:0086CB44                 mov     [ebp+var_10], esi
		.text:0086CB47                 mov     dword ptr [esi], offset ??_7CGOAIBattleBomber@@6B@ ; const CGOAIBattleBomber::`vftable'
		.text:0086CB4D                 mov     dword ptr [esi+8], offset ??_7CGOAIBattleBomber@@6B@_0 ; const CGOAIBattleBomber::`vftable'
		.text:0086CB54                 mov     dword ptr [esi+498h], offset ??_7CGOAIBattleBomber@@6B@_1 ; const CGOAIBattleBomber::`vftable'
		.text:0086CB5E                 mov     dword ptr [esi+4A0h], (offset loc_DAA33F+1)
		.text:0086CB68                 mov     dword ptr [esi+584h], offset ??_7CGOAIBattleBomber@@6B@_2 ; const CGOAIBattleBomber::`vftable'
		.text:0086CB72                 mov     dword ptr [esi+588h], offset ??_7CGOAIBattleBomber@@6B@_3 ; const CGOAIBattleBomber::`vftable'
		.text:0086CB7C                 mov     dword ptr [esi+58Ch], offset ??_7CGOAIBattleBomber@@6B@_4 ; const CGOAIBattleBomber::`vftable'
		.text:0086CB86                 mov     dword ptr [esi+590h], offset ??_7CGOAIBattleBomber@@6B@_5 ; const CGOAIBattleBomber::`vftable'
		.text:0086CB90                 mov     dword ptr [esi+3104h], offset ??_7CGOAIBattleBomber@@6B@_6 ; const CGOAIBattleBomber::`vftable'
	- This looks like a constructor, from that we can  tell what are size of each class. To verify if our assumption is correct, let dump the CGOAIBattleBomber then compare those offset if it's same
		Address		Offset		Value			Pointer To Class
		0x2cf68e98	0x0000	0xdaa020 -> 	33	M	CGOAIBattleBomber	CGOAIBattleBomber: CGOGameBomber, CGOBomber, CGOBomberBase, CGOAvatar, CGameObject, CObject, IEffectRegister, CBombOwner, CObject, IGridBaseBombUseAbleObject, IAIAbleObject, IEatObject, IAbilityObject, IUseAbleSpecialItem, IEventListener;
		0x2cf68ea0	0x0008	0xdaa318 -> 	1	M	CGOAIBattleBomber	IEffectRegister: CBombOwner, CObject, IGridBaseBombUseAbleObject, IAIAbleObject, IEatObject, IAbilityObject, IUseAbleSpecialItem, IEventListener;
		0x2cf69330	0x0498	0xdaa320 -> 	7	M	CGOAIBattleBomber	CBombOwner: CObject, IGridBaseBombUseAbleObject, IAIAbleObject, IEatObject, IAbilityObject, IUseAbleSpecialItem, IEventListener;
		0x2cf69378	0x04E0	0xbe16020 -> 	*(*0xbe16020) = 0xd9dfd4 -> 	12		CGameContext	CGameContext: CObject;
		0x2cf6937c	0x04E4	0x33410738 -> 	*(*(*0x33410738)) = 0xd3f2e0 -> 	11	M	CGOGameBomb	CGOGameBomb: CGOBomb, CGameObject, CObject, IEffectRegister, CSensorTrigger, CObject;
		0x2cf693c0	0x0528	0x2cf6a34c -> 	*(*0x2cf6a34c) = 0xd39e9c -> 	11	M	CGameObject	CGameObject: CObject, IEffectRegister;
		0x2cf6941c	0x0584	0xdaa418 -> 	44	M	CGOAIBattleBomber	IAIAbleObject: IEatObject, IAbilityObject, IUseAbleSpecialItem, IEventListener;
		0x2cf69420	0x0588	0xdaa4cc -> 	9	M	CGOAIBattleBomber	IEatObject: IAbilityObject, IUseAbleSpecialItem, IEventListener;
		0x2cf69424	0x058C	0xdaa4f4 -> 	12	M	CGOAIBattleBomber	IAbilityObject: IUseAbleSpecialItem, IEventListener;
		0x2cf69428	0x0590	0xdaa554 -> 	29	M	CGOAIBattleBomber	IUseAbleSpecialItem: IEventListener;
		....
		0x2cf6bf9c	0x3104	0xdaa5ec -> 	2	M	CGOAIBattleBomber	IEventListener:

- How for find a class layout in memory by scanning vftable
	- As we know for CA.exe we can reconstruct RTTI table using Class Informer
	- If a class has virtual methods, then the first address of that address is pointing to known vftable address
	- We dont know how many members this class has, we can do this by static analysis to find out how it load its offset
	- However, we also can do a linear scanning from starting address of a class until address that contain a vftable, hence it's the end of that object in the memory layout, because once we reach another vftable, it's a sign that starting address of another object
	- So strategy is let do a linear scanning from object address + 0x10000 (we think 0x10000 is big enough to cover all members) or until we reach another vftable then stop scanning
		- This might not true, because for multiple inheritance there will be multiple vftable in memory layout of each the derived class

- .text:00FF99C8     CHackDetector_TSingleton_dword_FF99C8
	- Ctrl + X (or X) on this global variable => 39 Xrefs to this, might need to consider to check what does it checking
	- The caller always push a different number follow by calling sub_9E3024, look like sub_9E3024 is to check hacking type base on given number
		.text:00689B43 0A0                 mov     ecx, CHackDetector_TSingleton_dword_FF99C8
		.text:00689B49 0A0                 push    0Bh
		.text:00689B4B 0A4                 call    sub_9E3024
	- There are 17 Xrefs to sub_9E3024 hence it looks like sub_9E3024 is a member method of CHackDetector (not virtual method as it does not appear in CHackDetector vftable)
	- Can hook into sub_9E3024 to see how it react

- Reverse CharTE.idd, Fx.idd, EmoTE.idd, FxAsset.idd
	- These 4 files looks like encrypted lua files in main Bnb folder and quite heavy size
	- by searching their name, we found this method sub_9CA901() has logic to load it some how
		- inside this method, it calls 4 time sub_B1C310() to load each file
			- xref this method, we found 1 interesting sub_A8216D() method, this in charge of downloading .idd, .idx files, need to reverse this to see how it uncompress the file or encrypt the files
				- Might hook into CreateFileA method to print out what file name created during this method using detours
		- we found global dword_1088D50 is being used, check it at runtime (cheat engine) we can tell this is pointing vftable of CPackSysMan
			.text:01088D50 dword_1088D50   dd 0
		- Look like CPackSysMan is in charge or packing/unpacking file, chext xref of this dword_1088D50 we found 83 results :D
- dword_FFB1D8 => maybe global pointer to store luaState structure
	.text:0057693D                 mov     eax, maybe_luaState_dword_FFB1D8
	.text:00576942                 push    esi
	.text:00576943                 push    [ebp+Source]    ; Source
	.text:00576946                 mov     esi, ecx
	.text:00576948                 mov     [esi], eax
	.text:0057694A                 call    xrefs_1_sub_576D44
	.text:0057694F                 push    [ebp+Source]
	.text:00576952                 push    dword ptr [esi] ; luaState 
	.text:00576954                 call    xrefs_114_?lua_pushstring@@YAXPAUlua_State@@PBD@Z

- TODO:
	- Check CA game in training mode, unlimited shop can be used without reducing, all the item is showing x99
		- Need to use frida and dump this case to see what kind of player is that, what game mode... and compare with normal game
	- Write a python/C# program to automate read specific memory from CA, sometime CHeat Engine is detected and game is auto logout
	- CGridMan::GetSafeDangerGridNum
		- // #STR: "%s grid %s Get Bomb", "%s grid %s no bomb", "CGridMan::GetSafeDangerGridNum"
	- Detours CBlackCipher2Client::PushData() method and flushData method to no execute at all (using cove cave technique) to see if still got BlackCipher2_Error01/02 error when attaching with frida
	- Check these suspicious string
		- DetectedHacking02
		- DetectedHacking07
			- Got this error popup while playing game and it pop out to lobby screen, not login screens
			- Check reference it's using in sub_7F834A, in this function it calls sub_9D0901(dword_FF95B8) multiple times and check the result integer with 14, 17, 19, 33, if not match then it will call xrefs_5359_sub_44F0F1 to check if result > 2000 then hack detected, it seems sub_44F0F1 is the wrapper to call Lua APIs
			- sub_9D0901 is just getter method to get this[141] = [this + 234h] = [*FF95B8 + 234h]
			- We also know that dword_FF95B8 is global pointer that we used to modify player moving effect  (it's pointing CFxContext vftable)

- BNBBotTW version
	- it create new random folder name at C:\ disk (C:\17a065b64ca0b2f557bfe2e9e4919419), inside will have .exe file and hook.dll file
		- hook.dll file is packaged using Themida version 3.0.0.0 - 3.1.3.0 (checked by Exeinfo PE tool)
		- The current release Unlicense v0.4.0 cant unpack this, however we raised an issue and dev fixed and pushed to dev branch, we need to build the tool by ourselves
			- Fetch the unlicense repo https://github.com/ergrelet/unlicense and switch to dev branch
			- As hook.dll is built by 32 bits instead of 64 bits, we need to build our Unlicense tool for 32 bits (you can not use Unlicense tool 64 bits to unpack 32 bits otherwise will get interpreter mismatch error: ERROR - Target PE cannot be dumped with this interpreter. This is most likely a 32 vs 64 bit mismatch.) during unpacking
			- Download python installer 32bit version and install it to new folder for 32bit usage			
			- Install Unlicense tool project dependency
				- Navigate to Unlicense git root folder and run this command:
					- C:\Users\rta\AppData\Local\Programs\Python\Python311-32\python.exe -m pip install .
			- Install pyinstaller package using python 32 bit - pyinstaller will be used to build Unlicense project
				- C:\Users\rta\AppData\Local\Programs\Python\Python311-32\python.exe -m pip uninstall pyinstaller
			- Using pyinstaller to build project
				- C:\Users\rta\AppData\Local\Programs\Python\Python311-32\Scripts\pyinstaller.exe .\unlicense.spec
			- After sucessfully, the Unlicense.exe 32 bits version will be generated in .\dist folder and ready to use
		- Use new unlicense.exe to unpack hook.dll
			- .\dist\unlicense.exe C:\Users\rta\Downloads\hack_bnbbot_1_session_trial_hoai86\hack1\17a065b64ca0b2f557bfe2e9e4919419\17a065b64ca0b2f557bfe2e9e4919419\hook.dll -v
		- The unpacked_hook.dll will be generated successfully in the current running location
		- Use Exeinfo PE to check unpacked_hook.dll it's saying "*Unknown DLL , BA 2C AC x  [ Linker 2.25 ] - First section Delphi  NOT Packed - [ CRC Set ] Std Compiler section  [ 16 ] sections "
		- Now we can use Interactive Delphi Reconstructor to load this file for analysis
			- From IDR select this file, it will recommend OEP input just leave as default
			- Next step select No for native knowledge bin
			- Next step we need to select the knowledge bin (kb2009.bin) will do
			- Wait a while and it will load successfully and ready for analysis
		- boom.dll
			- Packed by Themida too, can follow above steps to unpack successfully
			- Load into IDA and check the Exports tab, it's actually DWK.dll wrapper as it exports InstallDWK, UninstallDWK...
			- It's using Borland Delphi compiler (checked with Detect It Easy tool)
			- TLicenseInfo
				- This class is in charge of checking license, you can search string "License" and it will lead to this class and logic to check if license expire or not
				- POST https://wdyl.homes/vibnb/Process.php
		- bnb-bot.dll
			- x64 dll file, no packed
			- Load by IDA64 and it's showing pdb file path that mentions this is a BlackCipher hook bypass "H:\Pascal\lethuyproject\CrazyArcadeBypass\x64\Release\BlackCipherHook_x64.pdb"

			
		
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
