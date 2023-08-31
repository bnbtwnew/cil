//#pragma once
//#include <iostream>
//#include <string>
//#include <ctime>
//#include "curl/curl.h"
//
//// follow this to build libcurl for windows using vcpkg: https://stackoverflow.com/questions/53861300/how-do-you-properly-install-libcurl-for-use-in-visual-studio-2017
//
//
//// what to do to get libcurl working:
//// 1. Add CURL_STATICLIB to Properties -> C/C++ -> Proprocessors
//// 2. build curl static lib using this command: .\vcpkg.exe install curl:x86-windows-static
//// 3. Copy libcurl.lib and zlib.lib from vcpgk_root_folder/packages\curl_x86-windows-static\lib\libcurl.lib and packages\curl_x86-windows-static\lib\zlib.lib and put inside project folder
//// 4. Include below 4 system libs and 2 static libs we just built 
//// 5. Add $(SolutionDir)curl/include to Properties -> C/C++ -> General -> Additional Include Directories
//// 6. Add $(SolutionDir)curl/lib; to Properties -> Linker -> General -> Additional Lib Directories
//// refer this: https://stackoverflow.com/questions/4176503/unresolved-symbols-when-linking-a-program-using-libcurl/5411514#5411514
//// TODO: This kind of linking should not be in header file, need to move to .cpp file or in Properties config
//#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "Normaliz.lib")
//#pragma comment(lib, "Crypt32.lib")
//#pragma comment(lib, "Wldap32.lib")
//#pragma comment(lib, "curl/lib/libcurl.lib")
//#pragma comment(lib, "curl/lib/zlib.lib")
//
//class NTPClient {
//public:
//    NTPClient(const std::string& ntpServerAddress) : ntpServerAddress_(ntpServerAddress) {
//        // Initialize libcurl.
//        curl_global_init(CURL_GLOBAL_ALL);
//    }
//
//    ~NTPClient() {
//        // Cleanup libcurl.
//        curl_global_cleanup();
//    }
//
//    // Get the current UTC time from the NTP server using HTTP.
//    std::time_t GetCurrentUTCTime() {
//        CURL* curl = curl_easy_init();
//        if (curl) {
//            std::string url = "http://" + ntpServerAddress_;
//            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//
//            // Perform the HTTP request.
//            CURLcode res = curl_easy_perform(curl);
//            if (res != CURLE_OK) {
//                std::cerr << "Failed to fetch time from the server: " << curl_easy_strerror(res) << std::endl;
//                return 0; // Return 0 to indicate failure.
//            }
//
//            // Parse the response and extract the UTC time (assuming the response contains it).
//            std::string response;
//            curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &response);
//            curl_easy_cleanup(curl);
//
//            // Convert the response to a time_t object (parsing logic depends on the server's response format).
//            std::time_t unixTime = ParseResponse(response);
//
//            return unixTime;
//        }
//        else {
//            std::cerr << "Failed to initialize libcurl." << std::endl;
//            return 0; // Return 0 to indicate failure.
//        }
//    }
//
//private:
//    std::string ntpServerAddress_;
//
//    // Parse the NTP server's response and extract the UTC time.
//    std::time_t ParseResponse(const std::string& response) {
//        // Implement parsing logic specific to your NTP server's response format.
//        // For example, if the server returns the time in a known format, parse it here.
//        // If the server returns a Unix timestamp directly, you can convert it to time_t.
//
//        // Example: Parse the response as a Unix timestamp (assuming the server returns it this way).
//        try {
//            return std::stoi(response);
//        }
//        catch (const std::exception& ex) {
//            std::cerr << "Failed to parse server response: " << ex.what() << std::endl;
//            return 0; // Return 0 to indicate failure.
//        }
//    }
//};