#include "Compatibility.h"
#include "Util/Logger.hpp"
#include <Windows.h>
#include <string>

namespace MT {
    const char* (*GetVersion            )() = nullptr;
    bool        (*GetActive             )() = nullptr;
    void        (*SetActive             )(bool active) = nullptr;
    bool        (*NeutralGear           )() = nullptr;
    int         (*GetShiftMode          )() = nullptr;
    void        (*SetShiftMode          )(int mode) = nullptr;
    int         (*GetShiftIndicator     )() = nullptr;
    void        (*AddIgnoreVehicle      )(int vehicle) = nullptr;
    void        (*DelIgnoreVehicle      )(int vehicle) = nullptr;
    void        (*ClearIgnoredVehicles  )() = nullptr;
    unsigned    (*NumIgnoredVehicles    )() = nullptr;
    const int*  (*GetIgnoredVehicles    )() = nullptr;
    int         (*GetManagedVehicle     )() = nullptr;
    bool        (*LookingLeft           )() = nullptr;
    bool        (*LookingRight          )() = nullptr;
    bool        (*LookingBack           )() = nullptr;

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
        logger.Writef("Gears.asi not found");
        return;
    }
    MT::Available = true;
    MT::GetVersion = CheckAddr<const char* (*)()>(MT::GearsModule, "MT_GetVersion");
    MT::Available &= MT::GetVersion != nullptr;

    MT::GetActive = CheckAddr<bool (*)()>(MT::GearsModule, "MT_IsActive");
    MT::Available &= MT::GetActive != nullptr;

    MT::SetActive = CheckAddr<void (*)(bool)>(MT::GearsModule, "MT_SetActive");
    MT::Available &= MT::SetActive != nullptr;

    MT::NeutralGear = CheckAddr<bool (*)()>(MT::GearsModule, "MT_NeutralGear");
    MT::Available &= MT::NeutralGear != nullptr;

    MT::GetShiftMode = CheckAddr<int (*)()>(MT::GearsModule, "MT_GetShiftMode");
    MT::Available &= MT::GetShiftMode != nullptr;

    MT::SetShiftMode = CheckAddr<void (*)(int)>(MT::GearsModule, "MT_SetShiftMode");
    MT::Available &= MT::SetShiftMode != nullptr;

    MT::GetShiftIndicator = CheckAddr<int (*)()>(MT::GearsModule, "MT_GetShiftIndicator");
    MT::Available &= MT::GetShiftIndicator != nullptr;

    MT::AddIgnoreVehicle = CheckAddr<void (*)(int)>(MT::GearsModule, "MT_AddIgnoreVehicle");
    MT::Available &= MT::AddIgnoreVehicle != nullptr;

    MT::DelIgnoreVehicle = CheckAddr<void (*)(int)>(MT::GearsModule, "MT_DelIgnoreVehicle");
    MT::Available &= MT::DelIgnoreVehicle != nullptr;

    MT::ClearIgnoredVehicles = CheckAddr<void (*)()>(MT::GearsModule, "MT_ClearIgnoredVehicles");
    MT::Available &= MT::ClearIgnoredVehicles != nullptr;

    MT::NumIgnoredVehicles = CheckAddr<unsigned (*)()>(MT::GearsModule, "MT_NumIgnoredVehicles");
    MT::Available &= MT::NumIgnoredVehicles != nullptr;

    MT::GetIgnoredVehicles = CheckAddr<const int* (*)()>(MT::GearsModule, "MT_GetIgnoredVehicles");
    MT::Available &= MT::GetIgnoredVehicles != nullptr;

    MT::GetManagedVehicle = CheckAddr<int (*)()>(MT::GearsModule, "MT_GetManagedVehicle");
    MT::Available &= MT::GetManagedVehicle != nullptr;

    MT::LookingLeft = CheckAddr<bool (*)()>(MT::GearsModule, "MT_LookingLeft");
    MT::Available &= MT::LookingLeft != nullptr;

    MT::LookingRight = CheckAddr<bool (*)()>(MT::GearsModule, "MT_LookingRight");
    MT::Available &= MT::LookingRight != nullptr;

    MT::LookingBack = CheckAddr<bool (*)()>(MT::GearsModule, "MT_LookingBack");
    MT::Available &= MT::LookingBack != nullptr;
}

void releaseCompatibility() {
    if (MT::GearsModule && MT::Available) {
        MT::GearsModule = nullptr;
        MT::Available = false;
    }
}
