#include <iostream>
#include "Headers/ThreadsInfo.hpp"
#include "libmem.hpp"
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <thread>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#if LM_CHARSET == LM_CHARSET_UC
#define LM_PRINTF wprintf
#else
#define LM_PRINTF printf
#endif

[[maybe_unused]] void LibMemTest();

int MainTask() {
    try {
        lm_bool_t isOk;
        lm_pid_t currentPid;
        const char *processName;
        do {

            auto *threadsInfo = new ThreadsInfo();
            bool processSuccess = threadsInfo->ThreadsCount > 0;

            if (processSuccess) {
                currentPid = threadsInfo->SystemThreads[2000]->Process->pid;
                processName = threadsInfo->SystemThreads[2000]->ProcessName;
                isOk = LM_CheckProcess(currentPid);
                delete threadsInfo;
            } else {
                delete threadsInfo;
                break;
            }

        } while (!isOk);

        if (isOk) {
            std::cout << "Process ended correctly, for process with pid number : " << currentPid << " name :"
                      << processName
                      << "has been checked.\n" << std::endl;
        } else {
            std::cout << "Process failed, for process with pid number : " << currentPid << " name :" << processName
                      << "has not been checked.\n" << std::endl;
        }


    } catch (std::exception &ex) {
        std::cout << "Exception : " << ex.what();
    }

    return (EXIT_SUCCESS);
}

int main() {

    std::thread mainTask(MainTask);
    mainTask.join();
    return 0;

}


