#include "GameUtils.h"
#include <string>
#include <memory>
#include <cstdarg>
//#include <iosfwd>
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "exports.h"

using namespace std;

namespace GameUtils {    
    int GetTargetModuleDllBase() {
        int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
        printf("GameUtils::GetTargetModuleDllBase %s dllBase %x\n", TARGET_MODULE_DLL, dllBase);
        return dllBase;
    }

    bool HasItemAtTile(int targetDllASLR, MapPoint point) {        

        int hasItem = 0;
        int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;

        //printf("Before HasItemAtTile invoke function pointer with base %x\n", targetDllASLR);
        //hasItem = ((int (*)(int, int, int))_0x00658D38WithASLR)(column, row, 0x1C);

        __asm
        {
        LBL_006ED887:
            mov ecx, 0x1C; 006ED887        mov         ecx, 1C
                mov edx, point.row; 006ED88C        mov         edx, dword ptr[ebp - 10]
                mov eax, point.column; 006ED88F        mov         eax, dword ptr[ebp - 0C]
                call _0x00658D38WithASLR; 006ED892        call        00658D38

                ; this line is for debugging purpose.After running the possible output is 1 or 0
                ; 1 means this tile has item, 0 otherwise :D
                mov hasItem, eax
        }

        //printf("After HasItemAtTile invoke function pointer\n");

        return hasItem == 1;
    }

    int GetItemID(int targetDllASLR, MapPoint point) {
        int mapItemID = 0;
        int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;
        __asm {
            mov ecx, 0xA4; 006ED89A        mov         ecx, 0A4
            mov edx, point.row; 006ED89F        mov         edx, dword ptr[ebp - 10]
            mov eax, point.column; 006ED8A2        mov         eax, dword ptr[ebp - 0C]
            call _0x00658D38WithASLR; 006ED8A5        call        00658D38
            push eax; 006ED8AA        push        eax
            ; this line is for debugging purpose
            mov mapItemID, eax
        }

        return mapItemID;
    }

    int GetMysteriousNumber(int targetDllASLR, MapPoint point, int itemID) {
        int mysteriousNumber = 0;
        int _0x00658D38WithASLR = targetDllASLR + 0x00658D38;
        __asm {
            mov eax, itemID
            push eax; 006ED8AA        push        eax
            mov ecx, 0x98; 006ED8AB        mov         ecx, 98
            mov edx, point.row; 006ED8B0        mov         edx, dword ptr[ebp - 10]
            mov eax, point.column; 006ED8B3        mov         eax, dword ptr[ebp - 0C]
            call _0x00658D38WithASLR; 006ED8B6        call        00658D38
            ; this line is for debugging purpose
            mov mysteriousNumber, eax
        }

        return mysteriousNumber;
    }

    std::string string_format(const std::string fmt_str, ...) {
        int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
        std::unique_ptr<char[]> formatted;
        va_list ap;
        while (1) {
            formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
            strcpy(&formatted[0], fmt_str.c_str());
            va_start(ap, fmt_str);
            final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
            va_end(ap);
            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }
        return std::string(formatted.get());
    }

    string FormatString(const string fmt_str, ...) {
        int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
        std::unique_ptr<char[]> formatted;
        va_list ap;
        while (1) {
            formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
            strcpy(&formatted[0], fmt_str.c_str());
            va_start(ap, fmt_str);
            final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
            va_end(ap);
            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }
        return std::string(formatted.get());
    }
    
    void log_debug(const std::string fmt_str, ...) {        
        int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
        std::unique_ptr<char[]> formatted;
        va_list ap;
        while (1) {
            formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
            strcpy(&formatted[0], fmt_str.c_str());
            va_start(ap, fmt_str);
            final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
            va_end(ap);
            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }
       
        cout << formatted.get();

        // FIXME: << is not working here, compiler error
        /*ofstream logFile("my_log.txt", std::ios_base::app)
        logFile << std::string(formatted.get());
        logFile.close();*/
    }
};