#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define n 100

int main()
{
    HANDLE  hSerial;
    DCB dcbSerialParams = {0};
    char szBuff[n] = {0};
    DWORD dwBytesRead = 0;

    hSerial = CreateFile("\\\\.\\COM5",
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         0);
    if (hSerial == INVALID_HANDLE_VALUE){
        printf("serial create error\n");
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if(!GetCommState(hSerial, &dcbSerialParams)){
        printf("get commstate error\n");
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if(!SetCommState(hSerial, &dcbSerialParams)){
        printf("Set comState Error \n");
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout=50;
    timeouts.ReadTotalTimeoutConstant = 10;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if(!SetCommTimeouts(hSerial, &timeouts)){
        printf("setCommTimeouts Error\n");
    }

    while(1){
        if(!ReadFile(hSerial, szBuff, n, &dwBytesRead, NULL)){
            printf("readFile error\n");
        }
        else {
            printf(szBuff);
            memset(szBuff, 0, n);
        }
    }
    CloseHandle(hSerial);
    return 0;
}
