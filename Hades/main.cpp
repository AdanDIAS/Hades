#include <Windows.h>
#include <vector>
#include "Fonctions.h"
#include <iostream>


int main() {
    //get process ID
    HWND wesnoth_window = FindWindow(NULL, L"ELDEN RING™");
    DWORD process_id = 0;
    GetWindowThreadProcessId(wesnoth_window, &process_id);

    //Get module base adresss
    uintptr_t moduleBase = GetProcessBaseAdress(process_id, L"eldenring.exe");

    //Get handle to process
    HANDLE hrpocess = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);
    if (hrpocess == NULL) {
        return 1;
    }

    //Resolve base adress of the pointer chain
    uintptr_t GameDataManAddr = moduleBase + 0x3D5DF58;

    //resolve our GameDataMan pointer chain 
    std::vector<unsigned int> GameDataManOffset = {0x08, 0x6C};
    uintptr_t SoulAddr = FindDMAAddy(hrpocess, GameDataManAddr, GameDataManOffset);

    //read health value 
    int healthvalue = 0;
    ReadProcessMemory(hrpocess, (BYTE*)SoulAddr, &healthvalue, sizeof(healthvalue), nullptr);
    int newvalue = 10000;
    WriteProcessMemory(hrpocess, (BYTE*)SoulAddr, &newvalue, sizeof(newvalue), nullptr);

    ReadProcessMemory(hrpocess, (BYTE*)SoulAddr, &healthvalue, sizeof(healthvalue), nullptr);
    system("PAUSE");
    return 0;
}