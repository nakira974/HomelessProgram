//
// Created by maxim on 14/12/2021.
//

#ifndef HOMELESSPROGRAM_THREADSINFO_HPP
#define HOMELESSPROGRAM_THREADSINFO_HPP
#pragma comment( lib, "psapi" )

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "Threads.hpp"

class ThreadsInfo {
public:
    ThreadsInfo() {
        ThreadsCount = GetThreadsCount();
    };
public:
    ~ThreadsInfo() {
        for (auto thread: SystemThreads) {
            delete thread;
        }
        SystemThreads.clear();
    }

public:
    static const char *GetProcessNameFromPid(DWORD pid);

public:
    [[maybe_unused]] DWORD ThreadsCount;
public:
    std::vector<Threads *> SystemThreads;
private:
    [[maybe_unused]] static BOOL ShowProcessNameForThread(DWORD pid, Threads *currentThread);

public:
    DWORD GetThreadsCount();
};

#endif //HOMELESSPROGRAM_THREADSINFO_HPP
