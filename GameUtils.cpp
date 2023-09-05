#include "GameUtils.h"
#include <string>
#include <memory>
#include <cstdarg>
//#include <iosfwd>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include "exports.h"
#include "MyLic.h"
#include "LicenseFeaturesStatus.h"


using namespace std;

#ifdef LICENSE_BUILD
// need to add this here instead of using macro to prevent crashing when launch the app, dont know why :(
void my_rog_debug1_impl(const std::string& file, int line, const std::string& function, const std::string fmt_str, ...) {
    do {} while (0);
}
#else
void my_rog_debug1_impl(const std::string& file, int line, const std::string& function, const std::string fmt_str, ...) {
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

    std::string log_message = "[" + file + ":" + std::to_string(line) + " (" + function + ")] " + std::string(formatted.get());
    cout << log_message << endl;

    //std::string(formatted.get());
    std::ofstream logFile("my_log.txt", std::ios_base::app);
    logFile << log_message; //std::string(formatted.get());
    logFile.close();
}
#endif // !LICENSE_BUILD

namespace GameUtils {        
    int previousGameState = 0;

    void AllocateAndResizeConsole(int width, int height)
    {
        // Allocate a new console for this process
        AllocConsole();

        // Get a handle to the standard output console
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (consoleHandle != INVALID_HANDLE_VALUE)
        {
            // Define a COORD structure to set the console size
            COORD consoleSize;
            consoleSize.X = width;
            consoleSize.Y = height;

            // Set the console screen buffer size
            SetConsoleScreenBufferSize(consoleHandle, consoleSize);

            // Get the console window info
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

            // Define a SMALL_RECT structure to set the console window size
            SMALL_RECT consoleRect;
            consoleRect.Left = 0;
            consoleRect.Top = 0;
            consoleRect.Right = width - 1;   // 0-based index
            consoleRect.Bottom = height - 1; // 0-based index

            // Set the console window size
            SetConsoleWindowInfo(consoleHandle, TRUE, &consoleRect);

            // Optionally, set the font size, color, or other console attributes as needed
        }
    }

    void ClearConsole()
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD topLeft = { 0, 0 };
        DWORD written;

