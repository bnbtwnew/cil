#include "GameNotificationService.h"
#include <Windows.h>
#include <iostream>
#include <sapi.h>
#include "TelegramSecret.h"
using namespace std;

namespace GameNotificationService {
    DWORD WINAPI _AsyncCurlCommand(LPVOID lpParam);
    DWORD WINAPI _AsyncSpeakThread(LPVOID lpParam);

    void SendNotification(Notification notification) {
        Notification* heapNotification = new Notification();
        heapNotification->content = notification.content;
        cout << "\n" << "SendNotification content: " << heapNotification->content << "n";        
        HANDLE hThread = CreateThread(NULL, 0, _AsyncCurlCommand, heapNotification, 0, NULL);
        if (hThread != NULL) {
            // Close the thread handle to free resources (the thread will continue running)
            CloseHandle(hThread);
            //delete heapNotification;
        }

    }

    void Speak(Notification notification) {
        Notification* heapNotification = new Notification();
        heapNotification->content = notification.content;
        cout << "\n" << "Speak content: " << heapNotification->content << "n";
        HANDLE hThread = CreateThread(NULL, 0, _AsyncSpeakThread, heapNotification, 0, NULL);
        if (hThread != NULL) {
            // Close the thread handle to free resources (the thread will continue running)
            CloseHandle(hThread);
            //delete heapNotification;
        }
    }

    DWORD WINAPI _AsyncCurlCommand(LPVOID lpParam) {
        Notification* receivedNotification = (Notification*)lpParam;
        // Construct the cURL command string
        std::string chatId = TELEGRAM_CHAT_ID;
        std::string curlCommand = "curl -X POST ";
        curlCommand += "-H \"Content-Type: application/json\" ";
        curlCommand += "-d \"{\\\"chat_id\\\": \\\"" + chatId + "\\\", \\\"text\\\": \\\"" + receivedNotification->content + "\\\"}\" ";
        curlCommand += "https://api.telegram.org/bot";
        curlCommand += TELEGRAM_BOT_TOKEN;
        curlCommand += "/sendMessage";
        cout << "\n" << curlCommand << "\n";
        system(curlCommand.c_str());

        // this way of sending curl also working fine
        // // Launch the cURL command asynchronously
        // STARTUPINFOA si = { sizeof(si) };
        // PROCESS_INFORMATION pi;
        //if (CreateProcessA(NULL, const_cast<LPSTR>(curlCommand.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        //    // Wait for the process to finish (or you can add other handling logic here)
        //    WaitForSingleObject(pi.hProcess, INFINITE);

        //    // Close process and thread handles
        //    CloseHandle(pi.hProcess);
        //    CloseHandle(pi.hThread);

        //    std::cout << "cURL command executed asynchronously." << std::endl;
        //} else {
        //    std::cerr << "Error executing cURL command." << std::endl;
        //}

        return 0;
    }

    DWORD WINAPI _AsyncSpeakThread(LPVOID lpParam) {
        Notification* receivedNotification = (Notification*)lpParam;        

        // text to speak
        // we put it here inside a thread to make it work, otherwise it will not work
        ISpVoice* pVoice = NULL;                
        HRESULT a = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        if (FAILED(a))
        {
            cout << "SendNotification ERROR 404 FAILED INITIALIZING COM\n";
            return 0;           
        }
        //HRESULT CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit);
        HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
        if (SUCCEEDED(hr))
        {
            cout << "SendNotification CoCreateInstance succeeded!!!\n";
            //getline(wcin, input);

            std::wstring stemp = std::wstring(receivedNotification->content.begin(), receivedNotification->content.end());
            LPCWSTR sw = stemp.c_str();

            hr = pVoice->Speak(sw, 0, NULL);
            //hr = pVoice->Speak((L"<voice required='Gender = Female;'>" + input).c_str(), 0, NULL);
            pVoice->Release();
            pVoice = NULL;
            cout << "SendNotification CoCreateInstance succeeded DONE!!!\n";
        }
        else {
            cout << "SendNotification CoCreateInstance failed!!!\n";
        }

        return 0;
    }
}