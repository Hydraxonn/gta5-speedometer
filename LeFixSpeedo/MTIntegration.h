#pragma once
#include <Windows.h>
#include "Util/Logger.hpp"

////Gears.asi integration/////
class MT
{
public:
    inline static HMODULE Module = nullptr;
    inline static bool FunctionsPresent = false;

    inline static bool(*NeutralGear)(void) = nullptr;
    inline static int(*GetShiftIndicator)(void) = nullptr;

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
};
