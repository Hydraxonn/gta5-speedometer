#pragma once
#include <Windows.h>
namespace MT {
    extern bool (*NeutralGear)();
    extern int (*GetShiftIndicator)();

    extern HMODULE GearsModule;
    extern bool Available;
}

void setupCompatibility();

void releaseCompatibility();
