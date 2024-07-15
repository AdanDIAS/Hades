#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

// Fonction pour obtenir le PID du processus (simplifié pour cet exemple)
DWORD GetProcessIdByName(const char* processName) {
   DWORD processID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnap, &pe32)) {
            do {
                if (strcmp(pe32.szExeFile, processName) == 0) {
                    processID = pe32.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &pe32));
        }
        CloseHandle(hSnap);
    }
    if (processID == 0) {
        printf("Le processus n'a pas été trouvé.\n");
        return 0;
    }
    else {
        return processID;
    }
    
}

int main() {
    const char* processName = "Tutorial-i386.exe";
    DWORD processId = GetProcessIdByName(processName);
    

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    
    if (hProcess == NULL) {
        printf("Impossible d'ouvrir le processus.\n");
        return 1;
    }

    // Adresse de mémoire à lire/écrire (exemple)
    LPVOID baseAddress = (LPVOID)(0x015A2940 + 0x0017F160 - 0x00077220 + 0xB20 + 0x8 + 0x8B0);
    SIZE_T bytesRead;
    int buffer;
    //baseAddress = 0x016D8C58;
    printf("%p\n", baseAddress);
    // Lecture en mémoire
    if (ReadProcessMemory(hProcess, baseAddress, &buffer, sizeof(buffer), &bytesRead)) {
        printf("Valeur lue : %d\n", buffer);
    } else {
        printf("Echec de la lecture de la mémoire.\n");
    }

    CloseHandle(hProcess);
    return 0;
}