#include "MyLic.h"

#include <sstream>
#include <vector>
#include <windows.h>
#include <winioctl.h> // For IOCTL_DISK_GET_DRIVE_GEOMETRY
#include <ntddscsi.h> // For SCSI_PASS_THROUGH_DIRECT
#include <openssl/sha.h> // to include using <>, you need to add include folder to Environment Path
#include <iomanip> // Include for setw and setfill 
#include <tchar.h>
#include <iphlpapi.h>
#include "FileDownloader.h"
#include "LicenseFeaturesStatus.h"
#include "ThemidaSDK.h"
using namespace std;

#pragma comment(lib, "Iphlpapi.lib")

string MyLic::CheckLicense() {
    VM_TIGER_BLACK_START
    // 0. Generate machine id hashed as the key
    string hashedMachineId = GenerateMachineID();

    // 1. Fetch json file from server and check
    FileDownloader downloader = FileDownloader(hashedMachineId);
    stringstream urlStream;
    urlStream << "h"<<"t"<<"t"<<"p"<<"s"<<":"<<"/"<<"/"<<"ra"<<"w.g"<<"ith"<<"ubu"<<"ser"<<"co"<<"nte"<<"nt"<<".c"<<"om"<<"/"<< "bn" << "bt" << "wn" << "ew" << "/c" << "il" << "/ma" << "in/" << hashedMachineId;
    string url = urlStream.str();
    my_rog_debug1("fetching url: %s\n", url);
    bool result = downloader.DownloadAndDecryptFile(url);
    int integrity = 10000;
    CHECK_CODE_INTEGRITY(integrity, 20000);
    if (integrity != 20000) {
        // Application code is patched!
        // then we set licensed to false due to app is patched
        GenerateAddingBundleItemsLicensedCode((1000 + 1 - 335  + 4) > 900990);
        GenerateMovingEffectCode((2000 + 2 - 235 + 9) > 990990);
        my_rog_debug1("Application code is patched! resut: %d\n", result);
    }
    else {
        my_rog_debug1("check lic result: %d\n", result);
        GenerateAddingBundleItemsLicensedCode(result);
        GenerateMovingEffectCode(result);
    }
    
    VM_TIGER_BLACK_END

    return "";
}

void MyLic::PersistMachinceIdToFile() {
    VM_TIGER_BLACK_START
    string machineID = GenerateMachineID();
    stringstream fileNameStream;
    fileNameStream << "li" << "ce" << "n" << "se" << ".t" << "xt";
    std::ofstream outfile(fileNameStream.str(), std::ofstream::binary);
    outfile << machineID;
    outfile.close();
    VM_TIGER_BLACK_END
}

    // Generate a machine-unique ID based on system properties.
std::string MyLic::GenerateMachineID() {
    std::stringstream idStream;
    std::string bios = _GetBIOSVersion();
    std::string disk = _GetHardDiskSerialNumber();
    std::string macAddress = _GetMACAddress();
    std::string systemVolume = _GetSystemDriveSerialNumber();
    //printf("id = %s, bios = %s, serial = %s\n", id, bios, systemVolume);
    idStream << bios << "-" << macAddress << "-" << systemVolume << "-" << disk;
    //idStream << _GetProcessorID() << _GetBIOSVersion() << _GetHardDiskSerialNumber();
    // You can add more components here.

    //return idStream.str();
    std::string machineID = idStream.str();
    my_rog_debug1("machineID before hashing: %s\n", machineID);

    string hashedMachineID;
    MyEncryptor::Sha256UsingEVP(machineID, hashedMachineID);
    my_rog_debug1("machineID after hashing: %s\n", hashedMachineID);
    return hashedMachineID;
}

// Retrieve the CPU ID or a similar identifier.
std::string MyLic::_GetProcessorID() {
    std::string processorID;

    // This is a Windows-specific example. You may need to adapt it for other platforms.
    char buffer[256];
    DWORD size = sizeof(buffer);
    if (GetSystemFirmwareTable('RSMB', '0', buffer, size)) {
        // Convert the binary data to a string.
        for (DWORD i = 0; i < size; ++i) {
            char hex[3];
            sprintf(hex, "%02X", buffer[i]);
            processorID += hex;
        }
    }
    else {
        // Error handling if retrieving processor ID fails.
        processorID = "Unknown";
    }

    return processorID;
}

