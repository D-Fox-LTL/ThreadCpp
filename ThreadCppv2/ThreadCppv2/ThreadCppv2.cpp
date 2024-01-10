#include <iostream>
#include <Windows.h>
#include "stdio.h"

int RNDNumber;
//CRITICAL_SECTION pcsCriticalSection01;
HANDLE pmMutex01;



DWORD WINAPI RNDGenerator(LPVOID lpParam)
{
    DWORD ldwReturnValue;


    for (;;) {
        //EnterCriticalSection(&pcsCriticalSection01);
        ldwReturnValue = WaitForSingleObject(pmMutex01, 2000);



        if (ldwReturnValue == WAIT_OBJECT_0) 
        {
            __try {
                RNDNumber++;
                if (RNDNumber > 6) RNDNumber = 1;
            } 
            __finally {

                ReleaseMutex(pmMutex01);
            }
        }





        //LeaveCriticalSection(&pcsCriticalSection01);
    }
    return 0;
}

DWORD WINAPI RNDReader(LPVOID lpParam)
{
    DWORD ldwReturnValue;

    for (int i=0;i<30;i++) {
        //EnterCriticalSection(&pcsCriticalSection01);
        ldwReturnValue = WaitForSingleObject(pmMutex01, 2000);



        if (ldwReturnValue == WAIT_OBJECT_0)
        {
            __try {
                printf("%i, ", RNDNumber);
            }
            __finally {

                ReleaseMutex(pmMutex01);
            }
        }

        //LeaveCriticalSection(&pcsCriticalSection01);

        Sleep(120);
    }
    return 0;
}


int main()
{
    DWORD ldwThread1Id, ldwThread2Id;
    HANDLE lhThread2Id;
    pmMutex01 = CreateMutex(NULL, FALSE, NULL);

    if (pmMutex01 == NULL) {
        printf("Error creating mutex: %d\n", GetLastError());
        exit(-1);
    }
    else {
        printf("Mutex created, proceeding further in code...\n");
    }

    //InitializeCriticalSection(&pcsCriticalSection01);

    // init of variable
    RNDNumber = 1;

    //Start of RND thread
    CreateThread(NULL, 0, RNDGenerator, NULL, 0, &ldwThread1Id);
    lhThread2Id=CreateThread(NULL, 0, RNDReader, NULL, 0, &ldwThread2Id);
    //RNDGenerator(NULL);

    WaitForSingleObject(lhThread2Id, 20000);


    std::cout << "Hello World!\n";
}