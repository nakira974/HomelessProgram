//
// Created by maxim on 14/12/2021.
//

#ifndef HOMELESSPROGRAM_THREADS_HPP
#define HOMELESSPROGRAM_THREADS_HPP
#pragma comment( lib, "psapi" )

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "libmem.hpp"

class Threads {

public:
    Threads(DWORD id, LONG basePriority, LONG deltaPriority, DWORD pid, char processName[MAX_PATH]) {
        ThreadIdentifier = id;
        BasePriority = basePriority;
        DeltaPriority = deltaPriority;
        Pid = pid;
        strcpy_s(ProcessName, processName);
        InitializeLibMem();
    }

public:
    Threads(DWORD id, LONG basePriority, LONG deltaPriority, DWORD pid) {
        ThreadIdentifier = id;
        BasePriority = basePriority;
        DeltaPriority = deltaPriority;
        Pid = pid;
        InitializeLibMem();
    }

public:
    Threads() = default;

public:
    ~Threads() {
        free(Process);
    }

private:
    inline void InitializeLibMem() {
        Process = new lm_process_t;
        Process->pid = Pid;
        Process->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
        CloseHandle(Process->handle);
        Tid = LM_GetThreadIdEx(*Process);
    }

public:
    inline void SetProcessName(const char *processName) {
        strcpy_s(ProcessName, (const char *) processName);
    }

public:
    lm_process_t *Process{};
public:
    [[maybe_unused]] lm_tid_t Tid{};
public:
    [[maybe_unused]] DWORD ThreadIdentifier{};
public:
    [[maybe_unused]] DWORD BasePriority{};
public:
    [[maybe_unused]] DWORD DeltaPriority{};
public:
    DWORD Pid{};
public:
    char ProcessName[MAX_PATH]{};
};

#endif //HOMELESSPROGRAM_THREADS_HPP