        GetConsoleScreenBufferInfo(consoleHandle, &csbi);
        FillConsoleOutputCharacter(consoleHandle, ' ', csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);
        FillConsoleOutputAttribute(consoleHandle, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);
        SetConsoleCursorPosition(consoleHandle, topLeft);
    }

    void PrintCurrentFeatureStatesOnConsole(InGamePlaying _inGamePlaying) {
        
        ClearConsole();
        //my_rog_debug1("PrintCurrentFeatureStatesOnConsole\n");        
        int yourPlayerIndex = _inGamePlaying.GetYourPlayerIndex();
        //my_rog_debug1("PrintCurrentFeatureStatesOnConsole yourPlayerIndex = %d\n", yourPlayerIndex);
        string playerIndexBase1Str = "";
        if (yourPlayerIndex >= 0) {
            playerIndexBase1Str = "Box " + std::to_string(yourPlayerIndex + 1);
        }
        else {
            playerIndexBase1Str = "Not Set";
        }
        MyLic lic = MyLic();
        string machineIdHashed = lic.GenerateMachineID();
        string licenseStatus = "Activated";
        if (licensedAddingBundleItemsCode != LICENSED_ADDING_BUNDLE_ITEMS_VALID_CODE) {
            licenseStatus = "Expired";
        }

        cout << "==== LICENSE ====" << endl;
        cout << "Info:   \t" << machineIdHashed << endl;
        cout << "Status: \t" << licenseStatus << endl;

        cout << endl;
        cout << "==== SETTINGS ====" << endl;
        cout << "|Feature            \t" << "|Shortcuts\t\t" << "|State" << endl;
        cout << "[*] Add full shop  \t" << "Shift + 1 \t\t" << endl;
        cout << "[*] Moving effect  \t" << "Shift + 2 \t\t" << _inGamePlaying.GetCurrentMovingEffectModeDisplayString() << endl;
        //cout << "[*] Player position\t" << "P + Number\t\t" << playerIndexBase1Str << endl;        
    }

    int GetTargetModuleDllBase() {
        int dllBase = (int)GetModuleHandle(_T(TARGET_MODULE_DLL));
        my_rog_debug1("GameUtils::GetTargetModuleDllBase %s dllBase %x\n", TARGET_MODULE_DLL, dllBase);
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
            ; push eax; 006ED8AA        push        eax
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

    int GetGameState() {
        // this is porting from the logic of sub_658f00() in dll file
        /*
        int sub_658f00() {
            esp = esp - 0x8;
            eax = *dword_70559c; // 0x00ff9458
            eax = *eax; // *0x00ff9458
            if (eax != 0x0) {
                    var_4 = *(eax + 0xd4);
            }
            eax = var_4;
            return eax;
        }
        
        - Check this address in CA.exe, we can see there are 2 methods xref: sub_43abc5 and sub_45aa8a
            dword_ff9458:
        00ff9458         dd         0x00000000                                          ; DATA XREF=sub_43abc5+63, sub_43abc5+83, sub_43abc5+103, sub_43abc5+123, sub_43abc5+189, sub_43abc5+209, sub_43abc5+229, sub_43abc5+318, sub_43abc5+334, sub_43abc5+350, sub_45aa8a+273
        
        - navigate to sub_43abc5, we can see there are possible game states here
            if ((((((sub_9dd07b_GetGameState() == 0xa) || (sub_9dd07b_GetGameState() == 0x11)) || (sub_9dd07b_GetGameState() == 0x10)) || (sub_9dd07b_GetGameState() == 0xc)) || (sub_9c0fdb() != 0x0)) || (sub_9c0f17() != 0x0)) goto loc_43ad70;
        - And another one:
        int sub_9dd79f() {
            eax = *(ecx + 0xd0);
            return eax;
        }
        */
        int* DAT_0070559c_value = (int*)0x00ff9458;
        if (*DAT_0070559c_value != 0) {
            int gameObjectMaybeAddress = *DAT_0070559c_value;
            return *(int*)(gameObjectMaybeAddress + 0xd4);
        }
        return 0;
    }

    bool isGamePlaying() {
        return GetGameState() == GAME_STATE_PLAYING;
    }

    bool isShopping() {
        return GetGameState() == GAME_STATE_SHOPPING;
    }

    void EnumerateProperties() {
        int objectAddress = *(int*)0xFF9734;
        // from IDA Class Informer tab, we can see the Class Address records range from 0xD38BCC to 0xDE9EA8
        int IDA_CLASS_INFORMER_FOUND_START_ADDRESS = 0xD38BCC;
        int IDA_CLASS_INFORMER_FOUND_END_ADDRESS = 0xDE9EA8;
        int BnBTW_CA_IMAGE_BASE = 0x400000;
        int offset;
        int maxOffset = 0x6950;
        std::ofstream logfile("enumerate_properties_pointers.txt", std::ios_base::app);
        
        for (offset = 0; offset <= maxOffset; offset += 4)
        {
            int propertyAddressAtOffset = objectAddress + offset;
            int propertyValueAtOffset = *(int*)propertyAddressAtOffset;

            my_rog_debug1("checking offset %d with propertyValueAtOffset %x\n", offset, propertyValueAtOffset);

            // to make sure we have valid access, let assume the value should be at least greater than base image
            if (propertyValueAtOffset < BnBTW_CA_IMAGE_BASE) {
                continue;
            }

            //__try
            //{
                // we will try to check if this propertyValueAtOffset is a pointer

                int valueAtAddress = *(int*)propertyValueAtOffset;
                if (valueAtAddress >= IDA_CLASS_INFORMER_FOUND_START_ADDRESS && valueAtAddress <= IDA_CLASS_INFORMER_FOUND_END_ADDRESS) {
                    // possible a pointer
                    cout << hex << offset;
                    cout << "\t\t" << hex << valueAtAddress;
                    cout << "\n";
                }
            //}
            //__except(EXCEPTION_EXECUTE_HANDLER)
            //{
                
            //}

        }
        my_rog_debug1("Done enumerating!!\n");
        logfile.close();
    }

    // Reversing this method, this is part of sub_658D38 that is calling for GetItemID, HasItemAtTile
    int sub_658a2c_Retrieve_Object_Address_When_GameIsPlaying() {
        // eax = *(*dword_7055b4 + *(*dword_7055ac + **dword_70557c));
        //              dword_7055b4:
        // 007055b4         dd         0x001df02c
        // => *dword_7055b4 = 0x001df02c => CA.exe pointer
        // *dword_7055ac = 0x00006750
        // *dword_70557c =  0x00ff9734 => CA.exe pointer
        // **dword_70557c = *0x00ff9734
        
        // => eax = *(0x001df02c + *(0x00006750 + *0x00ff9734))
        /*00658a32         mov        ecx, dword [dword_70557c]                           ; dword_70557c
        00658a38         mov        ecx, dword [ecx]
        00658a3a         mov        edx, dword [dword_7055ac]                           ; dword_7055ac
        00658a40         mov        ecx, dword [edx+ecx]
        00658a43         mov        edx, dword [dword_7055b4]                           ; dword_7055b4
        00658a49         mov        ecx, dword [edx+ecx]*/
        
        /*int ecx = 0x00ff9734;
        ecx = *(int*)ecx;
        int edx = 0x00006750;
        ecx = *(int*)(ecx + edx);
        edx = 0x001df02c;
        ecx = *(int*)(ecx + edx);
        my_rog_debug1("GameUtils::sub_658a2c_Retrieve_Object_Address ecx = %x\n", ecx);*/

        if (!isGamePlaying()) {
            my_rog_debug1("GameUtils::sub_658a2c_Retrieve_Object_Address this method only can be called when game is playing, otherwise it will crash!!\n");
            return 0;
        }

        int eax = *(int*)(0x001df02c + *(int*)(0x00006750 + *(int*)0x00ff9734));
        my_rog_debug1("GameUtils::sub_658a2c_Retrieve_Object_Address eax = %x\n", eax);
        return eax;
        //return eax;
    }

    int sub_00658d38(int eax_column, int edx_row, int ecx_offset) {
        /*
          int iVar1;
            undefined4 local_14;
                var_C = ecx; // offset
                var_8 = edx; // row
                var_4 = eax; // column
            iVar1 = FUN_00658f00_GetGameState();
            if (iVar1 == 0xd) {
                eax = sub_658a2c_Retrieve_Object_Address_When_GameIsPlaying(); // will retrieve some base object                                
                ecx = (*DAT_00705640)(); // sub_80a44d(row, column)
                ecx = eax + offset ;
                local_14 = (*DAT_00705544)();
            }
            return local_14;
        */

        int gameState = GetGameState();
        if (gameState == GAME_STATE_PLAYING) {
            int gamePlayingObjectAddress = sub_658a2c_Retrieve_Object_Address_When_GameIsPlaying();
            
            //   DAT_00705640:
            //  00705640 0080A44Dh

            // *DAT_00705640 => 0x80A44D => CA.exe sub method
            /*
            int sub_80a44d(int arg0, int arg1) {
                var_8 = arg1; // column
                var_4 = arg0; // row
                esi = ecx; // some unknow base class pointer
                if (*(esi + 0x1714) == *(esi + 0x1718)) {
                        eax = 0x0;
                }
                else {
                        edi = sub_815d3a(row, column);
                        esp = esp - 0x10;
                        if (sub_8188d2(edi) == 0x0) {
                                eax = 0x0;
                        }
                        else {
                                eax = edi * 0x13c + *(esi + 0x1714);
                        }
                        esp = esp + 0x4;
                }
                return eax;
            }

            int sub_815d3a(int row, int column) {
                var_8 = arg1; // column
                esi = arg0; // row
                esp = esp - 0x4;
                edi = ecx;
                if (esi >= 0x0) {
                        var_4 = edi + 0x38;
                        eax = sub_44f0f1();
                        if ((esi <= eax) && (var_8 >= 0x0)) {
                                edi = edi + 0x2c;
                                var_4 = edi;
                                eax = sub_44f0f1();
                                if (var_8 <= eax) {
                                        edi = sub_44f0f1() * esi;
                                        esi = sub_44f0f1();
                                        eax = sub_44f0f1();
                                        eax = eax * esi - 0x1;
                                        edi = edi + var_8;
                                        if (edi >= 0x0) {
                                                if (edi <= eax) {
                                                        eax = edi;
                                                }
                                                else {
                                                        eax = eax | 0xffffffff;
                                                }
                                        }
                                        else {
                                                eax = eax | 0xffffffff;
                                        }
                                }
                                else {
                                        eax = eax | 0xffffffff;
                                }
                        }
                        else {
                                eax = eax | 0xffffffff;
                        }
                }
                else {
                        eax = eax | 0xffffffff;
                }
                return eax;
            }
            */


            // 00705544  0044F0F1h => *DAT_00705544 = 0x0044F0F1 => CA.exe sub method

        }

        return 0; // temporary only, for compiler error
    }

    /*
    This method used to check if the given skill item ID is valid or not, as we know the game has thousands of item like balloon, needle, themes...
    How I know this function?
        - First we know that AddItem function is calling sub routine sub_79275a(arg1, itemID, quantity, arg4) from CA.exe
        - Have a look inside this sub_79275a we can see it's calling sub_9A459C(itemID, &arg2, &arg3, &arg4) and inside it's calling sub_9A7334(itemID) that only given 1 argument is itemID,
        and this sub_9A459C is simple as given itemID it can return an object or return 0 (nil)
        - Hence we can simulate the implementation of sub_9A459C to enumerate all possible item id in the BNB Taiwan, if the return is not zero it means the itemID is valid    
    */
    bool IsSkillItemIDValid(int itemID) {
        /*
        sub_9A7334(itemID) need value of ecx which is assigned from caller sub_79275a:
            .text:0079276A                 mov     ecx, [dword_FF9498] => ecx = *(int*)0xFF9498
        */
        int* FF9498 = (int*)0xFF9498;
        int FF9498_Value = *FF9498;        
        
        int result = 0;
        /*
        Now we will simulate like sub_9A459C body to call sub_9A7334
        */
        __asm {
            mov eax, itemID
            push eax
            mov ecx, FF9498_Value; find Xref of sub_9A459C we find the before enter this routine it set ecx to[0xFF9498] at 0x0079276A
            add     ecx, 0xC
            mov eax, 0x9a7334
            call eax; call sub_9A7334(itemID)
            mov result, eax; move either 0 or pointer to our local variable
        };

        return result;
    }

    /*
    This method will retrieve your player position index (based zero) when you join a room
    This function return -1 if your player has not joined any room yet!
    */
    int GetYourPlayerPositionWhenJoinGame() {        
        int returnValueOfFunctionPointer_0x9CEF3F = 0;
        int* FF95B8 = (int*)0xFF95B8; // this is the value passing from callers, for example: .text:004876CC                 mov     ecx, CFxContext_CObject_dword_FF95B8
                                
        int FF95B8_value = *FF95B8;
        if (FF95B8_value == 0) {
            my_rog_debug1("ptr is null!!!!\n");
            return -1;
        }
        
        int eaxFunctionPointer = 0x9CEF3F;
        __asm {
            mov ecx, FF95B8_value
            push 0
            call eaxFunctionPointer
            mov returnValueOfFunctionPointer_0x9CEF3F, eax
        }

        return returnValueOfFunctionPointer_0x9CEF3F;
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
    

//#ifdef LICENSE_BUILD
//    // Define log_debug as an empty macro in release builds
//#define my_rog_debug1(fmt_str, ...) do {} while (0)
//#else
    //void log_debug(const std::string fmt_str, ...) {
    //    //#ifndef LICENSE_BUILD
    //    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    //    std::unique_ptr<char[]> formatted;
    //    va_list ap;
    //    while (1) {
    //        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
    //        strcpy(&formatted[0], fmt_str.c_str());
    //        va_start(ap, fmt_str);
    //        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
    //        va_end(ap);
    //        if (final_n < 0 || final_n >= n)
    //            n += abs(final_n - n + 1);
    //        else
    //            break;
    //    }

    //    cout << formatted.get();




    //    // FIXME: << is not working here, compiler error
    //    string s = std::string(formatted.get());
    //    std::ofstream logFile("my_log.txt", std::ios_base::app);
    //    logFile << s; //std::string(formatted.get());
    //    logFile.close();
    //    //#endif // !LICENSE_BUILD
    //}
//#endif // !LICENSE_BUILD

    
};

