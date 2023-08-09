#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
//#include <stdio.h>
//#include <stdint.h>
//#include <intrin.h>

#include "exports.h"
#include "Utils.h"

#pragma intrinsic(_ReturnAddress)

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
enum ChucNangCheckboxTabOrder
{
    CHECKBOX_CHUOT_BONG = 0,
    CHECKBOX_GIET_LEO = 1,
    CHECKBOX_DA_BONG = 2,
    CHECKBOX_HOI_SINH = 3,
    CHECKBOX_GIET_TRUM = 4, // chk7
    CHECKBOX_BONG_NUOC = 5,
    CHECKBOX_KHOA_TOC_DO = 6,
    CHECKBOX_AN_BUI_CAY = 7,
    CHECKBOX_RADAR = 8,
    CHECKBOX_CHUOT_NHAN_VAT = 9,
    CHECKBOX_GIAI_DOC = 10,
    CHECKBOX_MAT_NA = 12, // chk3
    CHECKBOX_BOOM_FULL_MAP = 13,
    CHECKBOX_THAU_KINH = 14, // chk5
    CHECKBOX_FULL_BONG = 15,
    CHECKBOX_XUYEN_TUONG = 16
};

//enum Direction {
//    TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
//};