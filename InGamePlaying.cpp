#include "InGamePlaying.h"
#include "GameUtils.h"
#include "LicenseFeaturesStatus.h"
#include "ThemidaSDK.h"

using namespace GameUtils;

void InGamePlaying::UpdateMovingEffectAndPlusEffect() {
    // TForm1.bongmo.TAdvOfficeCheckbox
            // this code is porting from old version dwk hack 3.8.2
            // this version allow an dropdown list to select which type of effect when a chacter move (Black effect: 3, ...)
            /*

            00896E65        mov         ecx,dword ptr ds:[0FF9734]; ecx = *0xFF9734
            00896E6B        mov         ecx,dword ptr [ecx+6750]; ecx = *(*0xFF9734 + 6750)
            00896E71        mov         ecx,dword ptr [ecx+1DF02C]; ecx = *(*(*0xFF9734 + 6750) + 0x1DF02C)
            00896E77        add         ecx,74; ecx = *(*(*0xFF9734 + 6750) + 0x1DF02C) + 74
            00896E7A        push        1
            00896E7C        mov         eax,44F3A4; CA.exe function pointer
            00896E81        call        eax
            00896E83        mov         eax,dword ptr [ebp-4]; TForm
            00896E86        mov         eax,dword ptr [eax+4BC];TForm1.bongmo:TAdvOfficeCheckBox
            00896E8C        mov         edx,dword ptr [eax]
            00896E8E        call        dword ptr [edx+114];TAdvOfficeCheckBox.GetChecked
            00896E94        test        al,al; check al == 0 (not checked)
            00896E96>       je          00896EB0; if not checked, then jump to other components
            00896E98        mov         eax,dword ptr [ebp-4]; TForm
            00896E9B        mov         eax,dword ptr [eax+4D4];TForm1.SpinEdit1:TSpinEdit
            00896EA1        call        TSpinEdit.GetValue; get dropdown list selected value
            00896EA6        mov         [008D1BB0],eax;gvar_008D1BB0; store selected effect type to global variable
            00896EAB        call        00896CA0; call sub_896CA0
            00896EB0        mov         eax,dword ptr [ebp-4]

                _Unit131.sub_00896CA0
            00896CA0        push        ebp
            00896CA1        mov         ebp,esp
            00896CA3        push        ebx
            00896CA4        push        esi
            00896CA5        push        edi
            00896CA6        xor         eax,eax
            00896CA8        push        ebp
            00896CA9        push        896D00
            00896CAE        push        dword ptr fs:[eax]
            00896CB1        mov         dword ptr fs:[eax],esp
            00896CB4        push        0
            00896CB6        mov         ecx,dword ptr ds:[8B4FEC];0xFF95B8 gvar_008B4FEC
            00896CBC        mov         ecx,dword ptr [ecx]
            00896CBE        mov         eax,[008B5048];^gvar_009CEF3F
            00896CC3        call        eax
            00896CC5        imul        ebx,eax,4 ; ebx = eax * 4
            00896CC8        mov         ecx,dword ptr ds:[8B4FE0];0xFF9734 gvar_008B4FE0 ; ecx = 0xFF9734
            00896CCE        mov         eax,dword ptr [ecx]; eax = [0xFF9734] = *0xFF9734
            00896CD0        mov         ecx,dword ptr ds:[8B500C]; 0x6750 gvar_008B500C; ecx = [8B500C] = 0x6750
            00896CD6        mov         eax,dword ptr [ecx+eax]; eax = [0x6750 + *0xFF9734] = *(0x6750 + *0xFF9734)
            00896CD9        mov         eax,dword ptr [eax+10]; eax = [*(0x6750 + *0xFF9734) + 10] = *(*(0x6750 + *0xFF9734) + 10)
            00896CDC        mov         ecx,dword ptr [ebx+eax]; ecx = [ebx + *(*(0x6750 + *0xFF9734) + 10)] = *(ebx + *(*(0x6750 + *0xFF9734) + 10))
            00896CDF        add         ecx,2458; ecx = *(ebx + *(*(0x6750 + *0xFF9734) + 10)) + 2458
            00896CE5        mov         eax,[008D1BB0];gvar_008D1BB0; eax = selectedDropdownListValue
            00896CEA        mov         dword ptr [ecx],eax; *ecx = selectedDropdownListValue
            00896CEC        add         ecx,4; ecx = *(ebx + *(*(0x6750 + *0xFF9734) + 10)) + 2458 + 4
            00896CEF        mov         eax,0C8
            00896CF4        mov         dword ptr [ecx],eax; *(*(ebx + *(*(0x6750 + *0xFF9734) + 10)) + 2458 + 4) = 0C8
            00896CF6        xor         eax,eax
            00896CF8        pop         edx
            00896CF9        pop         ecx
            00896CFA        pop         ecx
            00896CFB        mov         dword ptr fs:[eax],edx
            00896CFE>       jmp         00896D0A
            00896D00>       jmp         @HandleAnyException
            00896D05        call        @DoneExcept
            00896D0A        pop         edi
            00896D0B        pop         esi
            00896D0C        pop         ebx
            00896D0D        pop         ebp
            00896D0E        ret

            pseudo code for sub_896ca0 from Hopper:
            int sub_896ca0() {
                stack[-20] = ebp;
                stack[-28] = *0x0;
                *0x0 = &stack[-28];
                ecx = *(dword_8b5048(0x0, stack[-28], 0x896d00, stack[-20]) * 0x4 + *(*(*dword_8b500c + **dword_8b4fe0) + 0x10));
                *(ecx + 0x2458) = *dword_8d1bb0;
                *(ecx + 0x245c) = 0xc8;
                esp = (esp - 0x10) + 0xc;
                *0x0 = 0x0;
                return 0x0;
            }

            // what do we have:
                - 008b4fec         dd         0x00ff95b8 => [ecx] = *0x00ff95b8
                - 008b5048         dd         0x009cef3f => eax = [008b5048] = 0x009cef3f => function pointer in CA.exe

                call eax => call 0x009cef3f


                sub_9cef3f: ; CA.exe
            push       ebp          ; CODE XREF=sub_4876a8+52, sub_4876a8+294, sub_4aa79a+305, sub_4b4f81+22, sub_4b4f81+369, sub_4b5a0f+454, sub_4c7632+734, sub_4c7e9c+16, sub_4c8ad7+176, sub_4c95ab+2025, sub_4c95ab+2092
            mov        ebp, esp
            mov        eax, dword [ebp+arg_0]; arg0
            mov        edx, ecx ; need ecx from caller, ecx = *this
            add        eax, 0x5; eax = eax + 5 = arg0 + 5
            imul       ecx, eax, 0xc ; ecx = eax * 0xc = (arg0 + 5) * 0xc
            add        ecx, edx; ecx = this + ecx = this + (arg0 + 5) * 0xc
            call       sub_44f0f1   ; sub_44f0f1
            pop        ebp
            ret        0x4
            */

    

    int selectedMoveEffectType = _currentMode;

    if (!GameUtils::isGamePlaying()) {
        my_rog_debug1("Game is not playing, hence can not setup effect yet, however mode toggled to %d!!\n", _currentMode);
        return;
    }

    int debug_call_eaxFunctionPointer_0x009CEF3F = 0;
    int eaxFunctionPointer = 0x9CEF3F;
    int ecxValue = *(int*)0xFF95B8; //*(int*)(*(int*)(*(int*)0xFF9734 + 6750) + 0x1DF02C) + 74;

    int FF9734_Value = *(int*)0xFF9734;


    int debug_ebx_value = 0;
    int debug_eax_ptr_value_of_eax_plus_0x6750 = 0;
    int debug_eax_ptr_value_of_eax_plus_0x10 = 0;
    int debug_ecx_ptr_value_of_eax_plus_ebx = 0;
    int debug_ecx_ptr_value_after_plus_0x2458 = 0;
    int debug_ecx_ptr_value_after_plus_4 = 0;





    //my_rog_debug1("InGamePlaying::UpdateMovingEffectAndPlusEffect ecxValue: %x\n", ecxValue);

    //__asm {
    //    ; now we port logic of sub_00896CA0
    //    push 0                           ; 00896CB4        push        0
    //    ; 00896CB6        mov         ecx, dword ptr ds : [8B4FEC] ; 0xFF95B8 gvar_008B4FEC
    //    mov ecx, ecxValue                ; 00896CBC        mov         ecx, dword ptr[ecx]
    //    mov eax, eaxFunctionPointer      ; 00896CBE        mov         eax, [008B5048]; ^ gvar_009CEF3F
    //    call eaxFunctionPointer          ; 00896CC3        call        eax

    //    ; debug purpose
    //    mov debug_call_eaxFunctionPointer_0x009CEF3F, eax

    //    imul ebx, eax, 0x4              ; 00896CC5        imul        ebx, eax, 4; ebx = eax * 4
    //    ; debug purpose
    //    mov debug_ebx_value, ebx

    //        ; 00896CC8        mov         ecx, dword ptr ds : [8B4FE0] ; 0xFF9734 gvar_008B4FE0; ecx = 0xFF9734
    //    mov eax, FF9734_Value           ; 00896CCE        mov         eax, dword ptr[ecx]; eax = [0xFF9734] = *0xFF9734
    //    mov ecx, 0x6750                 ; 00896CD0        mov         ecx, dword ptr ds : [8B500C] ; 0x6750 gvar_008B500C; ecx = [8B500C] = 0x6750
    //    mov eax, dword ptr[ecx + eax]   ; 00896CD6        mov         eax, dword ptr[ecx + eax]; eax = [0x6750 + *0xFF9734] = *(0x6750 + *0xFF9734)
    //    ; debug purpose
    //    mov debug_eax_ptr_value_of_eax_plus_0x6750, eax
    //    
    //    mov eax, dword ptr[eax + 0x10]  ; 00896CD9        mov         eax, dword ptr[eax + 10]; eax = [*(0x6750 + *0xFF9734) + 0x10] = *(*(0x6750 + *0xFF9734) + 0x10)
    //    ; debug purpose
    //    mov debug_eax_ptr_value_of_eax_plus_0x10, eax
    //    
    //    mov ecx, dword ptr[ebx + eax]   ; 00896CDC        mov         ecx, dword ptr[ebx + eax]; ecx = [ebx + *(*(0x6750 + *0xFF9734) + 0x10)] = *(ebx + *(*(0x6750 + *0xFF9734) + 10))
    //    ; debug purpose
    //    mov debug_ecx_ptr_value_of_eax_plus_ebx, ecx
    //    
    //    add ecx, 0x2458                 ; 00896CDF        add         ecx, 0x2458; ecx = *(ebx + *(*(0x6750 + *0xFF9734) + 0x10)) + 0x2458
    //    ; debug purpose
    //    ; debug purpose
    //    mov eax, dword ptr[ecx]
    //    mov debug_ecx_ptr_value_after_plus_0x2458, eax

    //    mov eax, selectedMoveEffectType ; 00896CE5        mov         eax, [008D1BB0]; gvar_008D1BB0; eax = selectedDropdownListValue
    //    
    //    
    //    mov dword ptr[ecx], eax         ; 00896CEA        mov         dword ptr[ecx], eax; *ecx = selectedDropdownListValue                                                
    //    add ecx, 4                      ; 00896CEC        add         ecx, 4; ecx = *(ebx + *(*(0x6750 + *0xFF9734) + 0x10) + 0x2458 + 0x4)
    //    ; debug purpose
    //    mov eax, dword ptr[ecx]
    //    mov debug_ecx_ptr_value_after_plus_4, eax
    //    
    //    mov eax, 0xC8                   ; 00896CEF        mov         eax, 0C8
    //    
    //    

    //    ; tested, enable this to make the shadow bigger
    //    mov dword ptr[ecx], eax         ; 00896CF4        mov         dword ptr[ecx], eax; *(*(ebx + *(*(0x6750 + *0xFF9734) + 0x10)) + 0x2458 + 4) = 0C8                

    //};
    //printf("debug_call_eaxFunctionPointer_0x009CEF3F eax = %s = %x\n", "*0x009CEF3F", debug_call_eaxFunctionPointer_0x009CEF3F); // after debugging, eax is always 0 in this case
    //printf("debug_ebx_value %s = %d\n", "ebx = eax * 4", debug_ebx_value); // as eax is always zero, hence ebx is always zero too
    //printf("debug_eax_ptr_value_of_eax_plus_0x6750 eax = %s = %x\n", "*(*0xFF9734 + 0x6750)", debug_eax_ptr_value_of_eax_plus_0x6750);
    //printf("debug_eax_ptr_value_of_eax_plus_0x10 eax = %s = %x\n", "*(*(*0xFF9734 + 0x6750) + 0x10)", debug_eax_ptr_value_of_eax_plus_0x10);
    //printf("debug_ecx_ptr_value_of_eax_plus_ebx ecx = %s = %x\n", "*(ebx + *(*(*0xFF9734 + 0x6750) + 10))", debug_ecx_ptr_value_of_eax_plus_ebx);
    //printf("debug_ecx_ptr_value_after_plus_0x2458 ecx = %s = %x\n", "*(*(ebx + *(*(*0xFF9734 + 0x6750) + 0x10)) + 0x2458)", debug_ecx_ptr_value_after_plus_0x2458);
    //printf("debug_ecx_ptr_value_after_plus_4 ecx = %s = %x\n", "*(*(ebx + *(*(*0xFF9734 + 0x6750) + 0x10) + 0x2458 + 4)", debug_ecx_ptr_value_after_plus_4);            

    // After using cheat engine to examinie 0 => 0x3C (16 players??), all of them are valid object point to CGOAIBattleBomber
    // let try to set effect for all of them
    // as after debugging, debug_call_eaxFunctionPointer_0x009CEF3F is always zero, hence we can ignore the call can calculate the fixed address
    // to set visual type effect: *(*(ebx + *(*(*0xFF9734 + 0x6750) + 0x10)) + 0x2458)
    //int offset = 0;
    //for (offset = 0; offset <= 0x3C; offset += 4)
    //{
    //    *(int*)(*(int*)(offset + *(int*)(*(int*)(*(int*)0xFF9734 + 0x6750) + 0x10)) + 0x2458) = selectedMoveEffectType;

    //    // to set plus type effect: *(*(ebx + *(*(*0xFF9734 + 0x6750) + 0x10)) + 0x2458 + 0x4)
    //    *(int*)(*(int*)(offset + *(int*)(*(int*)(*(int*)0xFF9734 + 0x6750) + 0x10)) + 0x2458 + 0x4) = 0xC8;
    //}

    int yourCurrentPlayerIndex = GetYourPlayerIndex();
    my_rog_debug1("yourCurrentPlayerIndex = %d\n", yourCurrentPlayerIndex);
    if (yourCurrentPlayerIndex < 0 || yourCurrentPlayerIndex >= 8) {
        my_rog_debug1("InGamePlaying::UpdateMovingEffectAndPlusEffect yourCurrentPlayerIndex is invalid yourCurrentPlayerIndex = %d\n", yourCurrentPlayerIndex);
        return;
    }
    
    if (licensedMovingEffectCode == LICENSED_MOVING_EFFECT_CODE) {
        for (int index = 0; index <= 7; index++) {
            int offset = index * 4;
            int movingEffect = MOVING_EFFECT_MODE_NOTHING;
            int plusEffect = 0;
            if (index == yourCurrentPlayerIndex) { // our player, toggle effect
                movingEffect = _currentMode;
                plusEffect = 0xC8; // this only work if moving effect is not MOVING_EFFECT_MODE_NOTHING
                my_rog_debug1("Update yyour player at %d to movingEffect %d plusEffect %x\n", yourCurrentPlayerIndex, movingEffect, plusEffect);
            }
            else { // other player
                movingEffect = MOVING_EFFECT_MODE_NOTHING; // disable other players effect
                plusEffect = 0;
            }

            *(int*)(*(int*)(offset + *(int*)(*(int*)(*(int*)0xFF9734 + 0x6750) + 0x10)) + 0x2458) = movingEffect;// selectedMoveEffectType;

            // to set plus type effect: *(*(ebx + *(*(*0xFF9734 + 0x6750) + 0x10)) + 0x2458 + 0x4)
            *(int*)(*(int*)(offset + *(int*)(*(int*)(*(int*)0xFF9734 + 0x6750) + 0x10)) + 0x2458 + 0x4) = plusEffect;
        }
    }    
    
}

