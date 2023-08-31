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
        std::string decryptedFileContent;
        // Refer BnBTwBotKeyGen.cpp for logic of encryption
        string fileContentDecryptionKey = _keyHex.substr(32, 32);
        if (!MyEncryptor::DecryptAES(fileContent, decryptedFileContent, fileContentDecryptionKey)) {
            std::cerr << "Failed to decrypt file the content." << std::endl;
            return false;
        }

        // Now parse json using rapidjson and extract expiry time property
        rapidjson::Document document;
        document.Parse(decryptedFileContent.c_str());
        if (document.HasParseError()) {
            std::cerr << "J S O N parse error: " << document.GetParseError() << std::endl;
            return false;
        }

        // ====================== extract anti-tampering hash and compare if it's tampered ====================== 
        if (!document.HasMember("ta")) {
            std::cerr << "t.a not exist" << std::endl;
            return false;
        }

        const rapidjson::Value& ta = document["ta"];
        if (!ta.IsString()) {
            std::cerr << "t.a is not String" << std::endl;
            return false;
        }

        string encryptedAntitamperingStr = ta.GetString();
        string antiTamperKeyHex = _keyHex.substr(0, 32);
        string decryptedAntitamperingStr;
        MyEncryptor::DecryptAES(encryptedAntitamperingStr, decryptedAntitamperingStr, antiTamperKeyHex);

        // ====================== extract buyer info value ====================== 
        if (!document.HasMember("fi")) {
            std::cerr << "f.i not exist" << std::endl;
            return false;
        }
        const rapidjson::Value& fi = document["fi"];
        if (!fi.IsString()) {
            std::cerr << "f.i is not String" << std::endl;
            return false;
        }
        string encryptedBuyerInfoStr = fi.GetString();
        string buyerInfoKeyHex = _keyHex.substr(16, 32);
        string decryptedBuyerInfoStr;
        MyEncryptor::DecryptAES(encryptedBuyerInfoStr, decryptedBuyerInfoStr, buyerInfoKeyHex);

        // ====================== extract expiry time value ====================== 
        if (!document.HasMember("xe")) {
            std::cerr << "x.e not exist" << std::endl;
            return false;
        }
        const rapidjson::Value& xe = document["xe"];
        if (!xe.IsString()) {
            std::cerr << "x.e is not String" << std::endl;
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
            std::cerr << "t.a.m.p.e.r@@@" << std::endl;
            return false;
        }

        // ====================== Fetch minues since unix epoch ====================== 
        std::string minutesSinceEpochStr;
        string fetchTimeUrl = "https://currentmillis.com/time/minutes-since-unix-epoch.php";
        if (!DownloadFile(fetchTimeUrl, minutesSinceEpochStr)) {
            std::cerr << "Failed to fetch min@!!." << std::endl;
            return false;
        }

        int minutesSinceEpochValue;
        try {
            minutesSinceEpochValue = std::stoi(minutesSinceEpochStr);
        }
        catch (const std::invalid_argument) {
            printf("failed to parse %s\n", minutesSinceEpochStr);
            minutesSinceEpochValue = 0;
        }
        cout << "fetched min str: " << minutesSinceEpochStr << endl;
        cout << "fetched min: " << minutesSinceEpochValue << endl;

        // ====================== check expiryDate with remote time if license still valid ======================
        std::tm expiryDateTimeInfo = ParseDateString(decryptedExpiryDateStr);
        if (!expiryDateTimeInfo.tm_year) {
            std::cerr << "parsing ti failed!!" << endl;
            return false;
        }

        long long expiryMinutesSinceEpoch = ConvertToMinutesSinceEpoch(expiryDateTimeInfo);
        cout << "expiry minutes " << expiryMinutesSinceEpoch << endl;

        if (expiryMinutesSinceEpoch < minutesSinceEpochValue) {
            cout << "exp already!!" << endl;
            return false;
        }

        // ====================== now enable premium features here ======================
        // we want to do it hear instead of at caller side to prevent method hooking


        return true;
    }

    bool DownloadAndDecryptFile(const std::string& url) {
        // Download the file.
        std::string fileContent;
        if (!DownloadFile(url, fileContent)) {
            std::cerr << "Failed to download the file." << std::endl;
            return false;
        }

        return MyDecryptFile(fileContent);
    }

private:
    std::string _keyHex;

    bool DownloadFile(const std::string& url, std::string& content) {
        CURL* curl;
        CURLcode res;

        curl = curl_easy_init();
        if (curl) {
            // Set the URL to download.
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Set the write callback to collect downloaded data.
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

            // Perform the HTTP request.
            res = curl_easy_perform(curl);

            // Check for errors.
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                return false;
            }

            // Clean up.
            curl_easy_cleanup(curl);
            return true;
        }
        else {
            std::cerr << "Failed to initialize libcurl." << std::endl;
            return false;
        }
    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }



    bool ParseJson(const std::string& jsonContent) {
        rapidjson::Document document;
        document.Parse(jsonContent.c_str());

        if (document.HasParseError()) {
            std::cerr << "JSON parse error: " << document.GetParseError() << std::endl;
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
            std::cerr << "Failed to parse the date string." << std::endl;
        }

        return timeInfo;
    }

    long long ConvertToMinutesSinceEpoch(std::tm& timeInfo) {
        // Convert the std::tm structure to std::time_t.
        std::time_t timeValue = std::mktime(&timeInfo);

        if (timeValue == -1) {
            std::cerr << "Conversion to std::time_t failed." << std::endl;
            return -1; // Error condition.
        }

        // Calculate the number of seconds since the Unix epoch.
        long long secondsSinceEpoch = static_cast<long long>(timeValue);

        // Convert seconds to minutes.
        long long minutesSinceEpoch = secondsSinceEpoch / 60;

        return minutesSinceEpoch;
    }

};