// Retrieve the BIOS version or a similar identifier.
std::string MyLic::_GetBIOSVersion() {
    std::string biosVersion;

    // This is a Windows-specific example. You may need to adapt it for other platforms.
    char buffer[256];
    DWORD size = sizeof(buffer);
    if (GetFirmwareEnvironmentVariable("SystemSKU", "{00000000-0000-0000-0000-000000000000}", buffer, size)) {
        // Convert the binary data to a string.
        for (DWORD i = 0; i < size; ++i) {
            char hex[3];
            sprintf(hex, "%02X", buffer[i]);
            biosVersion += hex;
        }
    }
    else {
        // Error handling if retrieving BIOS version fails.
        biosVersion = "Unknown";
    }

    return biosVersion;
}

// Retrieve the MAC address of the first network adapter.
std::string MyLic::_GetMACAddress() {
    std::string macAddress;

    IP_ADAPTER_INFO adapterInfo[32];
    ULONG bufferSize = sizeof(adapterInfo);

    if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {
        // Convert the MAC address bytes to a hexadecimal string.
        for (int i = 0; i < 6; i++) {
            macAddress += (i == 0 ? "" : "-");
            macAddress += (i < 10 ? "0" : "");
            macAddress += std::to_string(adapterInfo[0].Address[i]);
        }
    }

    if (macAddress.empty()) {
        // Error handling if retrieving MAC address fails.
        macAddress = "Unknown";
    }

    return macAddress;
    //return "";
}

// Retrieve the serial number of the system drive.
std::string MyLic::_GetSystemDriveSerialNumber() {
    std::string serialNumber;

    TCHAR volumeName[MAX_PATH + 1];
    TCHAR fileSystem[MAX_PATH + 1];
    DWORD serialNumberDWORD;
    DWORD maxComponentLen;
    DWORD fileSystemFlags;

    if (GetVolumeInformation(_T("C:\\"), volumeName, sizeof(volumeName),
        &serialNumberDWORD, &maxComponentLen, &fileSystemFlags, fileSystem, sizeof(fileSystem))) {
        // Convert the serial number to a string.
        serialNumber = std::to_string(serialNumberDWORD);
    }

    if (serialNumber.empty()) {
        // Error handling if retrieving system drive serial number fails.
        serialNumber = "Unknown";
    }

    return serialNumber;
}

// Retrieve the serial number of the first hard disk.
std::string MyLic::_GetHardDiskSerialNumber() {
    std::string serialNumber;

    // This code assumes that the first hard disk is the one you want to retrieve.
    HANDLE hDevice = CreateFile(
        "\\\\.\\PhysicalDrive0", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL
    );

    if (hDevice != INVALID_HANDLE_VALUE) {
        STORAGE_PROPERTY_QUERY storagePropertyQuery;
        ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
        storagePropertyQuery.PropertyId = StorageDeviceProperty;
        storagePropertyQuery.QueryType = PropertyStandardQuery;

        DWORD bytesReturned = 0;
        STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };

        if (DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
            &storagePropertyQuery, sizeof(storagePropertyQuery),
            &storageDescriptorHeader, sizeof(storageDescriptorHeader),
            &bytesReturned, NULL)) {

            std::vector<char> buffer(storageDescriptorHeader.Size);
            if (DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
                &storagePropertyQuery, sizeof(storagePropertyQuery),
                buffer.data(), buffer.size(),
                &bytesReturned, NULL)) {

                STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(buffer.data());

                // Serial number starts at offset pDeviceDescriptor->SerialNumberOffset.
                serialNumber.assign(buffer.data() + pDeviceDescriptor->SerialNumberOffset);
            }
        }

        CloseHandle(hDevice);
    }

    if (serialNumber.empty()) {
        // Error handling if retrieving serial number fails.
        serialNumber = "Unknown";
    }

    return serialNumber;
}