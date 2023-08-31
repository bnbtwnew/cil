#pragma once
#include <iostream>
#include <string>

class MyLic {
public:
	std::string GenerateMachineID();
	std::string CheckLicense();
	void MyLic::PersistMachinceIdToFile();

private:
	std::string MyLic::_GetProcessorID();
	std::string MyLic::_GetBIOSVersion();
	std::string MyLic::_GetHardDiskSerialNumber();
	std::string MyLic::_GetMACAddress();
	std::string MyLic::_GetSystemDriveSerialNumber();
};




