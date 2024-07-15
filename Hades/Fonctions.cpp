#include "Fonctions.h"
#include <stdio.h>
#include <tchar.h>

DWORD GetProcessID(const wchar_t* processName) {
	return 0;

}

uintptr_t GetProcessBaseAdress(DWORD processID, const wchar_t* modname) {
	uintptr_t procBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!_wcsicmp(modEntry.szModule, modname)) {
					procBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnap, &modEntry));
		}

	}
	CloseHandle(hSnap);
	return procBaseAddr;
}

uintptr_t FindDMAAddy(HANDLE hprocess, uintptr_t ptr, std::vector<unsigned int> offset) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offset.size(); ++i) {
		ReadProcessMemory(hprocess, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offset[i];
	}
	return addr;
}