int InGamePlaying::GetYourPlayerIndex() {
    return GetYourPlayerPositionWhenJoinGame();
}
InGamePlaying::MOVING_EFFECT_MODE InGamePlaying::GetCurrentMovingEffectMode() {
    return _currentMode;
}

std::string InGamePlaying::GetCurrentMovingEffectModeDisplayString() {
    switch (_currentMode)
    {
    case InGamePlaying::MOVING_EFFECT_MODE_NOTHING:
        return "Nothing";
        break;
    case InGamePlaying::MOVING_EFFECT_MODE_NORMAL:
        return "Normal";
        break;
    case InGamePlaying::MOVING_EFFECT_MODE_FIVE_COLORS:
        return "Five colors";
        break;
    case InGamePlaying::MOVING_EFFECT_MODE_BLACK_EFFECT:
        return "Black effect";
        break;
    default:
        return "Nothing";
        break;
    }
}

void InGamePlaying::TogglePlayerMovingEffectMode() {    
    switch (_currentMode)
    {
    case InGamePlaying::MOVING_EFFECT_MODE_NOTHING:
        _currentMode = MOVING_EFFECT_MODE_NORMAL;
        break;
    case InGamePlaying::MOVING_EFFECT_MODE_NORMAL:
        _currentMode = MOVING_EFFECT_MODE_FIVE_COLORS;
        break;
    case InGamePlaying::MOVING_EFFECT_MODE_FIVE_COLORS:
        _currentMode = MOVING_EFFECT_MODE_BLACK_EFFECT;
        break;
    case InGamePlaying::MOVING_EFFECT_MODE_BLACK_EFFECT:
        _currentMode = MOVING_EFFECT_MODE_NOTHING;
        break;
    default:
        break;
    }
    my_rog_debug1("InGamePlaying::ToggleMode _currentMode = %d\n", _currentMode);
}