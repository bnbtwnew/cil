#pragma once
#include <Windows.h>

class GameSetup
{
public:
	GameSetup(int targetDllASLR);
	void UpdateDllASLR(int aslrOffset);
	void AddBundleItems();
	int GameSetup::AddItem(DWORD itemID, DWORD firstArg, DWORD fourthArg, DWORD quantity);

private:
	int targetDllASLR;
	int _AddItem(DWORD itemID, DWORD firstArg, DWORD fourthArg, DWORD quantity);
};

