#include <vector>
#include <Windows.h>
#include <Tlhelp32.h>
#include <unordered_map>
#include <string>


DWORD GetProcessID(const wchar_t* processName);

uintptr_t GetProcessBaseAdress(DWORD processID, const wchar_t* modname);

uintptr_t FindDMAAddy(HANDLE hprocess, uintptr_t ptr, std::vector<unsigned int> offset);

std::unordered_map<std::string, uintptr_t> Initialization(HANDLE hProcess, uintptr_t baseAddress, const std::unordered_map<std::string, std::vector<unsigned int>>& allOffsets);