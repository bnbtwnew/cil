#include "DetoursHooking.h"
#include <Windows.h>
#include "Detours/include/detours.h"
//#include <windows.h>
#include "GameUtils.h"

using namespace GameUtils;
//#pragma comment(lib, "Detours/lib/detours.lib")

namespace DetoursHooking {
    

    int(__thiscall* CBlackCipher2Client_Clear_sub_456DF0)(void* this_ptr) = (int(__thiscall*)(void*))0x456DF0;
    int __fastcall My_CBlackCipher2Client_Clear_sub_456DF0(void* this_ptr) {
        my_rog_debug1("My_CBlackCipher2Client_Clear_sub_456DF0 this_ptr = %x\n", this_ptr);
        int result = CBlackCipher2Client_Clear_sub_456DF0(this_ptr);
        my_rog_debug1("CBlackCipher2Client_Clear_sub_456DF0 result = %x\n", result);
        return result;
    }

    int(__thiscall* CBlackCipher2Client_PushData_sub_456C98)(void* this_ptr, int arg2) = (int(__thiscall*)(void*, int))0x456C98;
    int __fastcall My_CBlackCipher2Client_PushData_sub_456C98(void* this_ptr, int arg2) {
        my_rog_debug1("My_CBlackCipher2Client_PushData_sub_456C98 this_ptr = %x arg2 = %x\n", this_ptr, arg2);
        // after hooking this, we see whenever BlackCipher2_Error alert appear, arg2 is always have value 0x131
        // so let try to skip the call pushdata in this case
        int result = 1;
        if (arg2 != 0x131) {
            result = CBlackCipher2Client_PushData_sub_456C98(this_ptr, arg2);
        }
        else {
            my_rog_debug1("My_CBlackCipher2Client_PushData_sub_456C98 SKIPPED arg2 = %x\n", arg2);
        }
         
        my_rog_debug1("My_CBlackCipher2Client_PushData_sub_456C98 result = %x\n", result);
        return result;
    }

    // Please note this FlushData will be called every 500ms - xrefs_4_SubtractArg0FromArg1(v3, Time) >= 500u
    int(__thiscall* CBlackCipher2Client_FlushData_sub_456CFC)(void* this_ptr, int arg2) = (int(__thiscall*)(void*, int))0x456CFC;
    int __fastcall My_CBlackCipher2Client_FlushData_sub_456CFC(void* this_ptr, int arg2) {
        my_rog_debug1("My_CBlackCipher2Client_FlushData_sub_456CFC this_ptr = %x arg2 = %x\n", this_ptr, arg2);
        int result = CBlackCipher2Client_FlushData_sub_456CFC(this_ptr, arg2);
        my_rog_debug1("My_CBlackCipher2Client_FlushData_sub_456CFC result = %x\n", result);
        return result;
    }
    
    int(__thiscall* CHackDetector_sub_9E3024)(void* this_ptr, unsigned __int8 arg2) = (int(__thiscall*)(void*, unsigned __int8))0x9E3024;
    int __fastcall My_CHackDetector_sub_9E3024(void* this_ptr, unsigned __int8 arg2) {
        my_rog_debug1("My_CHackDetector_sub_9E3024 this_ptr = %x arg2 = %x\n", this_ptr, arg2);
        int result = 0;//CHackDetector_sub_9E3024(this_ptr, arg2);
        my_rog_debug1("My_CHackDetector_sub_9E3024 result = %x\n", result);
        // after run this, we observed this log then app crashed
        // My_CHackDetector_sub_9E3024 this_ptr = d318718 arg2 = 0
        // My_CHackDetector_sub_9E3024 result = 1
        return result;
    }

    typedef int(__thiscall* Sub_7F834A_DetectedHacking07_t)(void* this_ptr, int a2);
    Sub_7F834A_DetectedHacking07_t Sub_7F834A_DetectedHacking07 = reinterpret_cast<Sub_7F834A_DetectedHacking07_t>(0x7F834A);
    int __fastcall HookedSub7F834A(void* this_ptr, int arg2)
    {
        // Your custom code here
        // You can call the original function like this
        my_rog_debug1("arg2 = %d\n", arg2);
        my_rog_debug1("arg1 = %d\n", this_ptr);
        int result = Sub_7F834A_DetectedHacking07(this_ptr, arg2);
        my_rog_debug1("result = %d\n", result);

        return result;
    }

    int (*detectedHacking07Method_sub_7F834A)(int* thisPointer, int arg2) = (int (*)(int*, int))0x7F834A;
    int  My_detectedHacking07Method_sub_7F834A(int* thisPointer, int arg2)
    {
        my_rog_debug1("arg2 = %d\n", arg2);
        my_rog_debug1("arg1 = %x\n", thisPointer);
        int result = detectedHacking07Method_sub_7F834A(thisPointer, arg2);
        my_rog_debug1("result = %d\n", result);
        return result;
    }

    void _StartHooking(PVOID* ppPointer, PVOID pDetour, std::string description) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        //DetourAttach(&(PVOID&)detectedHacking07Method_sub_7F834A, My_detectedHacking07Method_sub_7F834A);
        DetourAttach(ppPointer, pDetour);

        if (DetourTransactionCommit() == NO_ERROR) {
            my_rog_debug1("%s successfully\n", description);
        }
        else {
            my_rog_debug1("%s failed!!\n", description);
        }
    }

    void HookedDetectedHacking07() {
        /*_StartHooking(&(PVOID&)Sub_7F834A_DetectedHacking07, HookedSub7F834A, "HookedDetectedHacking07");    
        _StartHooking(&(PVOID&)CBlackCipher2Client_Clear_sub_456DF0, My_CBlackCipher2Client_Clear_sub_456DF0, "CBlackCipher2Client_Clear_sub_456DF0");
        _StartHooking(&(PVOID&)CBlackCipher2Client_PushData_sub_456C98, My_CBlackCipher2Client_PushData_sub_456C98, "CBlackCipher2Client_PushData_sub_456C98");
        _StartHooking(&(PVOID&)CBlackCipher2Client_FlushData_sub_456CFC, My_CBlackCipher2Client_FlushData_sub_456CFC, "CBlackCipher2Client_FlushData_sub_456CFC");*/

        // hooking this can see the result but app crash immediately after login
        //_StartHooking(&(PVOID&)CHackDetector_sub_9E3024, My_CHackDetector_sub_9E3024, "CHackDetector_sub_9E3024");
    }
}