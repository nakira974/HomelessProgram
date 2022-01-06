//
// Created by maxim on 19/12/2021.
//

#ifndef HOMELESSPROGRAM_PROCESS_HPP
#define HOMELESSPROGRAM_PROCESS_HPP

#include <vector>
#include "Threads.hpp"
#include <libmem.h>

class Process {
public:
    Process() = default;

public:
    std::vector<Threads> ProcessThreads;
public:
    char ProcessName;
public:
    DWORD Pid;
public:
    lm_address_t Address;

};

#endif //HOMELESSPROGRAM_PROCESS_HPP
