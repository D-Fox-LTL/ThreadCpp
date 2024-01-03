#include <iostream>
#include <Windows.h>
#include "stdio.h"

int RNDNumber;
bool blClose = false;


DWORD WINAPI RNDGenerator(LPVOID lpParam)
{
    for (;;) {
        RNDNumber++;
        if (RNDNumber > 6) RNDNumber = 1;
        Sleep(200);
    }


    return 0;
}

DWORD WINAPI RNDReader(LPVOID lpParam)
{
    for (int i=0;i<20;i++) {
        printf("%i, ", RNDNumber);
        Sleep(200);
    }

    blClose = true;
    return 0;
}


int main()
{
    DWORD ldwThread1Id, ldwThread2Id;
    HANDLE lhThread2Id;



    // init of variable
    RNDNumber = 1;

    //Start of RND thread
    CreateThread(NULL, 0, RNDGenerator, NULL, 0, &ldwThread1Id);
    lhThread2Id=CreateThread(NULL, 0, RNDReader, NULL, 0, &ldwThread2Id);
    //RNDGenerator(NULL);

    WaitForSingleObject(lhThread2Id, 20000);


    std::cout << "Hello World!\n";
}