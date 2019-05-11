#pragma once
#include <Windows.h>
#include "Util/Logger.hpp"

namespace MT 
{
    ////Gears.asi integration/////
    static HMODULE Module;
    static bool FunctionsPresent;

    static bool(*NeutralGear)(void) = nullptr;
    static int(*GetShiftIndicator)(void) = nullptr;

    static void* CheckAddr(HMODULE lib, const char* funcName)
    {
        FARPROC mtFunc = GetProcAddress(lib, funcName);
        if (mtFunc == nullptr)
        {
            logger.Writef("%s not available", funcName);
            return nullptr;
        }
        logger.Writef("%s available", funcName);
        return mtFunc;
    }
}
