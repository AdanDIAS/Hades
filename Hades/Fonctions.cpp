#include "Fonctions.h"
#include <stdio.h>
#include <tchar.h>
#include <unordered_map>
#include <string>

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

std::unordered_map<std::string, uintptr_t> Initialization(HANDLE hProcess, uintptr_t baseAddress, const std::unordered_map<std::string, std::vector<unsigned int>>& allOffsets) {
	std::unordered_map<std::string, uintptr_t> results;

	for (const auto& pair : allOffsets) {
		const std::string& key = pair.first;
		const std::vector<unsigned int>& offsets = pair.second;
		uintptr_t result = FindDMAAddy(hProcess, baseAddress, offsets);
		results[key] = result;
	}

	return results;
}