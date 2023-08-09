#pragma warning( disable : 6031 )
#include "DLLMainEntry.h"
#include "HackModule.h"

BOOL WINAPI DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    static HackModule hackModule(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        hackModule.Initialize();
        break;        
    }
    case DLL_PROCESS_DETACH:
    {
        hackModule.Deinitialize();                
        break;
    }
    }

    return TRUE;
}