#include <Windows.h>
#include <vector>
#include "Fonctions.h"
#include <iostream>
#include <unordered_map>

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


    std::unordered_map<std::string, std::vector<unsigned int>> allOffsets = {
      {"soul", {0x08, 0x6C}},
      {"Hp", {0x08, 0x10}},
      {"BaseMaxHp", {0x08, 0x18} },
      {"MaxHp", {0x08, 0x14}},
      {"Mp", {0x08, 0x1C} },
      {"MaxMp", {0x08, 0x20}},
      {"Sp", {0x08, 0x2C} },
      {"BaseMaxSp", {0x08, 0x34}},
      {"MaxSp", {0x08, 0x30}},
      {"Vigor", {0x08, 0x3C}},
      {"Mind", {0x08, 0x40} },
      {"Endurance", {0x08, 0x40}},
      {"Strength", {0x08, 0x48} },
      {"Dexterity", {0x08, 0x4C}},
      {"Intelligence", {0x08, 0x50} },
      {"Faith", {0x08, 0x54}},
      {"SoulLv", {0x08, 0x68}},
      {"Total Get Soul", {0x08, 0x70}},
      {"Immunity", {0x08, 0x78} }
    };
 
    std::unordered_map<std::string, uintptr_t> results = Initialization(hrpocess, GameDataManAddr, allOffsets);
  
    //resolve our GameDataMan pointer chain 
    std::vector<unsigned int> GameDataManOffset = {0x08, 0x6C};
    uintptr_t SoulAddr = results["Total Get Soul"];

    //read health value 
    int healthvalue = 0;
    ReadProcessMemory(hrpocess, (BYTE*)SoulAddr, &healthvalue, sizeof(healthvalue), nullptr);
    int newvalue = 999;
    WriteProcessMemory(hrpocess, (BYTE*)SoulAddr, &newvalue, sizeof(newvalue), nullptr);

    ReadProcessMemory(hrpocess, (BYTE*)SoulAddr, &healthvalue, sizeof(healthvalue), nullptr);
    system("PAUSE");
    return 0;
}