#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "curl/curl.h" // libcurl library
#include <openssl/aes.h> // OpenSSL for AES decryption
#include "rapidjson/document.h" // RapidJSON for JSON parsing
#include "MyEncryptor.h"
#include "GameUtils.h"
#include "LicenseFeaturesStatus.h"
#include "ThemidaSDK.h"

using namespace GameUtils;

class FileDownloader {
public:
    FileDownloader(const std::string& keyHex) : _keyHex(keyHex) {
        // Initialize libcurl.
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    ~FileDownloader() {
        // Cleanup libcurl.
        curl_global_cleanup();
    }

    bool MyDecryptFile(const std::string fileContent) {
        VM_TIGER_BLACK_START
        std::string decryptedFileContent;
        // Refer BnBTwBotKeyGen.cpp for logic of encryption
        string fileContentDecryptionKey = _keyHex.substr(32, 32);
        my_rog_debug1("MyDecryptFile encrypted file content: %s key: %s\n", fileContent, fileContentDecryptionKey);
        if (!MyEncryptor::DecryptAES(fileContent, decryptedFileContent, fileContentDecryptionKey)) {
            my_rog_debug1("Failed to decrypt file the content.\n");
            return false;
        }

        // Now parse json using rapidjson and extract expiry time property
        rapidjson::Document document;
        document.Parse(decryptedFileContent.c_str());
        if (document.HasParseError()) {
            my_rog_debug1("J S O N parse error: %s\n", document.GetParseError());
            return false;
        }

        // ====================== extract anti-tampering hash and compare if it's tampered ====================== 
        if (!document.HasMember("ta")) {
            my_rog_debug1("t.a not exist\n");
            return false;
        }

        const rapidjson::Value& ta = document["ta"];
        if (!ta.IsString()) {
            my_rog_debug1("t.a is not String\n");
            return false;
        }

        string encryptedAntitamperingStr = ta.GetString();
        string antiTamperKeyHex = _keyHex.substr(0, 32);
        string decryptedAntitamperingStr;
        MyEncryptor::DecryptAES(encryptedAntitamperingStr, decryptedAntitamperingStr, antiTamperKeyHex);

        // ====================== extract buyer info value ====================== 
        if (!document.HasMember("fi")) {
            my_rog_debug1("f.i not exist\n");
            return false;
        }
        const rapidjson::Value& fi = document["fi"];
        if (!fi.IsString()) {
            my_rog_debug1("f.i is not String\n");
            return false;
        }
        string encryptedBuyerInfoStr = fi.GetString();
        string buyerInfoKeyHex = _keyHex.substr(16, 32);
        string decryptedBuyerInfoStr;
        MyEncryptor::DecryptAES(encryptedBuyerInfoStr, decryptedBuyerInfoStr, buyerInfoKeyHex);

        // ====================== extract expiry time value ====================== 
        if (!document.HasMember("xe")) {
            my_rog_debug1("x.e not exist\n");
            return false;
        }
        const rapidjson::Value& xe = document["xe"];
        if (!xe.IsString()) {
            my_rog_debug1("x.e is not String\n");
            return false;
        }
        string encryptedExpiryDateStr = xe.GetString();
        string expiryDateKeyHex = _keyHex.substr(16, 32);
        string decryptedExpiryDateStr;
        MyEncryptor::DecryptAES(encryptedExpiryDateStr, decryptedExpiryDateStr, expiryDateKeyHex);

        // ====================== SHA256(expiryDate + buyerInfo) == decryptedAntitamperingStr ====================== 
        string combineString = decryptedExpiryDateStr + decryptedBuyerInfoStr;
        string antitamperingHashedToCompare;
        MyEncryptor::Sha256UsingEVP(combineString, antitamperingHashedToCompare);
        if (decryptedAntitamperingStr.compare(antitamperingHashedToCompare) != 0) {
            my_rog_debug1("t.a.m.p.e.r@@@\n");
            return false;
        }

        // ====================== Fetch minues since unix epoch ====================== 
        std::string minutesSinceEpochStr;
        string fetchTimeUrl = "https://currentmillis.com/time/minutes-since-unix-epoch.php";
        if (!DownloadFile(fetchTimeUrl, minutesSinceEpochStr)) {
            my_rog_debug1("Failed to fetch min@!!.\n");
            return false;
        }

        int minutesSinceEpochValue;
        try {
            minutesSinceEpochValue = std::stoi(minutesSinceEpochStr);
        }
        catch (const std::invalid_argument) {
            my_rog_debug1("failed to parse %s\n", minutesSinceEpochStr);
            minutesSinceEpochValue = 0;
        }
        my_rog_debug1("fetched min str: %d\n", minutesSinceEpochStr);
        my_rog_debug1("fetched min: %d\n", minutesSinceEpochValue);

        // ====================== check expiryDate with remote time if license still valid ======================
        std::tm expiryDateTimeInfo = ParseDateString(decryptedExpiryDateStr);
        if (!expiryDateTimeInfo.tm_year) {
            my_rog_debug1("parsing ti failed!!\n");
            return false;
        }

        long long expiryMinutesSinceEpoch = ConvertToMinutesSinceEpoch(expiryDateTimeInfo);
        my_rog_debug1("expiry minutes %ll\n", expiryMinutesSinceEpoch);

        if (expiryMinutesSinceEpoch < minutesSinceEpochValue) {
            my_rog_debug1("exp already!!\n");
            return false;
        }

        // ====================== now enable premium features here ======================
        // we want to do it hear instead of at caller side to prevent method hooking

        my_rog_debug1("Successfully decrytped!!\n");
        // we set false here first and use Themida macro to check if dll is tampered
        int passedProtectionCheckValue = -1;
        // we set to true here if no tampered
        CHECK_PROTECTION(passedProtectionCheckValue, 90400);

        if (passedProtectionCheckValue != 90400) {
            // tampered already, generate false
            GenerateAddingBundleItemsLicensedCode((19000000 - 100 + 24 * 2 + 1 - 4 + 3 + 9 - 1 + 1 + 300 + 204 + 10) < 0);
            return false;
        }

        // just funny statement to mess up with reverse engineer, we want it returns true here
        bool result = (10000000 - 100 + 24 * 2 + 1 - 4 + 3 + 9 - 1 + 1 + 300 + 204 + 10) > 0;
        VM_TIGER_BLACK_END
        return result;
    }

    bool DownloadAndDecryptFile(const std::string& url) {
        // Download the file.
        std::string fileContent;
        if (!DownloadFile(url, fileContent)) {
            my_rog_debug1("Failed to download the file.\n");
            return false;
        }

        return MyDecryptFile(fileContent);
    }

private:
    std::string _keyHex;

    bool DownloadFile(const std::string& url, std::string& content) {
        my_rog_debug1("FileDownloader::DownloadFile starting download with url: %s\n", url);
        CURL* curl = nullptr;
        CURLcode res = CURLE_OK;

        try {

            curl = curl_easy_init();
            if (curl) {
                // Set the URL to download.
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

                my_rog_debug1("FileDownloader::DownloadFile before  curl_easy_setopt CURLOPT_WRITEFUNCTION\n");
                // Set the write callback to collect downloaded data.
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

                my_rog_debug1("FileDownloader::DownloadFile after curl_easy_setopt CURLOPT_WRITEDATA\n");

                // Perform the HTTP request.
                res = curl_easy_perform(curl);

                my_rog_debug1("FileDownloader::DownloadFile after curl_easy_perform()\n");

                // Check for errors.
                if (res != CURLE_OK) {
                    my_rog_debug1("FileDownloader::DownloadFile curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                    return false;
                }

                // DO NOT call curl_easy_cleanup(curl) here; leave the handle open for reuse
                my_rog_debug1("FileDownloader::DownloadFile before curl_easy_cleanup()\n");
                // Clean up.
               /* curl_easy_cleanup(curl);
                my_rog_debug1("FileDownloader::DownloadFile after curl_easy_cleanup()\n");
                Sleep(2000);*/
                //curl_global_cleanup();
                my_rog_debug1("FileDownloader::DownloadFile successfully\n");
                return true;
            }
            else {
                my_rog_debug1("FileDownloader::DownloadFile Failed to initialize libcurl.\n");
                return false;
            }
        }
        catch (const std::exception& e) {
            my_rog_debug1("FileDownloader::DownloadFile exception %s\n", e.what());
            // clean up the libcurl  handle if an exception occurs
            if (curl) {
                my_rog_debug1("FileDownloader::DownloadFile clean up the libcurl  handle if an exception occurs.\n");
                curl_easy_cleanup(curl);
            }
            return false;
        }

        // clean up the libcurl  handle here after all requests are done;
        if (curl) {
            my_rog_debug1("FileDownloader::DownloadFile clean up the libcurl  handle here after all requests are done.\n");
            curl_easy_cleanup(curl);
        }
        return true;
    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        my_rog_debug1("FileDownloader::WriteCallback called...\n");
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        my_rog_debug1("FileDownloader::WriteCallback completed\n");
        return totalSize;
    }



    bool ParseJson(const std::string& jsonContent) {
        rapidjson::Document document;
        document.Parse(jsonContent.c_str());

        if (document.HasParseError()) {
            my_rog_debug1("JSON parse error: %s\n", document.GetParseError());
            return false;
        }

        // Access and handle JSON properties as needed.
        // For example, you can access "xe" like this:
        if (document.HasMember("xe")) {
            const rapidjson::Value& xe = document["xe"];
            // Handle the "xe" property.
        }

        // Implement logic to save parsed data to outputFile.

        return true;
    }

    std::tm ParseDateString(const std::string& dateString) {
        std::tm timeInfo = {}; // Initialize with zeros.

        // Create an input string stream to parse the date string.
        std::istringstream dateStream(dateString);

        // Define the format of the date string ("%d/%m/%Y").
        dateStream >> std::get_time(&timeInfo, "%d/%m/%Y");

        if (dateStream.fail()) {
            my_rog_debug1("Failed to parse the date string.\n");
        }

        return timeInfo;
    }

    long long ConvertToMinutesSinceEpoch(std::tm& timeInfo) {
        // Convert the std::tm structure to std::time_t.
        std::time_t timeValue = std::mktime(&timeInfo);

        if (timeValue == -1) {
            my_rog_debug1("Conversion to std::time_t failed.\n");
            return -1; // Error condition.
        }

        // Calculate the number of seconds since the Unix epoch.
        long long secondsSinceEpoch = static_cast<long long>(timeValue);

        // Convert seconds to minutes.
        long long minutesSinceEpoch = secondsSinceEpoch / 60;

        return minutesSinceEpoch;
    }

};