//
// Created by maxim on 14/12/2021.
//

#include "../Headers/ThreadsInfo.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

[[maybe_unused]] BOOL ThreadsInfo::ShowProcessNameForThread(DWORD pid, Threads *currentThread) {
    wchar_t szProcessName[MAX_PATH] = L"<unknown>";

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (hProcess != nullptr) {
        if (GetModuleFileNameEx(hProcess, nullptr, reinterpret_cast<LPSTR>(szProcessName),
                                sizeof(wchar_t) * MAX_PATH / sizeof(wchar_t)) != 0) {
            //printf(" Name: %ws (%d)", szProcessName, pid);
            wcscpy(reinterpret_cast<wchar_t *>(currentThread->ProcessName), szProcessName);
            CloseHandle(hProcess);
            return TRUE;
        } else {
            //printf(" PiD: %d", pid);
            CloseHandle(hProcess);
            return FALSE;
        }

    } else
        //printf(" PiD: %d", pid);

        return FALSE;
}

DWORD ThreadsInfo::GetThreadsCount() {
    DWORD dwThreadCount = 0;

    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
        return (0);

    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32)) {
        CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
        return (0);
    }

    std::vector<Threads *> threads;
    do {
        auto *currentThread =
                new Threads(te32.th32ThreadID,
                            te32.tpBasePri,
                            te32.tpDeltaPri,
                            te32.th32OwnerProcessID);

        SystemThreads.push_back(currentThread);
        //printf("THREAD ID = 0x%08X (base priority  = %d | delta priority = %d)", te32.th32ThreadID, te32.tpBasePri, te32.tpDeltaPri);
        //ShowProcessNameForThread(te32.th32OwnerProcessID, currentThread);
        currentThread->SetProcessName(GetProcessNameFromPid(currentThread->Pid));
        dwThreadCount++;
        //printf("\n");
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    //printf("\n\n\t Count %d thereads.", dwThreadCount);
    return dwThreadCount;
}

const char *ThreadsInfo::GetProcessNameFromPid(DWORD pid) {
    const char *result = "";
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);
    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        //std::wcout  << "can't get a process snapshot ";
        CloseHandle(processesSnapshot);
        return result;
    }

    for (BOOL bok = Process32First(processesSnapshot, &processInfo); bok; bok = Process32Next(processesSnapshot,
                                                                                              &processInfo)) {
        if (pid == processInfo.th32ProcessID) {
            //std::wcout << "found running process: " << processInfo.szExeFile;
            CloseHandle(processesSnapshot);
            result = processInfo.szExeFile;
        }

    }
    //std::wcout << "no process with given pid" << thread->Pid;

    return result;
}

#pragma clang diagnostic pop