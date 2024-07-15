#include <vector>
#include <Windows.h>
#include <Tlhelp32.h>

DWORD GetProcessID(const wchar_t* processName);

uintptr_t GetProcessBaseAdress(DWORD processID, const wchar_t* modname);

uintptr_t FindDMAAddy(HANDLE hprocess, uintptr_t ptr, std::vector<unsigned int> offset);