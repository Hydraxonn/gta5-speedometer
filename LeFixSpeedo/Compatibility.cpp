#include "Compatibility.h"
#include "Util/Logger.hpp"
#include <Windows.h>
#include <string>

namespace MT {
    bool        (*NeutralGear           )() = nullptr;
    int         (*GetShiftIndicator     )() = nullptr;

    HMODULE GearsModule = nullptr;
    bool Available;
}

template <typename T>
T CheckAddr(HMODULE lib, const std::string& funcName)
{
    FARPROC func = GetProcAddress(lib, funcName.c_str());
    if (!func)
    {
        logger.Writef("Couldn't get function [%s]", funcName.c_str());
        return nullptr;
    }
    logger.Writef("Found function [%s]", funcName.c_str());
    return reinterpret_cast<T>(func);
}

void setupCompatibility() {
    logger.Writef("Setting up Manual Transmission compatibility");
    MT::GearsModule = GetModuleHandle("Gears.asi");
    if (!MT::GearsModule) {
        MT::Available = false;
        logger.Writef("Gears.asi not found");
        return;
    }
    MT::Available = true;

    MT::NeutralGear = CheckAddr<bool (*)()>(MT::GearsModule, "MT_NeutralGear");
    MT::Available &= MT::NeutralGear != nullptr;

    MT::GetShiftIndicator = CheckAddr<int (*)()>(MT::GearsModule, "MT_GetShiftIndicator");
    MT::Available &= MT::GetShiftIndicator != nullptr;
}

void releaseCompatibility() {
    if (MT::GearsModule) {
        MT::GearsModule = nullptr;
        MT::Available = false;
    }
}
